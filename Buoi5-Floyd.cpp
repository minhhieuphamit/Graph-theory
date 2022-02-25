#include <stdio.h>
#define MAX 20
#define VOCUC 1000

typedef struct Graph
{
    int n;
    int a[MAX][MAX];
} DoThi;

int sau_Nut[MAX][MAX];
int L[MAX][MAX];

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

void Floyd(DoThi g)
{
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            if (g.a[i][j] > 0)
            {
                sau_Nut[i][j] = j;
                L[i][j] = g.a[i][j];
            }
            else
            {
                sau_Nut[i][j] = -1;
                L[i][j] = VOCUC;
            }
        }
    }
    for (int k = 0; k < g.n; k++)
    {
        for (int i = 0; i < g.n; i++)
        {
            for (int j = 0; j < g.n; j++)
            {
                if (L[i][j] > L[i][k] + L[k][j])
                {
                    L[i][j] = L[i][k] + L[k][j];
                    sau_Nut[i][j] = sau_Nut[i][k];
                }
            }
        }
    }
    int start, finish;
    printf("Nhap dinh bat dau: ");
    scanf("%d", &start);
    printf("Nhap dinh ket thuc: ");
    scanf("%d", &finish);
    if (sau_Nut[start][finish] == -1)
    {
        printf("Khong co duong di tu %d den %d", start, finish);
    }
    else
    {
        printf("Duong di tu %d den %d la: ", start, finish);
        int i = start;
        printf("%d", start);
        while (sau_Nut[i][finish] != finish)
        {
            i = sau_Nut[i][finish];
            printf(" --> %d", i);
        }
        printf(" --> %d", finish);
        printf("\n\t\nDo dai duong di la: %d", L[start][finish]);
    }
}

int main()
{
    DoThi g;
    docFile("test10.txt", g);
    printf("Ma tran do thi: \n");
    printfMatrix(g);
    printf("\n");
    Floyd(g);
    return 0;
}
