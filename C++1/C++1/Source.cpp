#include <iostream>     //библиотеки
#include <string>
#include <fstream>

using namespace std;

ifstream fileIn1;
ifstream fileIn2;
ofstream fileOut;

int readingFile(string &text)
{
    //Считываем с файла текст
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
    string newText; //новый текст уже с транслитом
    for (int i = 0; i < text.length(); i++) //i - номер символа текста
    {
        fileIn2.open("lib.txt"); //открываем наш файлик

        if (fileIn2.fail()) //проверка на открытие файла
        {
            cout << "ERROR" << endl;
            return 404;
        }
        bool kol = false; //проверка на наличие элемента из библиотеки
        while (!fileIn2.eof()) //пока файл считываеться
        {
            bool sym = true;
            string str; //строка библиотеки
            getline(fileIn2, str);
            if (choice == "1") //если выбор русского в английский
            {
                //если символ текста = символу в библиотеке
                if (text[i] == str[0])
                {
                    kol = true; //отмечаем что элемент был найден
                    for (int j = 2; j < str.length(); j++) //j - символ английского элемента, и пока строка не закончиться
                    {
                        newText += str[j]; //к новому тексту будет добавляться английский символ
                    }
                    break;
                }
                //Если буква начинаеться с большой буквы
                else if (text[i] + 32 == (int)str[0])
                {
                    kol = true;
                    for (int j = 2; j < str.length(); j++)
                    {
                        if (j == 2)
                        {
                            newText += str[j] - 32; //1 символ делаем больший
                        }
                        else
                        {
                            newText += str[j]; //все остальные маленькими
                        }
                    }
                    break;
                }
            }
            //если выбор с английского в русский
            else
            {
                //если 1 символ английского языка = символу текста
                if (text[i] == str[2])
                {
                    kol = true;
                    for (int j = 3; j < str.length(); j++) //j - символ английского алфавита, начиная со 2 буквы, если она там есть
                    {
                        if (i+j-2 >= text.length()) //проверяем, что бы мы не вышли за пределы текста
                        {
                            break;
                        }
                        else if (text[i + j - 2] != str[j]) //проверяем, что бы следующая буква совпадала со следующей буквой текста
                        {
                            //если она не совпадает, тогда символы разные, поэтому записываться не будет
                            sym = false;
                            break;
                        }
                    }
                    //если символы сошлись, тогда записываем в новый текст и останавливаеми поиск
                    if (sym == true)
                    {
                        newText += str[0];
                        i += str.length() - 3;
                        break;
                    }
                }
                //тоже самое, только с большим регистром
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
        //если среди тех символов совсем ничего не совпало
        //мы добавим его в новый файл без изменений
        if (kol == false)
        {
            newText += text[i];
        }
        fileIn2.close(); //закрываем файл
    }
    //в самом конце передаем значения нового текста
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