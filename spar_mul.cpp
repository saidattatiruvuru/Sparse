#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

int* generateSparseMatrix(int m, int n, double s, int* col_ind, int* row_ptr, int* Size){
    srand(time(0));
    
    int col_i = 0, row_p = 0;
    int ran, c = 0, r = 0, size = (int)(m*n*s);
    int* M = (int*) malloc(size*sizeof(int));

    for(int i = 0; i< size; i++){
        while (c < size && r < m )
        {
            if(col_i == n){
                row_ptr[r] = row_p;
                col_i = 0;
                r++;
            }
            ran = rand() % m*n + 1;
            if( ran < m*n*s){
                col_ind[c] = col_i;
                row_p++;
                col_i++;
                c++;
                *Size = row_p;
                break;
            }
            col_i++;
        }
        M[i] = rand()%10 + 1; 
        
    }
    while(r<m){
            row_ptr[r] = row_p;
            r++;
    }
    return M;
}

void printCSR(int* M, int* col_ind, int* row_ptr, int m, int n){
    int c=0, r=0, next = 0;
    for(int i = 0; i<m ; i++){
        next = 0;
        for(int j = 0; j<n;j++){
            if(col_ind[c] == j && next != 1){
                cout<<M[c]<<" ";
                c++;
                r++;
                if(r == row_ptr[i]){
                    next = 1;
                }
            }
            else{
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void printRaw(int* A, int* colA, int* rowA, int m, int n, int sa){

    for(int i = 0; i < (int)(m*n*sa) ; i++){
        cout<< A[i] << " ";
    }
    cout<<"\n";
    for(int i = 0; i < (int)(m*n*sa) ; i++){
        cout<< colA[i] << " ";
    }
    cout<<"\n";for(int i = 0; i < (int)(m) ; i++){
        cout<< rowA[i] << " ";
    }
    cout<<endl;
}

int main(int argc, char* args[]){
    int m = 5, n = 3, p = 2;
    double sa = 0.2, sb = 0.5;
    
    m = atoi(args[1]);
    n = atoi(args[2]);
    p = atoi(args[3]);
    sa = atof(args[4]);
    sb = atof(args[5]);
    
    
    int sizeA = (int)(m*n*sa);
    
    int* col_indA = (int*) malloc(sizeA*sizeof(int));
    int* row_ptrA = (int*) malloc((m)*sizeof(int));
    int SizeA,SizeB;
    int* A = generateSparseMatrix(m, n, sa, col_indA, row_ptrA, &SizeA);

    int sizeB = (int)(n*p*sb);

    int* row_indB = (int*) malloc(sizeB*sizeof(int));
    int* col_ptrB  = (int*) malloc((p)*sizeof(int));
    int* B = generateSparseMatrix(p, n, sb, row_indB, col_ptrB, &SizeB);

/*
    printCSR(A, col_indA, row_ptrA, m, n);
    for(int i = 0; i < SizeA ; i++){
        cout<< A[i] << " ";
    }
    cout<<"\n";
    for(int i = 0; i < SizeA ; i++){
        cout<< col_indA[i] << " ";
    }
    cout<<"\n";for(int i = 0; i < (int)(m) ; i++){
        cout<< row_ptrA[i] << " ";
    }
    cout<<endl;
    cout<<"____________"<<endl;


    printCSR(B, row_indB, col_ptrB, p, n);
    for(int i = 0; i < SizeB ; i++){
        cout<< B[i] << " ";
    }
    cout<<"\n";
    for(int i = 0; i < SizeB ; i++){
        cout<< row_indB[i] << " ";
    }
    cout<<"\n";for(int i = 0; i < (int)(p) ; i++){
        cout<< col_ptrB[i] << " ";
    }
    cout<<endl;
    cout<<"____________"<<endl;

    */

    clock_t s1, e1, s2, e2;
    int* C = (int*) malloc(m*p*sizeof(int));
    int element = 0;
    int c=0, r=0;
    s1 = clock();
    for(int i = 0; i < m; i++){
        for(int j = 0; j < p; j++){
            element = 0;
            c = (i-1)<0 ? 0 : row_ptrA[i-1];
            while(c<row_ptrA[i]){
                r = (j-1)< 0 ? 0 : col_ptrB[j-1];
                while(r<col_ptrB[j]){
                    if(col_indA[c] == row_indB[r]){
                        element += A[c]*B[r];
                    }
                    r++;
                }
                c++;
            }
            //cout<<element<<"  ";
        }
        //cout<<endl;
    }
    e1 = clock();
    int next = 0;
    c = r = 0;
    int* AMat = (int*) malloc(m*n*sizeof(int));
    int* BMat = (int*) malloc(n*p*sizeof(int));
    for(int i = 0; i<m ; i++){
        next = 0;
        for(int j = 0; j<n;j++){
            if(col_indA[c] == j && next != 1){
                AMat[i*n + j] = A[c];
                c++;
                r++;
                if(r == row_ptrA[i]){
                    next = 1;
                }
            }
            else{
                AMat[i*n + j] = 0;
            }
        }
        //cout<<endl;
    }
    c = 0;
    r = 0;
    for(int i = 0; i<n ; i++){
        next = 0;
        for(int j = 0; j<p;j++){
            if(row_indB[c] == j && next != 1){
                BMat[i + j*n] = B[c];
                c++;
                r++;
                if(r == col_ptrB[i]){
                    next = 1;
                }
            }
            else{
                BMat[i + j*n] = 0;
            }
        }
        //cout<<endl;
    }
    
    
    int* CMat = (int*) malloc(m*p*sizeof(int));
    s2 = clock();
    for(int i=0; i<m; i++){
        for(int j=0; j<p; j++){
            element = 0;
            for(int k=0; k<n; k++){
                element += A[i*n + k] + B[k*p + j];
            }
            CMat[i*p + j] = element;
        }
    }
    e2 = clock();

    cout<<"Sparse implementation "<<(e1-s1)<<"     Normal "<<(e2-s2)<<endl;
}
