#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid;          // Тип pid_t для хранения идентификатора процесса
    char *args[] = {"./executable", NULL};  // Массив аргументов для нового процесса (здесь просто имя исполняемого файла)

    pid = fork();       // Создание нового процесса путем дублирования текущего

    if (pid == -1) {    // Проверка на ошибку при создании процесса
        perror("fork"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход с кодом ошибки
    }
    else if (pid == 0) { // Код для дочернего процесса
        printf("Child: PID=%ld, PPID=%ld\n", (long) getpid(), (long) getppid()); // Вывод идентификаторов текущего и родительского процесса

        if (execvp(args[0], args) == -1) { // Вызов нового процесса, заменяющего текущий код
            perror("execvp");   // Вывод сообщения об ошибке
            exit(EXIT_FAILURE); // Выход с кодом ошибки
        }
    }
    else { // Код для родительского процесса
        printf("Parent: PID=%ld, PPID=%ld\n", (long) getpid(), (long) getppid()); // Вывод идентификаторов текущего и родительского процесса
    }

    return 0;
}
