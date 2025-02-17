#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_clone(void)
{
  void (*fn)(int *);
  int* arg;
  void *stack;

  if(argptr(0, (char**)&fn, 0) < 0)
    return -1;
  if(argptr(1, (char**)(&arg), 4) < 0)
    return -1;
  if(argptr(2, (char**)(&stack), 4) < 0)
    return -1;

  return clone(fn, arg, stack);
}

int sys_join(void) 
{
  return join();
}

int
sys_semaphore_init(void)
{
  int v;

  if(argint(0, &v) < 0)
    return -1;

  return semaphore_init(v);
}

int
sys_semaphore_destroy(void)
{
  int s;

  if(argint(0, &s) < 0)
    return -1;

  return semaphore_destroy(s);
}

int
sys_semaphore_down(void)
{
  int s;

  if(argint(0, &s) < 0)
    return -1;

  return semaphore_down(s);
}

int
sys_semaphore_up(void)
{
  int s;

  if(argint(0, &s) < 0)
    return -1;

  return semaphore_up(s);
}