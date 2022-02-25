#include <stdio.h>
#define MAX 20

typedef struct Graph
{
    int n;
    int a[MAX][MAX];
} DoThi;

typedef struct Stack
{
    int size;   // So luong dinh tim duoc trong chu trinh/ duong di euler
    int a[MAX]; // Luu lai thu tu duong di cua cac dinh trong chu trinh duong di euler
} Stack;

int docFile(char DD[100], DoThi &g)
{
    FILE *f;
    f = fopen(DD, "rt");
    if (f == NULL)
    {
        printf("Khong mo duoc file");
        return 0;
    }
    fscanf(f, "%d", &g.n);
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            fscanf(f, "%d", &g.a[i][j]);
        }
    }
    fclose(f);
    return 1;
}

void printfMatrix(DoThi g)
{
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            printf("%d ", g.a[i][j]);
        }
        printf("\n");
    }
}

void init(Stack &s)
{
    s.size = 0;
}

void doDuLieuVaoStack(Stack &s, int x)
{
    if (s.size + 1 >= MAX)
    {
        printf("Stack day");
        return;
    }
    s.a[s.size] = x; // Day gia tri x vao stack
    s.size++;
}

int timDinhBatDau(DoThi g)
{
    int bac;
    // Kiem tra tat ca cac bac cua do thi (dam bao khong co bac le)
    for (int i = 0; i < g.n; i++)
    {
        bac = 0; //Khoi phuc bac de tim bac cua dinh tiep theo
        for (int j = 0; j < g.n; j++)
        {
            if (g.a[i][j] != 0)
                bac++; // Bac cua dinh i
        }
        if (bac % 2 != 0) // Bac le
            return -1;
    }

    // Lay ra dinh bat ki co bac la chan
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            if (g.a[i][j] != 0)
                return i;
    return -1;
}

void findTour(int i, DoThi &g, Stack &s)
{
    for (int j = 0; j < g.n; j++)
    {
        if (g.a[i][j] != 0)             //Vi do thi vo huong nen kiem tra canh noi
        {
            g.a[i][j] = 0;              //Loai bo canh noi tu dinh i den dinh j ra khoi do thi
            g.a[j][i] = 0;              
            findTour(j, g, s);          //Goi de quy tim duong di tai dinh j
        }
    }
    doDuLieuVaoStack(s, i); // Day dinh i vao stack
}

int kiemTraChuTrinh(DoThi g)
{
    DoThi g1 = g;
    Stack s;
    init(s);
    int dinhBatDau = timDinhBatDau(g1);
    if (dinhBatDau == -1)
        return 0;
    findTour(dinhBatDau, g1, s);
    for (int i = 0; i < g1.n; i++)
        for (int j = 0; j < g1.n; j++)
            if (g1.a[i][j] != 0)
                return 0; // Khong ton tai chu trinh
    if(s.a[0] != s.a[s.size-1])
        return 0; //Khong ton tai chu trinh euler
    printf("Ton tai chu trinh\n");
    printf("Chu trinh euler: ");
    for (int i = s.size - 1; i >= 0; i--)
        printf("%d ", s.a[i] + 1);
    return 1;
}


int main()
{
    DoThi g;
    docFile("kiemtra.txt", g);
    printfMatrix(g);
    printf("\n");
    if (kiemTraChuTrinh(g) == 0)
        printf("Khong ton tai chu trinh euler");
    printf("\n");

    return 0;
}