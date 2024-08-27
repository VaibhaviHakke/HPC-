#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void matrixMultiplySerial(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size(); // Assuming square matrices

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 3; // Size of the matrix (small size for demonstration)

    // Initialize matrices with values
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    vector<vector<int>> C(n, vector<int>(n, 0));

    auto start = chrono::high_resolution_clock::now();
    matrixMultiplySerial(A, B, C);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << "Serial Execution Time: " << duration.count() << " seconds" << endl;

    cout << "Matrix C:" << endl;
    for (const auto& row : C) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

