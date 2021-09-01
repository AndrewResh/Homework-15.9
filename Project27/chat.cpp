#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

class ECloseChat {}; // Класс-исключение закрытия чата

bool login(StringHashTable& auth, StringHashTable& in_chat) // Возвращает true в случае успешной авторизации, false при отказе
{
    string login, password;
    cout << "Введите имя пользователя (пустую строку для отмены): "; 
    while (true)
    {
        getline(cin, login);  
        if (login.empty())
        {
            return false;
        }
        if (!auth.check(login)) 
        { 
            cout << "Пользователь с таким именем не найден. Попробуйте ещё раз: "; 
        }
        else if (in_chat.check(login)) 
        { 
            cout << "Вы уже в чате. Введите имя другого пользователя: "; 
        }
        else 
        {
            cout << "Введите пароль: ";
            getline(cin, password);  
            if (auth.get(login) == auth.hash(password)) // сравнение хеша пароля с хешем введённой строки
            {  
                cout << "Поздравляем, вы добавлены в чат!" << endl;
                in_chat.set(login, 1);  // добавляем пользователя в список авторизованных пользователей
                return true;
            }
            else 
            {
                cout << "Пароль указан неверно. Введите имя пользователя: ";
            }
        }
    }
}

int main()
{

    setlocale(LC_ALL, "Russian");
    cout << "Добро пожаловать в чат!" << endl;

    StringHashTable auth;  // хеш-таблица (логины и пароли)
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

    StringHashTable in_chat;  // хеш-таблица тех, кто в чате
    int user_count = 0;  // кол-во пользователей чата
    string s;
    
    try 
    {
        while (true) 
        {
            if (user_count >= 4) // ограничение по количеству пользователей
            {
                cout << "Слишком много пользователей!" << endl;
                throw ECloseChat();
            }
            cout << endl;
            if (!login(auth, in_chat)) // залогинить пользователя
            {  
                throw ECloseChat();  // вызвать исключение при отказе (закрыть чат)
            }
            cout << endl;
            ++user_count;  // увеличиваем кол-во пользователей чата
            cout << "Пользователей в чате: " << user_count << "." << endl;
            if (user_count < 2) // новая авторизация, если пользователей меньше 2-х
            { 
                continue; 
            }  
            cout << "Приятного общения!" << endl;
            cout << "Для добавления ещё одного собеседника введите 1, для выхода - 0: ";
            while (true) 
            {
                getline(cin, s); // добавить собеседника
                if (s == "1") 
                { 
                    break; 
                }  
                if (s == "0")  // закрыть чат (исключение)
                { 
                    throw ECloseChat(); 
                }  
                cout << "Неверный ввод. Попробуйте ещё раз: ";
            }
        }
    }
    catch (ECloseChat) // завершить чат в случае исключения
    {  
        cout << endl << "Диалог завершён. До свидания!" << endl;
    }
}