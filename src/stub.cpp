
#include <cstdint>
#include <cstddef>

extern "C" void _exit(int status) {
    while (1) {

    }
}

extern "C" int _kill(int pid, int sig) {
    return -1;  
}

extern "C" int _getpid(void) {
    return 1;  
}

extern "C" void* _sbrk(ptrdiff_t increment) {
    static char heap[1024]; 
    static char* heap_ptr = heap;

    if (heap_ptr + increment > heap + sizeof(heap)) {
        return (void*)-1; 
    }

    char* prev_heap_ptr = heap_ptr;
    heap_ptr += increment;
    return prev_heap_ptr;
}