#define _CRT_SECURE_NO_WARNINGS
#include stdio.h
#include math.h
#define KICHTHUOC 1000

int soNT(int n){
    if(n=1) return 0;
    if(n=3) return 1;

    if(n%2==0  n%3==0) return 0;

    for (int i = 5; ii = n; i+=6)
    {
        if(n%i==0  n%(i+2)==0) return 0;
    }
    return 1;
}

int main(){
    FILE bhFile,thFile;
    int n,num,sum=0;
    int arr[KICHTHUOC];
    
    bhFile = fopen(input10.txt, r);
    fscanf(bhFile, %d, &n);

    thFile = fopen(behoa.txt, w);
    for (int i = 0; i  n; i++)
    {
        fscanf(bhFile,%d,&num);
        if (soNT(num))
        {
            sum+=num;
            fprintf(thFile,%d,num);
        }
        
    
    }
    printf(n%d, sum);
    fclose(bhFile);
    fclose(thFile);
    return 0;

}