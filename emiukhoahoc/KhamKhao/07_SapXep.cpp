/*
============================================================
 ON TAP 5: CAC THUAT TOAN SAP XEP (tat ca tang dan)
============================================================
 | Thuat toan   | Tot nhat   | Xau nhat   | Ghi chu            |
 |--------------|------------|------------|--------------------|
 | Interchange  | O(n^2)     | O(n^2)     | doi cho truc tiep  |
 | Selection    | O(n^2)     | O(n^2)     | chon min dua ve dau|
 | Insertion    | O(n)       | O(n^2)     | chen vao doan da sap|
 | Bubble       | O(n)*      | O(n^2)     | noi bot (*co cai tien)|
 | Quick        | O(n log n) | O(n^2)     | chia de tri, chon mot|
 | Heap         | O(n log n) | O(n log n) | max-heap           |
 | Shell        | ~O(n^1.2)  | tuy h      | insertion theo buoc h|
 | Merge        | O(n log n) | O(n log n) | tron, can bo nho phu|
 | Radix        | O(n*m)     | O(n*m)     | phan lo theo chu so|
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

void inMang(const char *ten, int a[], int n) {
    printf("%-12s: ", ten);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

/* ---------- 1. Interchange sort: doi cho truc tiep ---------- */
void InterchangeSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[i])
                hoanvi(a[i], a[j]);
}

/* ---------- 2. Selection sort: chon min dua ve dau ---------- */
void SelectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min]) min = j;
        if (min != i) hoanvi(a[i], a[min]);
    }
}

/* ---------- 3. Insertion sort: chen vao doan da sap ---------- */
void InsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i];               // phan tu can chen
        int pos = i - 1;
        while (pos >= 0 && a[pos] > x) {
            a[pos + 1] = a[pos];    // doi cho sang phai
            pos--;
        }
        a[pos + 1] = x;             // chen x vao vi tri thich hop
    }
}

/* ---------- 4. Bubble sort: noi bot tu cuoi len ---------- */
void BubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[j - 1])
                hoanvi(a[j], a[j - 1]);
}

/* ---------- 5. Quick sort: chia de tri ---------- */
void QuickSort(int a[], int left, int right) {
    if (left >= right) return;
    int x = a[(left + right) / 2];  // chon mot giua lam moc
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < x) i++;       // tim phan tu >= x ben trai
        while (a[j] > x) j--;       // tim phan tu <= x ben phai
        if (i <= j) {
            hoanvi(a[i], a[j]);
            i++; j--;
        }
    }
    QuickSort(a, left, j);          // sap nua trai
    QuickSort(a, i, right);         // sap nua phai
}

/* ---------- 6. Heap sort: dung max-heap ---------- */
// Hieu chinh doan a[l..r] thanh heap (lan truyen tu nut l xuong)
void heapify(int a[], int l, int r) {
    int x = a[l];
    int i = l, j = 2 * i + 1;       // con trai cua i
    while (j <= r) {
        if (j < r && a[j] < a[j + 1]) j++;  // chon con lon hon
        if (a[j] <= x) break;       // thoa dieu kien heap -> dung
        a[i] = a[j];                // keo con len
        i = j;
        j = 2 * i + 1;
    }
    a[i] = x;
}

void buildHeap(int a[], int n) {    // xay heap tu giua mang ve dau
    for (int l = n / 2 - 1; l >= 0; l--)
        heapify(a, l, n - 1);
}

void HeapSort(int a[], int n) {
    buildHeap(a, n);                // giai doan 1: tao max-heap
    for (int r = n - 1; r > 0; r--) {
        hoanvi(a[0], a[r]);         // dua max ve cuoi
        heapify(a, 0, r - 1);       // hieu chinh lai heap
    }
}

/* ---------- 7. Shell sort: insertion theo khoang cach h ---------- */
void ShellSort(int a[], int n, int h[], int k) {
    for (int step = 0; step < k; step++) {
        int len = h[step];
        for (int i = len; i < n; i++) {   // insertion sort buoc len
            int x = a[i];
            int j = i - len;
            while (j >= 0 && a[j] > x) {
                a[j + len] = a[j];
                j -= len;
            }
            a[j + len] = x;
        }
    }
}

/* ---------- 8. Merge sort (de quy cho de hieu) ---------- */
void Merge(int a[], int left, int mid, int right) {
    int nb = mid - left + 1, nc = right - mid;
    int *b = new int[nb], *c = new int[nc];
    for (int i = 0; i < nb; i++) b[i] = a[left + i];
    for (int i = 0; i < nc; i++) c[i] = a[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < nb && j < nc)            // tron: lay phan tu nho truoc
        a[k++] = (b[i] <= c[j]) ? b[i++] : c[j++];
    while (i < nb) a[k++] = b[i++];     // phan con lai
    while (j < nc) a[k++] = c[j++];
    delete[] b; delete[] c;
}

void MergeSort(int a[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);            // sap nua trai
    MergeSort(a, mid + 1, right);       // sap nua phai
    Merge(a, left, mid, right);         // tron 2 nua
}

/* ---------- 9. Radix sort: phan lo theo tung chu so ---------- */
void RadixSort(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max) max = a[i];

    int **B = new int*[10];             // 10 lo B0..B9
    for (int t = 0; t < 10; t++) B[t] = new int[n];
    int count[10];

    for (int exp = 1; max / exp > 0; exp *= 10) {  // tung hang don vi, chuc...
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; i++) {   // phan lo
            int t = (a[i] / exp) % 10;  // chu so hang exp
            B[t][count[t]++] = a[i];
        }
        int k = 0;                      // ghep lo B0..B9 lai vao a
        for (int t = 0; t < 10; t++)
            for (int i = 0; i < count[t]; i++)
                a[k++] = B[t][i];
    }
    for (int t = 0; t < 10; t++) delete[] B[t];
    delete[] B;
}

/* ==================== CHUONG TRINH TEST ==================== */
int main() {
    int goc[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    const int n = 10;
    int a[n];

    inMang("Mang goc", goc, n);
    printf("\n");

    memcpy(a, goc, sizeof(goc)); InterchangeSort(a, n); inMang("Interchange", a, n);
    memcpy(a, goc, sizeof(goc)); SelectionSort(a, n);   inMang("Selection", a, n);
    memcpy(a, goc, sizeof(goc)); InsertionSort(a, n);   inMang("Insertion", a, n);
    memcpy(a, goc, sizeof(goc)); BubbleSort(a, n);      inMang("Bubble", a, n);
    memcpy(a, goc, sizeof(goc)); QuickSort(a, 0, n-1);  inMang("Quick", a, n);
    memcpy(a, goc, sizeof(goc)); HeapSort(a, n);        inMang("Heap", a, n);
    int h[] = {7, 3, 1};   // day khoang cach giam dan ve 1
    memcpy(a, goc, sizeof(goc)); ShellSort(a, n, h, 3); inMang("Shell", a, n);
    memcpy(a, goc, sizeof(goc)); MergeSort(a, 0, n-1);  inMang("Merge", a, n);
    memcpy(a, goc, sizeof(goc)); RadixSort(a, n);       inMang("Radix", a, n);
    return 0;
}
