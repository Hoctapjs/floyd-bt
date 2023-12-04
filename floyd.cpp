#include <stdio.h>
#include <limits.h>

#define N_MAX 100 // số hàng - cột tối đa có thể có là 100
#define INF 9999  // định nghĩa vô cực bằng 9999 - khi nhập vô cực thì nhập 9999

void inMaTran(int mat[][N_MAX], int N);               // hàm in ma trận khoảng cách ngắn nhất
void floydWarshall(int MaTranDauVao[][N_MAX], int N); // hàm xử lý chính
int lietkeduongdi(int Dinh[][N_MAX], int N, int nhap, int xuat);

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
    int MaTranDauVao[N_MAX][N_MAX];
    printf("Nhap ma tran A:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &MaTranDauVao[i][j]);
        }
    }

    floydWarshall(MaTranDauVao, N); // gọi hàm để tính ma trận theo thuật toán

    return 0;
}

void floydWarshall(int MaTranDauVao[][N_MAX], int N)
{
    int KhoangCach[N_MAX][N_MAX]; // ma tran khoang cach
    int Dinh[N_MAX][N_MAX];       // ma tran dinh

    for (int i = 0; i < N; i++) // vòng lặp hàng
    {
        for (int j = 0; j < N; j++) // vòng lặp cột
        {
            KhoangCach[i][j] = MaTranDauVao[i][j]; // gán giá trị cho ma trận khoảng cách d1
            if (i == j)                            // kiểm tra điểm bắt đầu và điểm kết thúc
            {
                Dinh[i][j] = -1; // Không có đỉnh tiếp theo nếu là chính nó
            }
            else if (MaTranDauVao[i][j] != INF)
            {
                Dinh[i][j] = j; // Đỉnh tiếp theo là j nếu có đường đi từ i đến j
            }
            else
            {
                Dinh[i][j] = -1; // Không có đỉnh tiếp theo nếu không có đường từ i đến j
            }
        }
    }

    /*Ba vòng lặp lồng nhau này chạy qua tất cả các cặp đỉnh (i, j) và sử dụng đỉnh trung gian k để kiểm tra xem
    có đường đi ngắn hơn từ i đến j thông qua đỉnh k không.*/
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (KhoangCach[i][k] == INF || KhoangCach[k][j] == INF)
                {
                    continue; // Tránh tràn số nếu có cạnh âm
                }

                int TongDoDai = KhoangCach[i][k] + KhoangCach[k][j];
                if (TongDoDai < KhoangCach[i][j])
                {
                    KhoangCach[i][j] = TongDoDai;
                    Dinh[i][j] = Dinh[i][k];
                }
            }
        }
    }

    // In ra ma trận khoảng cách và ma trận lưu trữ đỉnh tiếp theo nếu có
    printf("Ma tran khoang cach ngan nhat:\n");
    inMaTran(KhoangCach, N);
    // in ra ma trận đường đi
    printf("\nMa tran duong di:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Dinh[i][j] == -1)
            {
                printf("0\t");
            }
            else
            {
                printf("%d\t", Dinh[i][j] + 1); // +1 vì đề bài đánh số đỉnh từ 1
            }
        }
        printf("\n");
    }
    int nhap, xuat;
    int temp = 0, temp2;

    do
    {
        printf("\nHay nhap dinh bat dau: ");
        scanf("%d", &nhap);
        printf("\nHay nhap dinh ket thuc: ");
        scanf("%d", &xuat);

        if (nhap == 0 || xuat == 0)
        {
            break; // Thoát khỏi vòng lặp nếu nhap hoặc xuat bằng 0
        }

        printf("\nKhoang cach ngan nhat tu dinh %d den dinh %d la: %d", nhap, xuat, KhoangCach[nhap - 1][xuat - 1]);

        lietkeduongdi(Dinh, N, nhap, xuat);
    } while (nhap != 0 && xuat != 0);
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
/*int lietkeduongdi(int Dinh[][N_MAX], int N, int nhap, int xuat)
{
    if (nhap == xuat)
    {
        return nhap;
    }

    if (nhap != xuat)
    {
        int temp = Dinh[nhap][xuat];
        printf("\nDuong di tu dinh %d den dinh %d la: %d", nhap + 1, xuat + 1, Dinh[nhap][xuat]);
        return lietkeduongdi(Dinh, N, temp, xuat);
    }
}*/

int lietkeduongdi(int Dinh[][N_MAX], int N, int nhap, int xuat)
{
    nhap = nhap - 1;
    xuat = xuat - 1;
    int temp;
    temp = Dinh[nhap][xuat];
    while (nhap != xuat)
    {
        printf("\nDuong di tu dinh %d den dinh %d la: %d", nhap + 1, xuat + 1, temp + 1);
        nhap = temp;
        temp = Dinh[nhap][xuat];

        if (nhap == xuat)
        {
            return 0;
        }
    }
}