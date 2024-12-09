#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    int rd_fd = open("in.txt", O_RDONLY);
    // if (rd_fd == NULL) {
    //     perror("Failed to open the file");
    //     return 1;
    // }
    // Use "chmod u+w ." in the current directory
    // If the program is not able to create file
    int wr_fd = open("out.txt", O_WRONLY);
    // if (wr_fd == NULL) {
    //     perror("Failed to open the file");
    //     return 1;
    // }
    char character;
    int size;
    while((size = read(rd_fd, &character, sizeof(char))) >0 )
    	write(wr_fd, &character, size);

    close(rd_fd);
    close(wr_fd);
    return 0;
}
