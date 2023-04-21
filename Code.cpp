//���������������� ��������� �����, ��������������� � �������
//���������������� ������� ���������.
#include <iostream>
#include <conio.h>
#include <windows.h>
#define TRUE 1
#define FALSE 0
#define XRY 4  //���������� ������ �����.

using namespace std;

typedef int Boolean;
typedef struct zveno* svqz;
typedef struct zveno
{
    int Key;  // ������� �����.
    svqz Up;  // ��������� �� ������� �������.
    svqz Sled;// ��������� �� ��������� ������� �������.
};

class Spisok
{
private:
    svqz Beg[XRY + 1]; //������ ���������� �� �������.
    void Add_Ver(int);
    int Find(int, int, svqz*);
    void Add_duga(int, int);
    void Make(int, int);
    void Delinenok(int, int);
    void Del_Duga(int, int);
    void Del_Ver(int);
    int Find_Color(int, int, svqz*);
public:
    Spisok();
    void Init_Graph();
    void Make_Graph();
    void Print_Graph();
    void Color();
    void Print_Color();
};

int main()
{
    SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
    Spisok A;

    //������������� �����.
    A.Init_Graph();
    //���������� �����.
    A.Make_Graph();
    //����� �����.
    A.Print_Graph();
    _getch();
    //���������������� ��������� �����, ���������������
    //����������������� �������� ���������.
    A.Color();
    A.Print_Color();
    _getch();
}

Spisok::Spisok()
{
    for (int i = 0; i <= XRY; Beg[i++] = NULL);
}

void Spisok::Add_Ver(int x)
//������� �������� ������� x.
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = NULL;
    Beg[x] = Ukaz;
}

void Spisok::Init_Graph()
//������� ������������� ���������������� ������� ���������.
{
    for (int i = 1; i <= XRY; i++) Add_Ver(i);
}

int Spisok::Find(int x, int y, svqz* UkZv)
//������� �������� ��������� ������ y � x. ������� ����������
//TRUE, ����  ������� x ������ � �������� y. ��������� *UkZv,
//���������� ��������� �� ����� y � ������  ��������� x. ����
//������� x �� ������ � �������� y, �� UkZv ���� NULL.
{
    svqz Ukaz;

    Ukaz = Beg[x]->Sled;
    while (Ukaz != NULL && Ukaz->Key != y)
        Ukaz = Ukaz->Sled;
    *UkZv = Ukaz;
    return  (Ukaz != NULL);
}

void Spisok::Add_duga(int x, int y)
//������� �������� ���� (x,y).
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = Beg[x]->Sled; Ukaz->Key = y;
    Beg[x]->Sled = Ukaz;
}

void Spisok::Make(int x, int y)
//������� �������� ����� {x,y}.
{
    svqz Ukaz;

    if (!Find(x, y, &Ukaz))
    {
        Add_duga(x, y);
        if (x != y) Add_duga(y, x);
        Beg[x]->Sled->Up = Beg[y];
        Beg[y]->Sled->Up = Beg[x];
    }
}

void Spisok::Make_Graph()
//������� ���������� ���������������� ������� ���������.
{
    int f;

    for (int i = 1; i <= XRY; i++)
    {
        cout << "������� �������, ������� � " << i << "-� ��������: ";
        cin >> f;
        while (f != 0)
        {
            Make(i, f);
            cout << " ";
            cin >> f;
        }
        cout << endl;
    }
}

void Spisok::Delinenok(int x, int y)
//������� �������� ���� (x,y).
{
    svqz Ukaz;
    svqz Ukazlenok;

    Ukazlenok = Beg[x]; Ukaz = Beg[x]->Sled;
    while (Ukaz != NULL && Ukaz->Key != y)
    {
        Ukazlenok = Ukaz; Ukaz = Ukaz->Sled;
    }
    if (Ukaz != NULL)
    {
        Ukazlenok->Sled = Ukaz->Sled;
        delete Ukaz;
    }
}

void Spisok::Del_Duga(int x, int y)
//������� �������� ����� {x,y}.
{
    Delinenok(x, y); Delinenok(y, x);
}

void Spisok::Del_Ver(int x)
//������� �������� ������� x.
{
    svqz Ukaz;
    svqz Ukazlenok;

    for (int i = 1; i <= XRY; i++) Delinenok(i, x);
    Ukaz = Beg[x]; Beg[x] = NULL;
    while (Ukaz != NULL)
    {
        Ukazlenok = Ukaz->Sled;
        delete Ukaz; Ukaz = Ukazlenok;
    }
}

void Spisok::Print_Graph()
//������� ������ ����p������ ����������������
//������� ���������.
{
    svqz UkZv;

    for (int i = 1; i <= XRY; i++)
    {
        if (Beg[i] != NULL)
        {
            UkZv = Beg[i]->Sled;
            cout << i << " - ";
            while (UkZv != NULL)
            {
                cout << " " << UkZv->Key;
                UkZv = UkZv->Sled;
            }
        }
        cout << endl;
    }
}

int Spisok::Find_Color(int x, int c, svqz* UkZv)
//�������  ��������� ����������� ��������� �������  x ������ c.
//�������  ���������� TRUE, ���� �������  x  �����  ����������.
//��������� *UkZv, ���������� ��������� �� �������, ������� � x
//� ������������ ������ c. ���� ������� x ����� ����������, ��
//*UkZv ���� NULL.
{
    int i = 1;

    while (!(Find(x, i, &(*UkZv)) &&
        Beg[i]->Key == c) &&
        i != x) i++;
    return (i == x);
}

void Spisok::Color()
//������� ���������������� ��������� �����, ���������
//����������������� �������� ��������� Beg.
{
    int i = 1;
    int c = 1;
    svqz UkZv;

    while (Beg[i] == NULL && i <= XRY) i++;
    if (i != XRY)
    {
        Beg[i]->Key = c;
        i++;
        while (i <= XRY)
            if (Beg[i] != NULL)
            {
                c = 1;
                while (!Find_Color(i, c, &UkZv)) c++;
                Beg[i]->Key = c; i++;
            }
            else  i++;
    }
    else  cout << "���� �����������!";
}

void Spisok::Print_Color()
//������� ������ ��������� �����, ���������
//����������������� �������� ��������� Beg.
{
    for (int i = 1; i <= XRY; i++)
        if (Beg[i] != NULL)
            cout << " Color " << i << " - " << Beg[i]->Key << endl;
}