#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

typedef struct {
    int a;
    int b;
} Num;

Num new_num(int a, int b)
{
    Num N;
    int g = gcd(a,b);
    N.a = a/g;
    N.b = b/g;
    return N;
}

Num sub_num(Num A, Num B)
{
    int a = (A.a * B.b) - (B.a * A.b);
    int b = A.b * B.b;  
    return new_num(a,b);
}

Num mult_num(Num A, Num B)
{
    int a = A.a * B.a;
    int b = A.b * B.b;  
    return new_num(a,b);
}
    
Num inv_num(Num N)    
{    
    return new_num(N.b,N.a);    
}    
    
void sub_numrow(Num *A, Num *B, int n)    
{    
    int i;    
    for(i=0; i<n; i++)    
    {    
        A[i] = sub_num(A[i],B[i]);    
    }    
}    
     
void scale_numrow(Num *In, Num *Out, Num S,int n)    
{    
    int i;    
    for(i=0; i<n; i++)    
    {    
        Out[i] = mult_num(In[i],S);    
    }    
}    
void print_num(char *F,Num A)    
{    
    printf(F,A.a,A.b);    
}    
     
void Gauss(Num **A, Num *O,int n)    
{    
    int i,j;    
    for(i=0; i<n; i++)    
    {    
        scale_numrow(A[i],A[i],inv_num(A[i][i]),n+1);    
        for(j=i+1; j<n; j++)    
        {    
            Num *Scaled = (Num *)malloc(sizeof(Num)*(n+1));    
            scale_numrow(A[i],Scaled,A[j][i],n+1);    
            sub_numrow(A[j],Scaled,n+1);    
            free(Scaled);    
        }    
    }    
    for(i=n-1; i>=0; i--)    
    {    
        for(j=0; j<i; j++)    
        {    
            Num *Scaled = (Num *)malloc(sizeof(Num)*(n+1));    
            scale_numrow(A[i],Scaled,A[j][i],n+1);
            sub_numrow(A[j],Scaled,n+1);
            free(Scaled);
        }
    }
    /*
    for(i=0; i<n; i++)
    {
        for(j=0; j<n+1; j++)
        {
            print_num("(%d/%d) ",A[i][j]);
        }
        printf("\n");
    }
    */
    for(i=0; i<n; i++)
    {
        O[i] = A[i][n];
    }
}


int dfind(int *lst, int n)
{
    int eq=1,dn,d,i;
    for(i=0; i<n-1; i++)
    {
        dn = lst[i+1] - lst[i];
        eq &= (dn == d);
        lst[i] = d = dn;
    }
    if(eq)
        return 0;
    else
        return 1+dfind(lst,n-1);
}

int main()
{
    int n,i,j;
    scanf("%d",&n);
    int *lst = (int *)malloc(sizeof(int)*n);
    int *lst1 = (int *)malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        scanf("%d",lst+i);
    for(i=0; i<n; i++)
        lst1[i] = lst[i];
    
    n=dfind(lst,n)+1;
    free(lst);
    Num **A = (Num **)malloc(sizeof(Num *)*n);
    Num *O = (Num *)malloc(sizeof(Num)*n);
    for(i=0; i<n; i++)
    {
        A[i] = (Num *)malloc(sizeof(Num)*(n+1));
        for(j=0; j<n; j++)
        {
            A[i][j] = new_num(pow(i+1,j),1);
        }
        A[i][n] = new_num(lst1[i],1);
    }
    free(lst1);
    Gauss(A,O,n);
    for(i=n-1; i>=0; i--)
    {
        if(O[i].a)
        {
            print_num("(%d/%d)",O[i]);
            printf("x^%d ",i);
        }
    }
    printf("\n");
    free(O);
    for(i=0; i<n; i++)
        free(A[i]);
    free(A);
}
