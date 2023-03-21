#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <math.h>

#define MSG_KEY 12345

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() 
{
    int msgid;
    struct msgbuf msg;
    double result;
    char op;
    double a, b;

    // Получаем идентификатор очереди сообщений
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Calc Worker started, waiting for tasks...\n");

    while (1) {
        // Получаем сообщение из очереди сообщений
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // Извлекаем аргументы и операцию из сообщения
        sscanf(msg.mtext, "%lf %c %lf", &a, &op, &b); 
        printf("%lf + %lf", a, b);
        // Вычисляем результат
        switch (op) {
            case '+':
                
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                if (b == 0) {
                    result = INFINITY;
                } else {
                    result = a / b;
                }
                break;
            case '^':
                result = pow(a, b);
                break;
            default:
                result = NAN;
                break;
        }

        // Создаем новое сообщение с результатом вычислений
        sprintf(msg.mtext, "%lf", result);
        msg.mtype = 2;

        // Отправляем сообщение обратно в очередь сообщений
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Task completed: %lf %c %lf = %lf\n", a, op, b, result);
    }

    return 0;
}
 