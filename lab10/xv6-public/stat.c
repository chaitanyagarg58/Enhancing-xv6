#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[]){

    if (argc != 2){
        printf(1, "Usage : %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);

    struct stat *st = malloc(sizeof(struct stat));
    if (fstat(fd, st) < 0){
        printf(1, "Error while Reading Stat\n");
        exit();
    };

    printf(1, "File: %s\n", argv[1]);
    printf(1, "Size: %d bytes\n", st->size);
    printf(1, "Type: %d (T_FILE)\n", st->type);
    printf(1, "Device: %d\n", st->dev);
    printf(1, "Inode number: %d\n", st->ino);
    printf(1, "Links or References: %d\n", st->nlink);

    exit();
    return 0;
}