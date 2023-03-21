#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_queue" // определение имени очереди
#define MAX_MSG_SIZE 256 // максимальный размер сообщения в очереди

int main() {
    char message[MAX_MSG_SIZE]; // буфер для сообщения
    mqd_t mq; // дескриптор очереди сообщений

    struct mq_attr attr; // атрибуты очереди сообщений
    attr.mq_flags = 0; // флаги
    attr.mq_maxmsg = 10; // максимальное количество сообщений в очереди
    attr.mq_msgsize = MAX_MSG_SIZE; // максимальный размер сообщения в очереди
    attr.mq_curmsgs = 0; // текущее количество сообщений в очереди

    mq_unlink(QUEUE_NAME); // удаление очереди, если она существует
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0666, &attr); // создание очереди

    if (mq == -1) { // проверка на успешное создание очереди
        perror("mq_open"); // вывод ошибки
        exit(1); // завершение программы с кодом ошибки
    }

    while (1) { // цикл отправки сообщений в очередь
        int a, b;
        char operation;

        printf("Enter expression (e.g. 2+3): ");
        fgets(message, MAX_MSG_SIZE, stdin); // получаем строку с выражением

        sscanf(message, "%d%c%d", &a, &operation, &b); // парсим выражение
        sprintf(message, "%d %c %d", a, operation, b); // переформатируем выражение

        if (mq_send(mq, message, MAX_MSG_SIZE, 0) == -1) { // отправляем сообщение в очередь
            perror("mq_send"); // вывод ошибки, если произошла ошибка
        }
    }

    mq_close(mq); // закрытие дескриптора очереди
    mq_unlink(QUEUE_NAME); // удаление очереди
    return 0; // завершение программы
}
