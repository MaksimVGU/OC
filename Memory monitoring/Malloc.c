#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    // Объявление указателя на выделенную память
    char * memory_for_eaten;
    // Выделение памяти в размере 100 МБ
    size_t bytes = (1024 * 1024 * 100);
    // Счетчик использованной памяти
    int used = 0;
    // Бесконечный цикл выделения памяти
    for (;;) 
    {
        // Выделение памяти размером 100 МБ с помощью функции malloc
        memory_for_eaten = (char * )malloc(bytes);
        // Если выделить память не удалось, выводим сообщение о количестве использованной памяти и завершаем программу
        if (memory_for_eaten == NULL) 
        {
            printf("\nTotal eaten memory: %i MB\n", used / 1024);
            exit(-1);
        }
        // Увеличиваем счетчик использованной памяти на 100 МБ
        used += 100;
        // Выводим количество использованной памяти в МБ
        printf("USED: %d MB\n", used / 1024);
    }
    return 0;
}
