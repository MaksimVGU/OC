Данная программа создает новый процесс с помощью функции fork(), 
а затем вызывает новый процесс с помощью функции execvp(), 
передавая ему имя исполняемого файла в массиве аргументов. В родительском 
процессе выводится информация о его ID и ID родительского процесса, а в дочернем - 
также выводится информация о его ID и ID родительского процесса, а затем 
вызывается новый процесс с помощью функции execvp(). 