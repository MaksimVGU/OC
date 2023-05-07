#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
int main() {
    pid_t pid; // переменная для хранения идентификатора процесса

    printf("Original process id: %d\n", getpid()); // вывод идентификатора текущего процесса
    printf("Original parent process id: %d\n", getppid()); // вывод идентификатора родительского процесса

    pid = fork(); // создание копии текущего процесса

    if (pid == -1) { // если не удалось создать копию
        printf("Error: Failed to create a new process.\n");
        return 1; // завершаем программу с кодом ошибки
    } else if (pid == 0) { // если текущий процесс - копия
        printf("New process id: %d\n", getpid()); // выводим идентификатор текущего процесса (копии)
        printf("New parent process id: %d\n", getppid()); // выводим идентификатор родительского процесса (копии)
    } else { // если текущий процесс - оригинал
        printf("Original process id: %d\n", getpid()); // выводим идентификатор текущего процесса (оригинала)
        printf("Original parent process id: %d\n", getppid()); // выводим идентификатор родительского процесса (оригинала)
    }

    return 0;
} 
 