#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#define MAX_TEXT_SIZE 100

//объявляем новый пользовательский тип данных message,использующийся для представления сообщения, которое будет отправлено в очередь сообщений.
typedef struct {
    long type;                  // тип сообщения
    char text[MAX_TEXT_SIZE];   // текст сообщения
} message;

int main() {
    // создаем очередь сообщений
    key_t key = ftok("calculator", 65);    // генерируем ключ для очереди
    int msgid = msgget(key, 0666 | IPC_CREAT);   // создаем очередь сообщений с заданным ключом

    if (msgid == -1) {      // проверяем успешность создания очереди
        printf("Ошибка при создании очереди сообщений\n");
        exit(EXIT_FAILURE);
    }

    // запускаем бесконечный цикл для обработки сообщений
    while (1) {
        message msg;    // создаем сообщение
        // получаем сообщение из очереди
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {  // читаем сообщение с типом 1
            printf("Ошибка при чтении сообщения\n");
            exit(EXIT_FAILURE);
        }

        // парсим сообщение
        char arg1[MAX_TEXT_SIZE], arg2[MAX_TEXT_SIZE], op;
        sscanf(msg.text, "%s %c %s", arg1, &op, arg2);   // разбираем сообщение на аргументы и оператор

        // вычисляем результат
        float result;
        switch (op) {
            case '+':
                result = atof(arg1) + atof(arg2);
                break;
            case '-':
                result = atof(arg1) - atof(arg2);
                break;
            case '*':
                result = atof(arg1) * atof(arg2);
                break;
            case '/':
                result = atof(arg1) / atof(arg2);
                break;
            default:
                printf("Ошибка: неверный оператор\n");
                continue;
        }

        // отправляем результат обратно в очередь
        char result_str[MAX_TEXT_SIZE];
        snprintf(result_str, sizeof(result_str), "%.2f", result); // преобразуем результат в строку
        message result_msg; //объявляем переменную типа message, которая используется для хранения сообщения, отправляемого в очередь сообщений.
        result_msg.type = 2;    // задаем тип сообщения
        strcpy(result_msg.text, result_str);  // копируем результат в сообщение
        if (msgsnd(msgid, &result_msg, sizeof(result_msg.text), 0) == -1) { // отправляем сообщение с типом 2
            printf("Ошибка при отправке сообщения\n");
            exit(EXIT_FAILURE); //завершение программы с кодом ошибки.
        }
    }

    return 0;
}
