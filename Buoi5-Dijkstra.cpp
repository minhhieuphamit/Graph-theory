#include <stdio.h>
#define MAX 20
#define VOCUC 1000

typedef struct Graph
{
    int n;
    int a[MAX][MAX];
} DoThi;

int chuaXet[MAX];
int luuVet[MAX];
int doDaiDuongDiToi[MAX];

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

// Ham tim dinh chua xet co gia tri duong di nho nhat
int timDuongDiNhoNhat(DoThi g)
{
    int temp = -1;
    int p = VOCUC;
    for (int i = 0; i < g.n; i++)
    {
        if (chuaXet[i] == 0 && doDaiDuongDiToi[i] < p)
        {
            p = doDaiDuongDiToi[i];
            temp = i;
        }
    }
    return temp;
}

void capNhatDuongDi(int u, DoThi g)
{
    chuaXet[u] = 1; // Dinh u da da xet
    for (int i = 0; i < g.n; i++)
    {
        if (chuaXet[i] == 0 && g.a[u][i] > 0 && g.a[u][i] < VOCUC)
        {
            if (doDaiDuongDiToi[i] > doDaiDuongDiToi[u] + g.a[u][i])
            {
                doDaiDuongDiToi[i] = doDaiDuongDiToi[u] + g.a[u][i];
                luuVet[i] = u;
            }
        }
    }
}

void dijkstra(int start, int finish, DoThi g)
{
    for (int i = 0; i < g.n; i++)
    {
        chuaXet[i] = 0;
        luuVet[i] = -1;
        doDaiDuongDiToi[i] = VOCUC;
    }

    doDaiDuongDiToi[start] = 0;
    while (chuaXet[finish] == 0)
    {
        int u = timDuongDiNhoNhat(g);
        if (u == -1)
            break;
        capNhatDuongDi(u, g);
    }
    if (chuaXet[finish] == 1)
    {
        printf("Duong di ngan nhat tu dinh %d den dinh %d la: ", start, finish);
        printf("%d ", finish);
        int i = finish;
        while (luuVet[i] != start)
        {
            printf("<- %d ", luuVet[i]);
            i = luuVet[i];
        }
        printf("<- %d\n", luuVet[i]);
        printf("\t\nVoi do dai la %d\n", doDaiDuongDiToi[finish]);
    }
    else
    {
        printf("Khong co duong di");
    }
}

int main()
{
    DoThi g;
    docFile("kiemtra.txt", g);
    printf("Ma tran do thi: \n");
    printfMatrix(g);
    printf("\n");
    dijkstra(0, 3, g);

    return 0;
}