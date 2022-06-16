#include <iostream>     //библиотеки
#include <string>
#include <fstream>

using namespace std;

ifstream fileIn1;
ifstream fileIn2;
ofstream fileOut;

int readingFile(string &text)
{
    fileIn1.open("original.txt");

    if (fileIn1.fail())
    {
        cout << "ERROR" << endl;
        return 404;
    }
    while (!fileIn1.eof())
    {
        string str;
        getline(fileIn1, str);
        text += str;
        text += '\n';
    }
    fileIn1.close();
}

int translitText(string text,string choice)
{
    string newText;
    for (int i = 0; i < text.length(); i++)
    {
        fileIn2.open("lib.txt");

        if (fileIn2.fail())
        {
            cout << "ERROR" << endl;
            return 404;
        }
        bool kol = false;
        while (!fileIn2.eof())
        {
            bool sym = true;
            string str;
            getline(fileIn2, str);
            if (choice == "1")
            {
                if (text[i] == str[0])
                {
                    kol = true;
                    for (int j = 2; j < str.length(); j++)
                    {
                        newText += str[j];
                    }
                    break;
                }
                else if (text[i] + 32 == (int)str[0])
                {
                    kol = true;
                    for (int j = 2; j < str.length(); j++)
                    {
                        if (j == 2)
                        {
                            newText += str[j] - 32;
                        }
                        else
                        {
                            newText += str[j];
                        }
                    }
                    break;
                }
            }
            else
            {
                if (text[i] == str[2])
                {
                    kol = true;
                    for (int j = 3; j < str.length(); j++)
                    {
                        if (i+j-2 >= text.length())
                        {
                            break;
                        }
                        else if (text[i + j - 2] != str[j])
                        {
                            sym = false;
                            break;
                        }
                    }
                    if (sym == true)
                    {
                        newText += str[0];
                        i += str.length() - 3;
                        break;
                    }
                }
                else if (text[i] +32 == str[2])
                {
                    kol = true;
                    for (int j = 3; j < str.length(); j++)
                    {
                        if (i + j - 2 >= text.length())
                        {
                            break;
                        }
                        else if (text[i + j - 2] +32 != str[j] && text[i + j - 2] != str[j])
                        {
                            sym = false;
                            break;
                        }
                    }
                    if (sym == true)
                    {
                        newText += str[0] - 32;
                        i += str.length() - 3;
                        break;
                    }
                }
            }
        }
        if (kol == false)
        {
            newText += text[i];
        }
        fileIn2.close();
    }
    fileOut.open("final.txt");
    fileOut << newText;
    fileOut.close();

}

void main()
{
    setlocale(LC_ALL, "Russian"); //руссификатор
    string text = "";
    readingFile(text);
    string choice = "";
    while (true)
    {
        cout << "Меню:\n";
        cout << "Переводить с русского на английский (1)\n";
        cout << "Переводить с английского на русский (2)\n";
        cout << "Выберите действие: ";
        cin >> choice;
        if (choice == "1" || choice == "2")
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Ошибка, введите правильное действие: " << endl;
        }
    }
    translitText(text, choice);
}