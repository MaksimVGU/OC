#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Функция, которую будут выполнять потоки
void* thread_func(void* arg) {
    // Извлечение номера потока из аргумента
    int thread_num = *(int*)arg;
    // Цикл вывода строки на экран 10 раз
    for (int i = 0; i < 10; i++) {
        printf("Привет, я поток #%d\n", thread_num);
    }
    // Функция потока должна возвращать указатель на void
    return NULL;
}

int main(int argc, char** argv) {
    // Проверка наличия аргумента командной строки
    if (argc != 2) {
        printf("Использование: %s <количество потоков>\n", argv[0]);
        return 1;
    }
    // Извлечение числа потоков из аргумента
    int num_threads = atoi(argv[1]);
    // Создание массива для хранения идентификаторов потоков
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    // Создание массива для передачи номера потока в функцию потока
    int* thread_nums = malloc(num_threads * sizeof(int));
    // Цикл создания потоков
    for (int i = 0; i < num_threads; i++) {
        // Сохранение номера потока в массиве для передачи в функцию потока
        thread_nums[i] = i;
        // Создание потока, передача ему номера потока и функции потока
        pthread_create(&threads[i], NULL, thread_func, &thread_nums[i]);
    }
    // Цикл ожидания завершения всех потоков
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    // Освобождение памяти, выделенной под массивы
    free(threads);
    free(thread_nums);
    // Выход из программы с кодом 0 (успешное завершение)
    return 0;
}