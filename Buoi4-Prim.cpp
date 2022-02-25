#include <stdio.h>
#define MAX 20

typedef struct Graph
{
    int n;
    int a[MAX][MAX];
} DoThi;

typedef struct EDGE
{
    int x, y, value;
} Canh;

Canh T[MAX];

int ChuaXet[MAX];

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

int XetLienThong(DoThi g)
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
    return (SoThanhPhanLT == 1);
}

void Prim(DoThi g)
{
    if (XetLienThong(g) == 0)
        printf("\nDo thi khong lien thong nen khong co cay khung");
    int nT = 0;
    for (int i = 0; i < g.n - 1; i++)
    {
        ChuaXet[i] = 0;
    }
    ChuaXet[0] = 1;
    while (nT < g.n)
    {
        Canh canhMin;
        int min = 100;
        for (int i = 0; i < g.n; i++)
        {
            if (ChuaXet[i] == 1)
            {
                for (int j = 0; j < g.n; j++)
                {
                    if (ChuaXet[j] == 0 && g.a[i][j] < min && g.a[i][j] != 0)
                    {
                        canhMin.x = i;
                        canhMin.y = j;
                        canhMin.value = g.a[i][j];
                        min = g.a[i][j];
                    }
                }
            }
        }
        T[nT++] = canhMin;
        ChuaXet[canhMin.y] = 1;
    }
    int tongCayKhung = 0;
    printf("Cay khung nho nhat la: ");
    for (int i = 0; i < nT - 1; i++)
    {
        printf("\n(%d,%d): %d", T[i].x, T[i].y, T[i].value);
        tongCayKhung += T[i].value;
    }
    printf("\nTong trong so cay khung la: %d", tongCayKhung);
}

int main()
{
    DoThi g;
    docFile("kiemtra.txt", g);
    printf("Ma tran do thi: \n");
    printfMatrix(g);
    printf("\n");
    Prim(g);
    return 0;
}