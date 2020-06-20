#include <iostream>
#include <vector>

using namespace std;

static const int g_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
#define data_len (sizeof(g_data)/sizeof(int))

int main() {
    int width;
    cout << "Specify width: ";
    cin >> width;

    int fullRows = data_len / width;
    int remainder = data_len % width;
    int rows = fullRows + (remainder > 0 ? 1 : 0);
    int rawTransformed[rows][width];
    //vector<vector<int>> rawTransformed(rows, vector<int>(width, -1));

    int pos = 0;
    for (int j = 0; j < rows; j++) {
        if ((j + 1) % 2 != 0) {
            cout << "odd" << endl;
            // odd, go right
            for (int i = 0; i < width; i++) {
                if (pos < data_len) {
                    rawTransformed[j][i] = g_data[pos];
                    pos++;
                }
            }
        } else {
            cout << "even" << endl;
            // even, go left
            for (int i = width - 1; i >= 0; i--) {
                if (pos < data_len) {
                    rawTransformed[j][i] = g_data[pos];
                    pos++;
                }
            }
        }
    }

    vector<vector<int>> transformed(width, vector<int>(rows, -1));
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < width; i++) {
            transformed[i][j] = rawTransformed[j][i];
        }
    }

    // print each row (transposed)
    for (int j = 0; j < width; j++) {
        for (int i = 0; i < rows; i++) {
            if (transformed[j][i] != -1) {
                cout << transformed[j][i];
            } else {
                cout << ' ';
            }
            cout << '\t';
        }
        cout << endl;
    }

    return 0;
}
