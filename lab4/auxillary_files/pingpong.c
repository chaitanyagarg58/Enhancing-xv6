#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512

void ping_pong(int fd) 
{
    // ------------------------- Write your code here -------------------------
    char c;
    int state = 0; // 0->nothing, 1->"p", 2->"pi", 3->"pin"
    while (read(fd, &c, sizeof(c)) > 0){
        if (state == 0){
            if (c == 'p') state = 1;
        }
        else if (state == 1){
            if (c == 'i') state = 2;
            else if (c != 'p') state = 0;
        }
        else if (state == 2){
            if (c == 'n') state = 3;
            else if (c == 'p') state = 1;
            else state = 0;
        }
        else{
            if (c == 'g'){
                printf(1, "pong\n");
                state = 0;
            }
            else if (c == 'p') state = 1;
            else state = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
