#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0; // глобальная переменная для хранения суммы
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // инициализация мьютекса

// функция, которую будет выполнять каждый поток
void *thread_function(void *arg) {
    int i; // счетчик для цикла
    int thread_number = *(int *) arg; // приводим указатель к целому числу и присваиваем номер потока
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // блокируем доступ к глобальной переменной
        counter++; // увеличиваем значение счетчика на 1
        pthread_mutex_unlock(&mutex); // разблокируем доступ к глобальной переменной
    }
    printf("Thread %d finished\n", thread_number); // сообщаем, что поток завершил работу
    pthread_exit(NULL); // завершаем работу потока
}

int main(int argc, char *argv[]) {
    int i, num_threads; // переменные для счетчика циклов и количества потоков
    pthread_t *threads; // указатель на массив потоков
    num_threads = atoi(argv[1]); // преобразуем аргумент командной строки в число
    threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t)); // выделяем память под массив потоков
    for (i = 0; i < num_threads; i++) {
        int *thread_number = malloc(sizeof(int)); // выделяем память под номер потока
        *thread_number = i + 1; // присваиваем значение номеру потока
        pthread_create(&threads[i], NULL, thread_function, (void *) thread_number); // создаем новый поток
    }
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL); // ожидаем завершения всех потоков
    }
    printf("Final value of counter: %d\n", counter); // выводим итоговое значение счетчика
    free(threads); // освобождаем память, выделенную под массив потоков
    pthread_mutex_destroy(&mutex); // удаляем мьютекс
    return 0;
}
