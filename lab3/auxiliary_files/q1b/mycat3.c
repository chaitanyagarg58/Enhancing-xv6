#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    int rd_fd = open("in.txt", O_RDONLY);
    int wr_fd = open("out.txt", O_WRONLY | O_CREAT, 0777);

    // close(0);
    // close(1);
    // dup(rd_fd);
    // dup(wr_fd);

    dup2(rd_fd, 0);
    dup2(wr_fd, 1);

    char character;
    int size;
    while((size = read(0, &character, sizeof(character))) > 0)
    	write(1, &character, size);


    // while (scanf("%s", &character) > 0) printf("%s", &character);
    return 0;
}
