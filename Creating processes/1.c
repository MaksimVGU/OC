#include <stdio.h> 
#include <unistd.h>

int main() { // объявление главной функции программы
    printf("Текущий ID процесса: %d\n", getpid()); // вывод текущего ID процесса на экран
    printf("ID родительского процесса: %d\n", getppid()); // вывод ID родительского процесса на экран
    return 0; 
}