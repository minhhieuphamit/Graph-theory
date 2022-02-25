#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct Graph
{
    int n;
    int a[MAX][MAX];
} DoThi;

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

int ChuaXet[MAX];
int LuuVet[MAX];

void DFS(int v, DoThi g)
{
    ChuaXet[v] = 1;
    
    for (int i = 0; i < g.n; i++)
    {
        if (g.a[v][i] != 0 && ChuaXet[i] == 0)
        {
            LuuVet[i] = v;
            DFS(i, g);
        }
    }
}

void duyetDFS(int dinhBatDau, int dinhKetThuc, DoThi g)
{
    for (int i = 0; i < g.n; i++)
    {
        ChuaXet[i] = 0;
        LuuVet[i] = -1;
    }
    DFS(dinhBatDau, g);
    if (ChuaXet[dinhKetThuc] == 1)
    {
        printf("Duong di DFS tu dinh %d den dinh %d la: \n", dinhBatDau, dinhKetThuc);
        int i = dinhKetThuc;
        printf("%d ", i);
        while (i != dinhBatDau)
        {
            printf("%d ", LuuVet[i]);
            i = LuuVet[i];
        }
    }
}
    
int main()
{
    DoThi g;
    docFile("kiemtra.txt", g);
    printfMatrix(g);
    duyetDFS(0, 5, g);
}