#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFER_SIZE 256

struct message {
    long mtype;
    char mtext[BUFFER_SIZE];
};

void calculate(char *command, char *result)
{
    int a, b;
    char op;
    sscanf(command, "%d %c %d", &a, &op, &b);

    switch (op)
    {
        case '+':
            sprintf(result, "%d", a + b);
            break;
        case '-':
            sprintf(result, "%d", a - b);
            break;
        case '*':
            sprintf(result, "%d", a * b);
            break;
        case '/':
            if (b == 0) {
                strcpy(result, "Divide by zero error");
            } else {
                sprintf(result, "%d", a / b);
            }
            break;
        case '^':
            sprintf(result, "%d", (int) pow(a, b));
            break;
        default:
            strcpy(result, "Invalid operator");
            break;
    }
}

int main()
{
    key_t key;
    int msqid;
    struct message msg;
    size_t length;

    // generate unique key
    if ((key = ftok(".", 'c')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // create message queue
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // receive messages and process them
    while (true) {
        // receive message
        if (msgrcv(msqid, &msg, BUFFER_SIZE, 0, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        // check for end-of-file message
        if (strcmp(msg.mtext, "EOF") == 0) {
            break;
        }

        // process message
        char result[BUFFER_SIZE];
        calculate(msg.mtext, result);

        // send result back
        struct message reply = { 1, "" };
        strncpy(reply.mtext, result, BUFFER_SIZE);
        length = strlen(reply.mtext) + 1;
        if (msgsnd(msqid, &reply, length, 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    // remove message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
