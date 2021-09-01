#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

class ECloseChat {}; // �����-���������� �������� ����

bool login(StringHashTable& auth, StringHashTable& in_chat) // ���������� true � ������ �������� �����������, false ��� ������
{
    string login, password;
    cout << "������� ��� ������������ (������ ������ ��� ������): "; 
    while (true)
    {
        getline(cin, login);  
        if (login.empty())
        {
            return false;
        }
        if (!auth.check(login)) 
        { 
            cout << "������������ � ����� ������ �� ������. ���������� ��� ���: "; 
        }
        else if (in_chat.check(login)) 
        { 
            cout << "�� ��� � ����. ������� ��� ������� ������������: "; 
        }
        else 
        {
            cout << "������� ������: ";
            getline(cin, password);  
            if (auth.get(login) == auth.hash(password)) // ��������� ���� ������ � ����� �������� ������
            {  
                cout << "�����������, �� ��������� � ���!" << endl;
                in_chat.set(login, 1);  // ��������� ������������ � ������ �������������� �������������
                return true;
            }
            else 
            {
                cout << "������ ������ �������. ������� ��� ������������: ";
            }
        }
    }
}

int main()
{

    setlocale(LC_ALL, "Russian");
    cout << "����� ���������� � ���!" << endl;

    StringHashTable auth;  // ���-������� (������ � ������)
    auth.set("misha", auth.hash("MIHA90"));
    auth.set("masha", auth.hash("Mashulya_1995"));
    auth.set("kolya", auth.hash("KOLYAmba"));
    auth.set("olya", auth.hash("Ola-la"));
    auth.set("anton", auth.hash("12345"));
    auth.set("sergey", auth.hash("SERG87"));
    auth.set("elena", auth.hash("Lenchik@"));
    auth.set("dima", auth.hash("DimoN"));
    auth.set("sveta", auth.hash("svetic!"));
    auth.set("irina", auth.hash("irishka03"));

    StringHashTable in_chat;  // ���-������� ���, ��� � ����
    int user_count = 0;  // ���-�� ������������� ����
    string s;
    
    try 
    {
        while (true) 
        {
            if (user_count >= 4) // ����������� �� ���������� �������������
            {
                cout << "������� ����� �������������!" << endl;
                throw ECloseChat();
            }
            cout << endl;
            if (!login(auth, in_chat)) // ���������� ������������
            {  
                throw ECloseChat();  // ������� ���������� ��� ������ (������� ���)
            }
            cout << endl;
            ++user_count;  // ����������� ���-�� ������������� ����
            cout << "������������� � ����: " << user_count << "." << endl;
            if (user_count < 2) // ����� �����������, ���� ������������� ������ 2-�
            { 
                continue; 
            }  
            cout << "��������� �������!" << endl;
            cout << "��� ���������� ��� ������ ����������� ������� 1, ��� ������ - 0: ";
            while (true) 
            {
                getline(cin, s); // �������� �����������
                if (s == "1") 
                { 
                    break; 
                }  
                if (s == "0")  // ������� ��� (����������)
                { 
                    throw ECloseChat(); 
                }  
                cout << "�������� ����. ���������� ��� ���: ";
            }
        }
    }
    catch (ECloseChat) // ��������� ��� � ������ ����������
    {  
        cout << endl << "������ ��������. �� ��������!" << endl;
    }
}