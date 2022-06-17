#include <iostream>     //библиотеки
#include <string>
#include <fstream>

using namespace std;

ifstream fileIn1;
ifstream fileIn2;
ofstream fileOut;

//тут считываем текст
int readingFile(string& text)
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

int removeBadWords(string text)
{
    string newText; //новый текст
    for (int i = 0; i < text.length(); i++) //i - номер символа текста
    {
        fileIn2.open("BadWords.txt"); //открываем наш файлик

        if (fileIn2.fail()) //проверка на открытие файла
        {
            cout << "ERROR" << endl;
            return 404;
        }
        bool sym = true; 
        while (!fileIn2.eof()) //пока файл читаеться
        {
            string str = "";
            getline(fileIn2, str); //считываем запретное слово
            for (int j = 0; j < str.length(); j++) //j - символ запретного слова
            {
                //если мы вышли за пределы текста
                if (i + j >= text.length())
                {
                    sym = false;
                    break;
                }
                //если символы несовпадают
                else if (text[i+j] != str[j] && text[i + j]+32 != str[j])
                {
                    sym = true; //символы неодинаковые
                    break;
                }
                //иначе символы совпали и они одинаковые
                sym = false;
            }
            //если символы одинаковые, то пропускаем символы до 1 пробела
            if (sym == false)
            {
                while (text[i] != ' ')
                {
                    i++;
                }
            }
        }
        //если символы разные, то добавляем символ и переходит к следующему
        if (sym == true)
        {
            newText += text[i];
        }
        //закрываем файл
        fileIn2.close();
    }
    //в самом конце переносим новый текст в файл
    fileOut.open("final.txt");
    fileOut << newText;
    fileOut.close();
}

void main()
{
    string str = "";
    readingFile(str);
    removeBadWords(str);
    setlocale(LC_ALL, "Russian"); //руссификатор
}