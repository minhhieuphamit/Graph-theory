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

int KiemTraHopLe(DoThi g)
{
    int i;
    for (i = 0; i < g.n; i++)
    {
        if (g.a[i][i] != 0)
            return 0;
    }
    return 1;
}

int kiemTraDoThiHuong(DoThi g)
{
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            if (g.a[i][j] != g.a[j][i])
                return 0;
    return 1;
}


int main()
{
    DoThi g;
    docFile("test4.txt", g);
    printf("\nSo dinh cua do thi la: %d", g.n);
    printf("\nMa tran do thi:\n");
    printfMatrix(g);

    if (KiemTraHopLe(g) == 0)
        printf("\nDo thi khong hop le");
    else
        printf("\nDo thi hop le");

    if (kiemTraDoThiHuong(g) == 0)
        printf("\nDo thi vo huong");
    else
        printf("\nDo thi co huong");

    return 0;
}