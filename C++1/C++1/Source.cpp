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

int translitText(string text)
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
            string str;
            getline(fileIn2, str);
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
    cout << text;
    translitText(text);
}