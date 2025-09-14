#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int>& A, int n){

    for(int i = 1; i < n; i++){
        
        int key = A[i];
        // key 를 하나 잡는다
        
        int j = i - 1;
        // 이후 삽입할 포인터를 초기화 해 준다.
        // 이전은 정렬이 되있으므로, key의 index - 1 정도로 잡는다.
        
        while(j >= 0 && A[j] > key){
            
            A[j + 1] = A[j];
            //부분 배열을 앞으로 땡기고
            // 중간에 값이 key 보다 작으면 멈춘뒤에 키를= 삽입한다.
            j -= 1;
        
        }
        
        A[j + 1] = key;
    
    }

}

int main(){
    
    int n;
    cin >> n;

    vector<int>v(n);
    
    for(int& i : v)
        cin >> i;

    sort(v, n);

    for(const int& i : v){
        cout << i << ' ';
    }

    return 0;

}