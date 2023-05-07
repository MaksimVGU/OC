#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 12345 // определение ключа для очереди сообщений
#define MAX_MSG_SIZE 512 // максимальный размер сообщения в очереди

typedef struct { // определение пользовательской структуры CalcTask
    long type; // тип сообщения
    char operation; // операция калькулятора
    double operand1; // первый операнд
    double operand2; // второй операнд
} CalcTask;

int main() 
{
    key_t key = ftok("/tmp", 'C'); // создание ключа IPC для очереди сообщений
    if (key == -1) // проверка успешности создания ключа
    {
        perror("ftok"); // вывод сообщения об ошибке
        exit(1); // завершение программы с кодом 1
    }

    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT); // создание или подключение к очереди сообщений
    if (msgid == -1) // проверка успешности создания очереди
    {
        perror("msgget"); // вывод сообщения об ошибке
        exit(1); // завершение программы с кодом 1
    }

    while (1) // бесконечный цикл для ожидания и обработки задач калькулятора
    {
        CalcTask task; // создание экземпляра структуры CalcTask

        printf("Enter an operation (+, -, *, /, ^) and two operands:"); // запрос на ввод операции и двух операндов
        scanf(" %c %lf %lf", &task.operation, &task.operand1, &task.operand2); // считывание введенных значений и сохранение в экземпляре структуры CalcTask

        char msg[MAX_MSG_SIZE]; // создание буфера для сообщения в очереди
        sprintf(msg, "%lf %c %lf", task.operand1, task.operation, task.operand2); // формирование сообщения вбуфере msg в формате: "значение_операнда1 операция значение_операнда2"
        task.type = 1; // установка типа сообщения в структуре CalcTask

        if (msgsnd(msgid, msg, strlen(msg) + 1, 0) == -1) // отправка сообщения в очередь
        {
            perror("msgsnd"); // вывод сообщения об ошибке
            exit(1); // завершение программы с кодом 1
        }
        if (msgsnd(msgid, &task, sizeof(task) - sizeof(long), 0) == -1) // отправка сообщения в очередь
        {
            perror("msgsnd"); // вывод сообщения об ошибке
            exit(1); // завершение программы с кодом 1
        }
    }

    return 0; 
}
