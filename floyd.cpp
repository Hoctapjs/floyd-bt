#include <stdio.h>
#include <limits.h>

#define N_MAX 100 // số hàng - cột tối đa có thể có là 100
#define INF 9999 // định nghĩa vô cực bằng 9999 - khi nhập vô cực thì nhập 9999

void inMaTran(int mat[][N_MAX], int N); // hàm in ma trận khoảng cách ngắn nhất
void floydWarshall(int graph[][N_MAX], int N); // hàm xử lý chính

int main()
{
    // hàm main sẽ chứa những thao tác nhập
    int N;
    printf("Nhap so dinh cua do thi: ");
    scanf("%d", &N);

    // đoạn mã kiểm tra điều kiện với đỉnh nhập vào
    // số lượng đỉnh không thể âm và không thể lớn hơn giới hạn cho phép
    if (N <= 0 || N > N_MAX)
    {
        printf("Nhap so dinh khong hop le.\n");
        return 1; // Thoat chuong trinh voi ma loi 1
    }

    // đoạn mã khai báo và nhập ma trận khoảng cách
    int graph[N_MAX][N_MAX];
    printf("Nhap ma tran A:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, N); // gọi hàm để tính ma trận theo thuật toán

    return 0;
}

void floydWarshall(int graph[][N_MAX], int N)
{
    int dist[N_MAX][N_MAX];
    int next[N_MAX][N_MAX];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dist[i][j] = graph[i][j];
            if (i == j)
            {
                next[i][j] = -1; // Không có đỉnh tiếp theo nếu là chính nó
            }
            else if (graph[i][j] != INF)
            {
                next[i][j] = j; // Đỉnh tiếp theo là j nếu có kết nối từ i đến j
            }
            else
            {
                next[i][j] = -1; // Không có đỉnh tiếp theo nếu không có kết nối từ i đến j
            }
        }
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (dist[i][k] == INF || dist[k][j] == INF)
                {
                    continue; // Tránh tràn số nếu có cạnh âm
                }

                int altDist = dist[i][k] + dist[k][j];
                if (altDist < dist[i][j])
                {
                    dist[i][j] = altDist;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // In ra ma trận khoảng cách và ma trận lưu trữ đỉnh tiếp theo nếu có
    printf("Ma tran khoang cach ngan nhat:\n");
    inMaTran(dist, N);


    // in ra ma trận đường đi
    printf("\nMa tran duong di:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (next[i][j] == -1)
            {
                printf("0\t");
            }
            else
            {
                printf("%d\t", next[i][j] + 1); // +1 vì đề bài đánh số đỉnh từ 1
            }
        }
        printf("\n");
    }
}

void inMaTran(int mat[][N_MAX], int N) // hàm dùng để in ma trận khoảng cách
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] == INF)
            {
                printf("INF\t");
            }
            else
            {
                printf("%d\t", mat[i][j]);
            }
        }
        printf("\n");
    }
}
