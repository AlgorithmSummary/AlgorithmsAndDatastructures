#include <iostream>
#include <vector>

using namespace std;

vector<int> Add(const vector<int>& A, const vector<int>& B,const int& n){

    vector<int>C(n + 1, 0);

    for(int i = 0; i < n; i++){

        C[i] += A[i] + B[i];
        
        int j = i;

        while(j < n && C[j] >= 2){
            C[j] = C[j] % 2;
            C[j + 1] += 1;
            j++;
        }

    }
    return C;
}

int main(){

    int n;
    cin >> n;

    vector<int> a(n), b(n);

    for(int& i : a)
        cin >> i;
    for(int& j : b)
        cin >> j;

    vector<int>Answer = Add(a, b, n);
    
    for(const int& k : Answer)
        cout << k << ' ';

    return 0;
}   