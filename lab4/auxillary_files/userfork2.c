#include "types.h"

#include "stat.h"

#include "user.h"

 

int main(int argc, char *argv[])

{

    if (argc < 2)

    {

        printf(1, "Usage: %s <program> [arguments...]\n", argv[0]);

        exit();

    }

    // ----------------------- Write the implementation of fork2() on trap number 65 in kernel -----------------------

    // It should behave as a normal fork() system call

    int pid = fork2();

    if (pid < 0)

    {

        printf(1, "Fork 2 failed\n");

        exit();

    }

 

    else if (pid == 0)

    {

        // Child process

        exec(argv[1], argv + 1); // Execute the specified program

        printf(1, "Failed to execute %s\n", argv[1]);

        exit();

    }

    else

    {

        int wpid;

        do

        {

            wpid = wait(); // Wait for the child process to complete

        } while (wpid != pid);

    }

    exit();
}