#include <iostream>
#include <vector>

using namespace std;

void MERGE(vector<int>&A, int l, int m,  int r){

    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int>L(n1, 0), R(n2, 0);


    for(int i = 0; i < n1; i++)
        L[i] = A[l + i];
    for(int i = 0; i < n2; i++)
        R[i] = A[m + 1 + i];

    int i = 0, j = 0;
    int k = l;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        A[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        A[k] = R[j];
        j++;
        k++;
    }

}

void MERGE_SORT(vector<int>&A, int l, int r){
    if(l >= r)
        return;
    int m = (l + r) >> 1;
    MERGE_SORT(A, l, m);
    MERGE_SORT(A, m + 1, r);
    MERGE(A, l, m, r);
}

int main(){

    int n;

    cout << "Type the size of array ";

    cin >> n;
    vector<int>v(n, 0);

    cout << "Type the l-values in array ";
    for(int& i : v)
        cin >> i;

    cout << "RESULT : ";

    MERGE_SORT(v, 0, n - 1);

    for(const int& value : v)
        cout << value << ' ';

    return 0;
}