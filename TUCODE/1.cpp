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

void sulyVsFile(int** a, int hang, int cot){
    FILE *file = fopen("output24.txt", "w");
    if(file==NULL){
        printf("Khong the mo file");
        return;
    }
    printf("Sau khi su ly\n");
    for (int i = 0; i < hang; i++)
    {
        for (int j = 0; j < cot; j++)
        {
            if(a[i][j]%2!=0){
                printf("%d ", a[i][j]);
                fprintf(file,"%d ",a[i][j]);
            }
        }
        
    }
    fclose(file);
    printf("\nDa hoan thanh");
    
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
    sulyVsFile(Mangne, n,m);

    //Giai phong bo nho
    free(Mangne);
    
}