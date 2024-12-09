#include <stdio.h>
#include <unistd.h>

int main() {
    FILE *rd_fd = fopen("in.txt", "r");
    if (rd_fd == NULL) {
        perror("Failed to open the file");
        return 1;
    }
    // Use "chmod u+w ." in the current directory
    // If the program is not able to create file
    FILE *wr_fd = fopen("out.txt", "w");
    if (wr_fd == NULL) {
        perror("Failed to open the file");
        return 1;
    }
    char character;
    while(fread(&character, sizeof(char), 1, rd_fd) >0 )
    	fwrite(&character, sizeof(char), 1, wr_fd);

    fclose(rd_fd);
    fclose(wr_fd);
    return 0;
}
