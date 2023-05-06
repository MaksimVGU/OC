#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <math.h>

#define MSG_KEY 12345 // задаем ключ для обмена сообщениями

// определяем структуру для задачи калькулятора
typedef struct {
    long type; // тип сообщения
    char operation; // операция
    double operand1; // первый операнд
    double operand2; // второй операнд
} CalcTask;

// определяем структуру для результата калькулятора
typedef struct {
    long type; // тип сообщения
    double result; // результат
} CalcResult;

int main()
{
    int msgid; // идентификатор очереди сообщений
    CalcTask task; // задача калькулятора
    CalcResult result; // результат калькулятора

    // Получаем идентификатор очереди сообщений
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT); // создаем очередь сообщений или получаем ее идентификатор, если она уже была создана
    if (msgid == -1) { // проверяем успешность создания очереди сообщений
        perror("msgget"); // выводим сообщение об ошибке
        exit(1); // завершаем программу с ошибкой
    }

    printf("Calc Worker started, waiting for tasks...\n");

    while (1) 
    {
        // Получаем сообщение с типом 1 из очереди сообщений
        if (msgrcv(msgid, &task, sizeof(task) - sizeof(long), 1, 0) == -1) { // получаем сообщение из очереди с типом 1
            perror("msgrcv"); // выводим сообщение об ошибке
            exit(1); // завершаем программу с ошибкой
        }

        // Извлекаем аргументы и операцию из сообщения
        double a = task.operand1; // извлекаем первый операнд
        double b = task.operand2; // извлекаем второй операнд
        char op = task.operation; // извлекаем операцию

        // Вычисляем результат
        switch (op) { // выбираем действие в зависимости от операции
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
                if (b == 0) { // проверяем деление на ноль
                    result.result = INFINITY;
                } else {
                    result.result = a / b;
                }
                break;
            case '^':
                result.result = pow(a, b);
                break;
            default:
                result.result = NAN; // результат неопределен
                break;
        }
        // Устанавливаем тип сообщения в 2, чтобы клиент знал, что это результат выполнения операции
        result.type = 2;

        // Отправляем сообщение обратно в очередь сообщений с типом 2
        // Функция msgsnd возвращает -1, если произошла ошибка при отправке сообщения
        if (msgsnd(msgid, &result, sizeof(result) - sizeof(long), 0) == -1) {
        perror("msgsnd"); // Выводим сообщение об ошибке
        exit(1); // Завершаем программу с кодом ошибки
        }

        // Выводим сообщение о завершении задания, включая аргументы и результат
        printf("\nTask completed: %lf %c %lf = %lf\n", a, op, b, result.result);

        // Конец бесконечного цикла
    } 
    return 0; // Возвращаем код успешного завершения программы
}