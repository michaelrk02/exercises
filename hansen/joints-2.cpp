#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Status {
    BALIK_AJA,
    TERPAKSA,
    SENANG,
};

int main() {
    int n, r, c;
    cin >> n >> r >> c;

    vector<string> seat;
    seat.resize(r);
    for (int i = 0; i < r; i++) {
        cin >> seat[i];
    }

    string emptyGroup;
    for (int i = 0; i < n; i++) {
        emptyGroup += "O";
    }

    Status status = Status::BALIK_AJA;
    bool keepUpRow = true;
    for (string& row : seat) {
        if (keepUpRow) {
            for (int i = 0; i < c; i++) {
                if (i + n <= c) {
                    if (row.substr(i, n) == emptyGroup) {
                        status = Status::TERPAKSA;

                        int left = i - 1;
                        int right = i + n - 1;
                        bool kiri_perempuan = false;
                        bool kanan_perempuan = false;

                        if (left >= 0) {
                            kiri_perempuan = (row[left] == 'P');
                        }

                        if (right <= c - 1) {
                            kanan_perempuan = (row[right] == 'P');
                        }

                        if (!kiri_perempuan && !kanan_perempuan) {
                            status = Status::SENANG;
                            keepUpRow = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    switch (status) {
    case Status::BALIK_AJA:
        cout << "BALIK AJA" << endl;
        break;
    case Status::TERPAKSA:
        cout << "TERPAKSA" << endl;
        break;
    case Status::SENANG:
        cout << "SENANG" << endl;
        break;
    }

    return 0;
}

