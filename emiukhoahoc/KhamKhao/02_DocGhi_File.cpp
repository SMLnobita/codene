/*
============================================================
 ON TAP 2: DOC / GHI FILE (nhap xuat du lieu + xu ly du lieu)
============================================================
 4 buoc thao tac file:
   1. Khai bao con tro FILE*
   2. Mo file: fopen(tenfile, mode)
   3. Xu ly (doc/ghi)
   4. Dong file: fclose
 Mode thong dung:
   "rt" doc van ban | "wt" ghi van ban | "at" ghi noi tiep
   "rb"/"wb" nhi phan | "r+" doc va ghi
 Ham van ban : fscanf / fprintf, fgets / fputs, getc
 Ham nhi phan: fread / fwrite
 Meo doc het file: while (fscanf(...) == 1)  (chac hon feof)
============================================================
*/
#include <cstdio>
#include <cstdlib>

// Ghi n so nguyen ra file van ban
void GhiFile(const char *tenFile, int a[], int n) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc file de ghi!\n"); return; }
    fprintf(fo, "%d\n", n);                 // dong dau: so luong
    for (int i = 0; i < n; i++)
        fprintf(fo, "%d ", a[i]);
    fclose(fo);
}

// Doc danh sach so nguyen tu file van ban, tra ve mang cap phat dong
int* DocFile(const char *tenFile, int &n) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc file de doc!\n"); n = 0; return NULL; }
    fscanf(fi, "%d", &n);
    int *a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        fscanf(fi, "%d", &a[i]);
    fclose(fi);
    return a;
}

// Doc tung dong chuoi bang fgets
void DocTungDong(const char *tenFile) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) return;
    char dong[256];
    while (fgets(dong, 256, fi) != NULL)   // doc den het file
        printf("  dong: %s", dong);
    fclose(fi);
}

// Ghi / doc file NHI PHAN bang fwrite / fread
void DemoNhiPhan(int a[], int n) {
    FILE *f = fopen("data.bin", "wb");
    fwrite(&n, sizeof(int), 1, f);         // ghi so luong
    fwrite(a, sizeof(int), n, f);          // ghi ca mang
    fclose(f);

    int m, b[100];
    f = fopen("data.bin", "rb");
    fread(&m, sizeof(int), 1, f);
    fread(b, sizeof(int), m, f);
    fclose(f);
    printf("Doc tu file nhi phan: ");
    for (int i = 0; i < m; i++) printf("%d ", b[i]);
    printf("\n");
}

int main() {
    int a[] = {9, 3, 7, 1, 5};
    int n = 5;

    // 1. Ghi mang ra file van ban
    GhiFile("input.txt", a, n);
    printf("Da ghi input.txt\n");

    // 2. Doc lai tu file
    int m = 0;
    int *b = DocFile("input.txt", m);
    printf("Doc duoc %d so: ", m);
    for (int i = 0; i < m; i++) printf("%d ", b[i]);
    printf("\n");

    // 3. Xu ly du lieu doc duoc: tinh tong, max
    int tong = 0, max = b[0];
    for (int i = 0; i < m; i++) {
        tong += b[i];
        if (b[i] > max) max = b[i];
    }
    printf("Tong = %d, Max = %d\n", tong, max);

    // 4. Doc theo dong
    printf("Noi dung file theo dong:\n");
    DocTungDong("input.txt");
    printf("\n");

    // 5. File nhi phan
    DemoNhiPhan(a, n);

    free(b);
    return 0;
}
