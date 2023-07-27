// testLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>

typedef int (*func1)(DWORD);

int main_test()
{
    HINSTANCE hDLL = LoadLibrary(L"fdLib.dll");
    if (hDLL != NULL)
    {
        func1 p = (func1)GetProcAddress(hDLL, "func1");
        if (p != NULL) {
            std::cout << "Load DLL successfully, and func1 return " << p(1) << std::endl;
        }
    }
    return 0;
    //std::cout << "Hello World!\n";
}

int main() 
{
    HANDLE hFile = CreateFile(L"shared_memory", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        HANDLE h = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, MAX_PATH, L"shared_memory");
        if (h != NULL) {
            LPVOID p = MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, MAX_PATH);
            memcpy(p, "Hello, World", 100);
            std::cout << "Press any key to terminate...";
            std::cin.get();
            UnmapViewOfFile(p);
            CloseHandle(h);
        }
        CloseHandle(hFile);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
