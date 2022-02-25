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

void sort(Canh T[], int tongSoCanh)
{
    for (int i = 0; i < tongSoCanh; i++)
    {
        for (int j = i + 1; j < tongSoCanh; j++)
        {
            if (T[i].value > T[j].value)
            {
                Canh tam = T[i];
                T[i] = T[j];
                T[j] = tam;
            }
        }
    }
}

void Kruskal(DoThi g)
{
    Canh listEdge[MAX];
    int tongSoCanh = 0;
    for (int i = 0; i < g.n; i++) // thêm các cạnh vào listEdge
    {
        for (int j = i + 1; j < g.n; j++)
        {
            if (g.a[i][j] > 0)
            {
                listEdge[tongSoCanh].x = i;
                listEdge[tongSoCanh].y = j;
                listEdge[tongSoCanh].value = g.a[i][j];
                tongSoCanh++;
            }
        }
    }
    sort(listEdge, tongSoCanh);
    int nT = 0; // slg các cạnh trong cây khung
    Canh T[MAX]; // chứa các cạnh của cây khung
    int nhan[MAX]; // chứa nhãn của các đỉnh trong đồ thị
    for (int i = 0; i < g.n; i++) 
        nhan[i] = i;
    int canhDangXet = 0;
    while (nT < g.n && canhDangXet < tongSoCanh)
    {
    //thêm 1 cạnh vào cây khung mà không tạo chu trình bằng cách chọn mà đỉnh tại nhãn khác nhau
        int x = listEdge[canhDangXet].x;
        int y = listEdge[canhDangXet].y;
        if (nhan[x] != nhan[y])
        {
            T[nT].x = x;
            T[nT].y = y;
            T[nT].value = listEdge[canhDangXet].value;
            nT++;
    // sửa nhãn của tất cả các đỉnh có cùng gtrị với nhãn của đỉnh y thành nhãn của đỉnh x
            for (int i = 0; i < g.n; i++)
            {
                if (nhan[i] == nhan[y])
                    nhan[i] = nhan[x];
            }
        }
        canhDangXet++;
    }
    if (nT < g.n - 1)
        printf("\nDo thi khong lien thong.\n");
    else
    {
        int tongCayKhung = 0;
        printf("Cay khung nho nhat cua do thi la:");
        for (int i = 0; i < nT - 1; i++)
        {
            printf("\n(%d, %d): %d", T[i].x + 1, T[i].y + 1, T[i].value);
            tongCayKhung += T[i].value;
        }
        printf("\nTong gia tri cua cay khung la %d\n", tongCayKhung);
    }
}

int main()
{
    DoThi g;
    int tongSoCanh;
    docFile("test8.txt", g);
    printf("Ma tran do thi:\n");
    printfMatrix(g);
    printf("\n");
    Kruskal(g);
    return 0;
}