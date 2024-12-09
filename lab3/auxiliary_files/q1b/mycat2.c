#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    char * character;
    int size;
    while((size = read(0, &character, sizeof(character))) > 0)
    	write(1, &character, size);
    return 0;
}
