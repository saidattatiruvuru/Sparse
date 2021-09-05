#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

int* generateSparseMatrix(int m, int n, double s, int* col_ind, int* row_ptr){
    srand(time(0));
    
    int col_i = 0, row_p = 0;
    int ran, c = 0, r = 0, size = (int)(m*n*s);
    int* M = (int*) malloc(size*sizeof(int));

    for(int i = 0; i< size; i++){
        M[i] =(int) rand()+1; 
        //cout<< "element" << M[i]<<endl;
        while (c < size && r < m )
        {
            if(col_i == n){
                row_ptr[r] = row_p;
                cout<<"here "<<row_p<<endl;
                col_i = 0;
                r++;
            }
            ran = rand() % m*n + 1;
            cout<<"c and r "<<c<<" "<<r<<endl;
            if( ran < m*n*s){
                col_ind[c] = col_i;
                row_p++;
                col_i++;
                c++;
                //cout<<"done"<<endl;
                break;
            }
            col_i++;
        }
        
    }
    while(r<m){
            row_ptr[r] = row_p;
            r++;
    }
    return M;
}


int main(int argc, char* args[]){
    int m = 5, n = 3, p = 2;
    double sa = 0.2, sb = 0.5;
    
    m = atoi(args[1]);
    n = atoi(args[2]);
    p = atoi(args[3]);
    sa = atof(args[4]);
    sb = atof(args[5]);
    
    
    int size = (int)(m*n*sa);
    
    int* colA = (int*) malloc(size*sizeof(int));
    int* rowA = (int*) malloc((m)*sizeof(int));
    int* A = generateSparseMatrix(m, n, sa, colA, rowA);

    int* colA = (int*) malloc(size*sizeof(int));
    int* rowA = (int*) malloc((m)*sizeof(int));
    int* B = generateSparseMatrix(m, n, sa, colA, rowA);

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
    cout<<"\n";


}
