#include <windows.h>
#include <pthread.h>
#include <stdio.h>

void* run(void*) {
    MessageBoxA(NULL, "test", "test", 0);

    return NULL;
}

int main() {

    pthread_t pthread;
    pthread_create(&pthread, NULL, run, NULL);

    Sleep(1000);

    return 0;

}
