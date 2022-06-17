#include <iostream>     //����������
#include <string>
#include <fstream>

using namespace std;

ifstream fileIn1;
ifstream fileIn2;
ofstream fileOut;

//��� ��������� �����
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
    string newText; //����� �����
    for (int i = 0; i < text.length(); i++) //i - ����� ������� ������
    {
        fileIn2.open("BadWords.txt"); //��������� ��� ������

        if (fileIn2.fail()) //�������� �� �������� �����
        {
            cout << "ERROR" << endl;
            return 404;
        }
        bool sym = true; 
        while (!fileIn2.eof()) //���� ���� ���������
        {
            string str = "";
            getline(fileIn2, str); //��������� ��������� �����
            for (int j = 0; j < str.length(); j++) //j - ������ ���������� �����
            {
                //���� �� ����� �� ������� ������
                if (i + j >= text.length())
                {
                    sym = false;
                    break;
                }
                //���� ������� �����������
                else if (text[i+j] != str[j] && text[i + j]+32 != str[j])
                {
                    sym = true; //������� ������������
                    break;
                }
                //����� ������� ������� � ��� ����������
                sym = false;
            }
            //���� ������� ����������, �� ���������� ������� �� 1 �������
            if (sym == false)
            {
                while (text[i] != ' ')
                {
                    i++;
                }
            }
        }
        //���� ������� ������, �� ��������� ������ � ��������� � ����������
        if (sym == true)
        {
            newText += text[i];
        }
        //��������� ����
        fileIn2.close();
    }
    //� ����� ����� ��������� ����� ����� � ����
    fileOut.open("final.txt");
    fileOut << newText;
    fileOut.close();
}

void main()
{
    string str = "";
    readingFile(str);
    removeBadWords(str);
    setlocale(LC_ALL, "Russian"); //������������
}