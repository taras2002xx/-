//Последовательная раскраска графа, представленного с помощью
//модифицированных списков смежности.
#include <iostream>
#include <conio.h>
#include <windows.h>
#define TRUE 1
#define FALSE 0
#define XRY 4  //Количество вершин графа.

using namespace std;

typedef int Boolean;
typedef struct zveno* svqz;
typedef struct zveno
{
    int Key;  // Вершина графа.
    svqz Up;  // Указатель на смежную вершину.
    svqz Sled;// Указатель на следующую смежную вершину.
};

class Spisok
{
private:
    svqz Beg[XRY + 1]; //Массив указателей на вершины.
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
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
    Spisok A;

    //Инициализация графа.
    A.Init_Graph();
    //Построение графа.
    A.Make_Graph();
    //Вывод графа.
    A.Print_Graph();
    _getch();
    //Последовательная раскраска графа, представленного
    //модифицированными списками смежности.
    A.Color();
    A.Print_Color();
    _getch();
}

Spisok::Spisok()
{
    for (int i = 0; i <= XRY; Beg[i++] = NULL);
}

void Spisok::Add_Ver(int x)
//Функция создания вершины x.
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = NULL;
    Beg[x] = Ukaz;
}

void Spisok::Init_Graph()
//Функция инициализации модифицированных списков смежности.
{
    for (int i = 1; i <= XRY; i++) Add_Ver(i);
}

int Spisok::Find(int x, int y, svqz* UkZv)
//Функция проверки смежности вершин y и x. Функция возвращает
//TRUE, если  вершина x смежна с вершиной y. Указатель *UkZv,
//возвращает указатель на место y в списке  смежности x. Если
//вершина x не смежна с вершиной y, то UkZv есть NULL.
{
    svqz Ukaz;

    Ukaz = Beg[x]->Sled;
    while (Ukaz != NULL && Ukaz->Key != y)
        Ukaz = Ukaz->Sled;
    *UkZv = Ukaz;
    return  (Ukaz != NULL);
}

void Spisok::Add_duga(int x, int y)
//Функция создания дуги (x,y).
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = Beg[x]->Sled; Ukaz->Key = y;
    Beg[x]->Sled = Ukaz;
}

void Spisok::Make(int x, int y)
//Функция создания ребра {x,y}.
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
//Функция построения модифицированных списков смежности.
{
    int f;

    for (int i = 1; i <= XRY; i++)
    {
        cout << "Введите вершины, смежные с " << i << "-й вершиной: ";
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
//Функция удаления дуги (x,y).
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
//Функция удаления ребра {x,y}.
{
    Delinenok(x, y); Delinenok(y, x);
}

void Spisok::Del_Ver(int x)
//Функция удаления вершины x.
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
//Функция вывода содеpжимого модифицированных
//списков смежности.
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
//Функция  выявления возможности раскраски вершины  x цветом c.
//Функция  возвращает TRUE, если вершину  x  можно  раскрасить.
//Указатель *UkZv, возвращает указатель на вершину, смежную с x
//и раскрашенную цветом c. Если вершину x можно раскрасить, то
//*UkZv есть NULL.
{
    int i = 1;

    while (!(Find(x, i, &(*UkZv)) &&
        Beg[i]->Key == c) &&
        i != x) i++;
    return (i == x);
}

void Spisok::Color()
//Функция последовательной раскраски графа, заданного
//модифицированными списками смежности Beg.
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
    else  cout << "Граф отсутствует!";
}

void Spisok::Print_Color()
//Функция вывода раскраски графа, заданного
//модифицированными списками смежности Beg.
{
    for (int i = 1; i <= XRY; i++)
        if (Beg[i] != NULL)
            cout << " Color " << i << " - " << Beg[i]->Key << endl;
}