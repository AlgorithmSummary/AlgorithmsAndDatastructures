#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Matrix = vector<vector<int>>;

#include <vector>
using namespace std;

using Row    = vector<int>;
using Matrix = vector<Row>;

// C += A * B  (n x n)
/*void MatrixMult(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }

    const int h = n / 2;


    vector<Matrix> a(4, Matrix(h, Row(h, 0)));
    vector<Matrix> b(4, Matrix(h, Row(h, 0)));
    vector<Matrix> c(4, Matrix(h, Row(h, 0)));

    
    for (int i = 0; i < 4; ++i) {
        int sx = (i < 2) ? 0 : h;
        int sy = (i % 2 == 0) ? 0 : h;
        for (int u = 0; u < h; ++u) {
            for (int v = 0; v < h; ++v) {
                a[i][u][v] = A[sx + u][sy + v];
                b[i][u][v] = B[sx + u][sy + v];
                c[i][u][v] = C[sx + u][sy + v];
            }
        }
    }

    // 블록 곱셈 (C블록에 누적)
    // C11 = A11*B11 + A12*B21 + C11
    MatrixMult(a[0], b[0], c[0], h);
    MatrixMult(a[1], b[2], c[0], h);

    // C12 = A11*B12 + A12*B22 + C12
    MatrixMult(a[0], b[1], c[1], h);
    MatrixMult(a[1], b[3], c[1], h);

    // C21 = A21*B11 + A22*B21 + C21
    MatrixMult(a[2], b[0], c[2], h);
    MatrixMult(a[3], b[2], c[2], h);

    // C22 = A21*B12 + A22*B22 + C22
    MatrixMult(a[2], b[1], c[3], h);
    MatrixMult(a[3], b[3], c[3], h);
    
    for (int i = 0; i < 4; ++i) {
        int sx = (i < 2) ? 0 : h;
        int sy = (i % 2 == 0) ? 0 : h;
        for (int u = 0; u < h; ++u) {
            for (int v = 0; v < h; ++v) {
                C[sx + u][sy + v] = c[i][u][v];
            }
        }
    }
}*/

void MatrixMult(const Matrix& A, int ax, int ay,
                const Matrix& B, int bx, int by,
                Matrix& C,       int cx, int cy,
                int n)
{
    if (n == 1) {
        C[cx][cy] += A[ax][ay] * B[bx][by];
        return;
    }

    int h = n / 2;

    // C11 = A11*B11 + A12*B21
    MatrixMult(A, ax,      ay,      B, bx,      by,      C, cx,      cy,      h);
    MatrixMult(A, ax,      ay + h,  B, bx + h,  by,      C, cx,      cy,      h);

    // C12 = A11*B12 + A12*B22
    MatrixMult(A, ax,      ay,      B, bx,      by + h,  C, cx,      cy + h,  h);
    MatrixMult(A, ax,      ay + h,  B, bx + h,  by + h,  C, cx,      cy + h,  h);

    // C21 = A21*B11 + A22*B21
    MatrixMult(A, ax + h,  ay,      B, bx,      by,      C, cx + h,  cy,      h);
    MatrixMult(A, ax + h,  ay + h,  B, bx + h,  by,      C, cx + h,  cy,      h);

    // C22 = A21*B12 + A22*B22
    MatrixMult(A, ax + h,  ay,      B, bx,      by + h,  C, cx + h,  cy + h,  h);
    MatrixMult(A, ax + h,  ay + h,  B, bx + h,  by + h,  C, cx + h,  cy + h,  h);
}


void get(Matrix& tmp){
    for(auto& iter : tmp)
        for(int& i : iter)
            cin >> i;
    
}

void call(const Matrix& tmp){
    for(const auto& iter : tmp){
        for(const int& i : iter){
            cout << i <<' ';
        }
        cout << '\n';
    }
}

int main(){

    int n;
    cin >> n;


    Matrix A(n, Row(n, 0)), B, C;
    C = B = A;

    get(A);
    get(B);

    MatrixMult(A, 0, 0, B, 0, 0, C, 0, 0, n);

    call(C);

    return 0;
}
