#include <iostream>

using namespace std;

int Q[25][25];
int M, N;

int solve(int i, int j, int c) {
    int T = 0;

    Q[i][j] = 0;
    T++;

    if ((i > 0) && (Q[i - 1][j] == c)) {
        T += solve(i - 1, j, c);
    }
    if ((i < M - 1) && (Q[i + 1][j] == c)) {
        T += solve(i + 1, j, c);
    }
    if ((j > 0) && (Q[i][j - 1] == c)) {
        T += solve(i, j - 1, c);
    }
    if ((j < N - 1) && (Q[i][j + 1] == c)) {
        T += solve(i, j + 1, c);
    }

    return T;
}

int main() {
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> Q[i][j];
        }
    }

    int B, K;
    cin >> B >> K;

    int T = solve(B, K, Q[B][K]);
    cout << T * (T - 1) << endl;

    return 0;
}

