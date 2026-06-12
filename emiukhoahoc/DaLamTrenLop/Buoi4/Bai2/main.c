#include <stdio.h>
#include <stdlib.h>

int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  int temp;
  int dem = 0;
  while (fscanf(f, "%d", &temp) == 1) {
    dem++;
  }
  fclose(f);
  return dem;
}

void readfile(int *arr, const char *tenfile) {
  FILE *fi = fopen(tenfile, "rt");
  int i = 0;
  printf("Du lieu tu file: ");
  while (fscanf(fi, "%d", &arr[i]) == 1) {
    printf("%d ", arr[i]);
    i++;
  }
  fclose(fi);
}

void writefile(int *arr, int n, const char *tenfile) {
  FILE *fo = fopen(tenfile, "wt");
  printf("\nDu lieu luu file: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
    fprintf(fo, "%d ", arr[i]);
  }
  fclose(fo);
}

void Distribute(int a[], int n, int *pb, int *pc, int k, int b[], int c[]) {
  int p = 0;
  int i;

  *pb = 0;
  *pc = 0;

  while (p < n) {
    for (i = 0; i < k && p < n; i++) {
      b[(*pb)++] = a[p++];
    }
    for (i = 0; i < k && p < n; i++) {
      c[(*pc)++] = a[p++];
    }
  }
}

void Merge(int a[], int nb, int nc, int k, int b[], int c[]) {
  int p = 0;
  int pb = 0;
  int pc = 0;

  while (pb < nb && pc < nc) {
    int ib = 0, ic = 0;
    int kb, kc;

    kb = (nb - pb < k) ? (nb - pb) : k;
    kc = (nc - pc < k) ? (nc - pc) : k;

    while (ib < kb && ic < kc) {
      if (b[pb + ib] <= c[pc + ic]) {
        a[p++] = b[pb + ib];
        ib++;
      } else {
        a[p++] = c[pc + ic];
        ic++;
      }
    }

    while (ib < kb) {
      a[p++] = b[pb + ib];
      ib++;
    }

    while (ic < kc) {
      a[p++] = c[pc + ic];
      ic++;
    }

    pb += kb;
    pc += kc;
  }

  while (pb < nb) {
    a[p++] = b[pb++];
  }

  while (pc < nc) {
    a[p++] = c[pc++];
  }
}

void MergeSort(int a[], int n) {
  int *b = (int *)malloc(n * sizeof(int));
  int *c = (int *)malloc(n * sizeof(int));
  int pb, pc;
  int k = 1;

  do {
    Distribute(a, n, &pb, &pc, k, b, c);
    Merge(a, pb, pc, k, b, c);
    k = k * 2;
  } while (k < n);

  free(b);
  free(c);
}

int main() {
  int n = demPhanTu("data.txt");
  int *arr = (int *)malloc(n * sizeof(int));

  readfile(arr, "data.txt");

  MergeSort(arr, n);

  writefile(arr, n, "ketqua.txt");

  free(arr);
  return 0;
}