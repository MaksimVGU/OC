#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <math.h>

#define MSG_KEY 12345

typedef struct {
    long type;
    char operation;
    double operand1;
    double operand2;
} CalcTask;

typedef struct {
    long type;
    double result;
} CalcResult;

int main() 
{
    int msgid;
    CalcTask task;
    CalcResult result;

    // Получаем идентификатор очереди сообщений
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Calc Worker started, waiting for tasks...\n");

    while (1) {
        // Получаем сообщение с типом 1 из очереди сообщений
        if (msgrcv(msgid, &task, sizeof(task) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // Извлекаем аргументы и операцию из сообщения
        double a = task.operand1;
        double b = task.operand2;
        char op = task.operation;

        // Вычисляем результат
        switch (op) {
            case '+':
                result.result = a + b;
                break;
            case '-':
                result.result = a - b;
                break;
            case '*':
                result.result = a * b;
                break;
            case '/':
                if (b == 0) {
                    result.result = INFINITY;
                } else {
                    result.result = a / b;
                }
                break;
            case '^':
                result.result = pow(a, b);
                break;
            default:
                result.result = NAN;
                break;
        }

        result.type = 2;

        // Отправляем сообщение с типом 2 обратно в очередь сообщений
        if (msgsnd(msgid, &result, sizeof(result) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("\nTask completed: %lf %c %lf = %lf\n", a, op, b, result.result);
    }

    return 0;
}
