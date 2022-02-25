#include <stdio.h>
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

void CacDinhLienThong(DoThi g, int nhan[MAX], int i)
{
    for (int j = 0; j < g.n; j++)
    {
        if (g.a[i][j] != 0 && nhan[j] != nhan[i])
        {
            nhan[j] = nhan[i];
            CacDinhLienThong(g, nhan, j);
        }
    }
}

void XetLienThong(DoThi g)
{

    int Nhan[MAX];
    int i;
    for (i = 0; i < g.n; i++)
        Nhan[i] = 0;
    int SoThanhPhanLT = 0;
    for (i = 0; i < g.n; i++)
    {
        if (Nhan[i] == 0)
        {
            SoThanhPhanLT++;
            Nhan[i] = SoThanhPhanLT;
        }
        if (Nhan[i] != 0)
            CacDinhLienThong(g, Nhan, i);
    }
    printf("So thanh phan lien thong la %d\n", SoThanhPhanLT);
    for (i = 1; i <= SoThanhPhanLT; i++)
    {
        printf("Thanh phan lien thong thu %d gom cac dinh: ", i);
        for (int j = 0; j < g.n; j++)
        {
            if (Nhan[j] == i)
                printf(" %d ", j + 1);
        }
        printf("\n");
    }
}

int main()
{
    DoThi g;
    docFile("test3.txt", g);
    printfMatrix(g);
    printf("\n");
    XetLienThong(g);

    return 0;
}