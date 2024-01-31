#include "types.h"
#include "user.h"

lock_t* lk;

void fn(int x, int y) {
    // printf(1, "--%d %d--\n", x, y);

    if (y) lock_acquire(lk);
    printf(1, "fn %d 1\n", x);
    if (y) lock_release(lk);

    if (y) lock_acquire(lk);
    printf(1, "fn %d 2\n", x);
    if (y) lock_release(lk);

    if (y) lock_acquire(lk);
    printf(1, "fn %d 3\n", x);
    if (y) lock_release(lk);

    if (y) lock_acquire(lk);
    printf(1, "fn %d 4\n", x);
    if (y) lock_release(lk);

    if (y) lock_acquire(lk);
    printf(1, "fn %d 5\n", x);
    if (y) lock_release(lk);
}

void fn_wrapper(void *_x, void *_y) {
    // printf(1, "%d %d %d %d\n", _x, _x, *(int*)_x, *(int*)_y);
    fn(*(int *)_x, *(int *)_y);
}

int main () {
    lock_init(lk);
    
    // no threading.
    fn(1, 0);
    fn(2, 0);
    
    
    // threading using system call (low level)
    void* stack;
    stack = malloc(4096);
    
    int tid = clone(stack);
    if(tid == 0)
    {
        fn(1, 0);
        exit();
    }
    fn(2, 0);
    join(0);
    free(stack); // manually prevent memory leak
    fn(3, 0);


    int v0 = 0, v1 = 1, v2 = 2;
    // threading using wrapper functions (high level) (without lock. its mess)
    thread_create(&fn_wrapper, (void *)&v1, (void *)&v0);
    thread_create(&fn_wrapper, (void *)&v2, (void *)&v0);
    thread_join();
    thread_join();


    // threading using wrapper functions (high level) and loock for printer
    thread_create(&fn_wrapper, (void *)&v1, (void *)&v1);
    thread_create(&fn_wrapper, (void *)&v2, (void *)&v1);
    thread_join();
    thread_join();



    exit();
}
