#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 3)  // если в командной строке не было передано 2 параметра
    {
        printf("Usage: %s <pid> <signal>\n", argv[0]);  // выводим подсказку по использованию программы
        return 1;  // возвращаем 1 - ошибка
    }
    
    int pid = atoi(argv[1]);  // преобразуем первый параметр (PID программы-получателя) из строки в число
    int signal = atoi(argv[2]);  // преобразуем второй параметр (номер сигнала) из строки в число
    
    // отправляем сигнал программе-получателю и проверяем, произошла ли ошибка
    if (kill(pid, signal) == -1)
    {
        printf("Error sending signal\n");  // выводим сообщение об ошибке
        return 1;  // возвращаем 1 - ошибка
    }
    
    return 0;
}
    