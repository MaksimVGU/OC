p2 - это программа, которая отправляет сигнал SIGUSR1 или SIGUSR2 другой программе. p2 получает в качестве аргументов PID процесса-получателя, тип сигнала и задержку в секундах. После запуска p2 отправляет заданный тип сигнала процессу-получателю с использованием системного вызова kill().
Если p2 была запущена с неправильными аргументами (например, если PID процесса-получателя не существует или задан неправильный тип сигнала), она выводит сообщение об ошибке и завершается.
p2 использует механизм сигналов, чтобы обмениваться данными с другой программой. Она не завершается сама по себе, а завершается только после отправки сигнала процессу-получателю. 