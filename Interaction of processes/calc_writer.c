#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buffer[BUFFER_SIZE];

    // create the FIFO (named pipe)
    mkfifo(myfifo, 0666);

    while (1)
    {
        // open the FIFO for writing
        fd = open(myfifo, O_WRONLY);

        // get the command from user
        printf("Enter a command (e.g. '2 + 2'): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // write the command to the FIFO
        write(fd, buffer, strlen(buffer)+1);

        // close the FIFO
        close(fd);
    }

    return 0;
}
