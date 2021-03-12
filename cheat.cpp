#include <iostream>
#include <Windows.h>

using namespace std;

int main(){
    int valueToWrite = 0;
    cout << "Enter new value: ";
    cin >> valueToWrite;


    HWND window = FindWindowA(0, "Dead Space");

    if(window == 0){
        cout << "Window not found!" << endl;
    } else {
        DWORD processId;

        GetWindowThreadProcessId(window, &processId);

        HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

        if(!process){
            cout << "Process couldn't be opened" << endl;
        } else {

            int memoryWriteStatus = WriteProcessMemory(process, (LPVOID)0x0474A9A4, &valueToWrite, (DWORD)sizeof(valueToWrite), NULL);

            if(memoryWriteStatus > 0){
                cout << "Data has been writen!" << endl;
            } else {
                cout << "Error!!!" << endl;
            }
        }

        CloseHandle(process);


    }

    cin.get();

    return 0;
}