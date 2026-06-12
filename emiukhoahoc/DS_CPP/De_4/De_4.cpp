/*
============================================================
 DE 4:
   1. Tao va ghi mot file gom 10000 phan tu so nguyen.
   2. Doc file vua tao, luu 10000 phan tu vao mot mang 1 chieu.
   3. Cai dat thuat toan SHELL SORT cho mang mot chieu.
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 10000

// ---- 1. Tao file gom N so nguyen ngau nhien ----
void TaoFile(const char *tenFile, int n) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc file de ghi!\n"); return; }
    fprintf(fo, "%d\n", n);
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        fprintf(fo, "%d ", rand() % 100000);   // so nguyen 0..99999
    fclose(fo);
}

// ---- 2. Doc file vao mang 1 chieu, tra ve so phan tu doc duoc ----
int DocFile(const char *tenFile, int a[]) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc file de doc!\n"); return 0; }
    int n = 0;
    fscanf(fi, "%d", &n);
    for (int i = 0; i < n; i++) fscanf(fi, "%d", &a[i]);
    fclose(fi);
    return n;
}

// ---- 3. Shell sort (insertion sort theo khoang cach h giam dan) ----
void ShellSort(int a[], int n) {
    for (int h = n / 2; h > 0; h /= 2) {        // khoang cach h: n/2, n/4 ... 1
        for (int i = h; i < n; i++) {
            int x = a[i];
            int j = i - h;
            while (j >= 0 && a[j] > x) {         // chen vao doan da sap
                a[j + h] = a[j];
                j -= h;
            }
            a[j + h] = x;
        }
    }
}

// ---- Kiem tra mang da tang dan chua ----
bool DaSapTang(int a[], int n) {
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1]) return false;
    return true;
}

int main() {
    static int a[N];
    const char *file = "input.txt";

    TaoFile(file, N);
    printf("Da tao file %s gom %d so nguyen.\n", file, N);

    int n = DocFile(file, a);
    printf("Da doc %d phan tu vao mang.\n", n);
    printf("5 phan tu dau truoc khi sap: ");
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");

    ShellSort(a, n);
    printf("5 phan tu dau sau Shell sort: ");
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");
    printf("Mang da sap tang dan? %s\n", DaSapTang(a, n) ? "DUNG" : "SAI");

    // Ghi ket qua da sap ra file
    FILE *fo = fopen("output.txt", "wt");
    if (fo) {
        fprintf(fo, "%d\n", n);
        for (int i = 0; i < n; i++) fprintf(fo, "%d ", a[i]);
        fclose(fo);
        printf("Da ghi mang da sap vao output.txt\n");
    }
    return 0;
}
