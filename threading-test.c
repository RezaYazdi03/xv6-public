#include "types.h"
#include "user.h"

lock_t* lk;

void fn(int x) {
    printf(1, "fn %d 1\n", x);
    sleep(100);
    printf(1, "fn %d 2\n", x);
    sleep(100);
    printf(1, "fn %d 3\n", x);
}

int main () {
    lock_init(lk);
    
    // no threading.
    fn(1);
    fn(2);
    
    
    // threading using system call (low level)
    void* stack;
    stack = malloc(4096);
    
    int tid = clone(stack);
    if(tid == 0)
    {
        fn(1);
        exit();
    }
    fn(2);
    join(0);


    // threading using functions (high level)


    exit();
}