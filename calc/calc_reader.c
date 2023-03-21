#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_KEY 12345
#define MAX_MSG_SIZE 512

typedef struct {
    long type;
    char operation;
    double operand1;
    double operand2;
} CalcTask;

int main() {
    key_t key = ftok("/tmp", 'C');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        CalcTask task;

CalcTask task;

printf("Enter an operation (+, -, *, /, ^) and two operands: ");
scanf("%c %lf %lf", &task.operation, &task.operand1, &task.operand2);

char msg[MAX_MSG_SIZE];
sprintf(msg, "%lf %c %lf", task.operand1, task.operation, task.operand2);

task.type = 1;

if (msgsnd(msgid, msg, strlen(msg) + 1, 0) == -1) {
    perror("msgsnd");
    exit(1);
}
        if (msgsnd(msgid, &task, sizeof(task) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
