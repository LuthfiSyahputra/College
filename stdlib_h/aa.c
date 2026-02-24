#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    HINSTANCE hinst = GetModuleHandleA(NULL);
    printf("HINSTANCE: %llx  | %llx\n", hInst, hinst);
    return MessageBox(NULL, "hello, world", "caption", 0);
}

