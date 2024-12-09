#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int shm_key = 10;
    char *data = "Systems are vital to WORLD PEACE !!";
    uint shm_addr = create_shm(shm_key);
    printf(1, "Creating Shared Memory with key %d\n", shm_key);
    char *shm = (char *)shm_addr;
    printf(1, "Writing Data Into Shared Memory From Parent: %s\n", data);
    strcpy(shm, data);
    int id = fork();
    if (id < 0)
        exit();
    if (id == 0)
    {
        printf(1, "Accessing Shared Memory In Child Process: %s\n", (char *)attach_shm(shm_key));
        if (detach_shm(shm_key))
            printf(1, "Failure\n");
        else
        {
            printf(1, "Detached Shared Memory From Child Address Space\n", shm_key);
        }
    }
    else
    {
        wait();
        if (destroy_shm(shm_key))
            printf(1, "Failure\n");
        else
        {
            printf(1, "Destoryed Shared Memory From Parent\n", shm_key);
        }
    }
    exit();
}
