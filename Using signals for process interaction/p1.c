#include <stdio.h>  // подключаем стандартную библиотеку ввода-вывода
#include <signal.h>  // подключаем библиотеку для работы с сигналами
#include <unistd.h>  // подключаем библиотеку для работы с POSIX API

char* string_to_output = "Hello, world!";  // строка для вывода на экран

// функция-обработчик сигналов
void signal_handler(int signal)
{
    if (signal == SIGUSR1)  // если получен сигнал SIGUSR1
    {
        string_to_output = "Received SIGUSR1";  // меняем строку для вывода
    }
    else if (signal == SIGUSR2)  // если получен сигнал SIGUSR2
    {
        string_to_output = "Received SIGUSR2";  // меняем строку для вывода
    }
}

int main()
{
    // устанавливаем функцию-обработчик для сигналов SIGUSR1 и SIGUSR2
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    
    while (1)  // бесконечный цикл
    {
        printf("%s\n", string_to_output);  // выводим строку на экран
        sleep(1);  // ждем 1 секунду
    }
    
    return 0;  // возвращаем 0 - успех
}
