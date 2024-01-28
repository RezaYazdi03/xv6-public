#include "types.h"
#include "user.h"

void fn(int x) {
    printf(1, "fn %d 1\n", x);
    sleep(100);
    printf(1, "fn %d 2\n", x);
    sleep(100);
    printf(1, "fn %d 3\n", x);
}

int main () {
    // no threading.
    fn(1);
    fn(2);
    
    exit();
}