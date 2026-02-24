#include <windows.h>
#include <stdio.h>
#include <conio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow){
    HWND handle = (void*) hInst;

    // Register the window class.
    LPCSTR CLASS_NAME  = "Sample Window Class";

    WNDCLASSA wc = { sizeof(WNDCLASSA) };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = CLASS_NAME;

    // RegisterClassA(&wc);


    HWND test = FindWindowA(CLASS_NAME, NULL);
    printf("hwnd: %llx\n", test);

    // SetLastError(0);
    handle = CreateWindowExA(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        
        NULL,       // Parent window    
        NULL,       // Menu
        hInst,  // Instance handle
        NULL        // Additional application data
    );
    
    // if(handle == NULL) {
    //     return GetLastError();
    // }
    
    printf("handle: %llx\n", handle);
    // ShowWindow(handle, cmdshow);
    // getch();

    return GetLastError();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_SIZE:
        {
            int width = LOWORD(lParam);  // Macro to get the low-order word.
            int height = HIWORD(lParam); // Macro to get the high-order word.

            // Respond to the message:
            // OnSize(hwnd, (UINT)wParam, width, height);
        }
        break;
    }
    return 0;
}