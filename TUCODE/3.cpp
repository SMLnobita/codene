#include <stdio.h>
#include <stdlib.h>

void nhapMang(int** a, int hang, int cot){
    for (int i = 0; i < hang; i++)
    {
        for (int j = 0; j < cot; j++)
        {
            printf("Mang dang nhap [%d][%d]: ", i,j);
            scanf("%d", &a[i][j]);
        }
        
    }
    
}

void xuatMang(int** a, int hang , int cot){
    for (int i = 0; i < hang; i++)
    {
        for (int j = 0; j < cot; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
}

void suly(int** a, int hang , int cot){
    FILE *file = fopen("behoane.inp", "w");
    if (file==NULL)
    {
        printf("khong the mo file");
    }

    for (int i = 0; i < hang; i++)
    {
        double sum = 0;
        for (int j = 0; j < cot; j++)
        {
            sum+=a[i][j];
        }
        sum/=cot;
        printf("%.2lf ", sum);
    }
    fclose(file);
    
}

int main(){
    int n,m;
    printf("Nhap so hang: ");
    scanf("%d", &n);
    printf("Nhap so cot: ");
    scanf("%d", &m);
    //tao con tro
    int** Mangne = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        Mangne[i] = (int*)malloc(m*sizeof(int));
    }

    nhapMang(Mangne, n,m);
    xuatMang(Mangne, n,m);
    suly(Mangne,n,m);

    //Giai phong bo nho
    free(Mangne);
    
}