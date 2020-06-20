// Gaussian elimination algorithm

#include <iostream>

struct Vector {
    float data[4];
};

union Matrix3x4 {
    Vector r1, r2, r3;
    Vector rows[3];
    float data[3][4];
};

void mulVector(Vector &v, float s) {
    for (int i = 0; i < 4; i++) {
        v.data[i] *= s;
        if (v.data[i] == -0.0f) {
            v.data[i] = 0.0f;
        }
    }
}

void addVector(Vector &v, const Vector &src) {
    for (int i = 0; i < 4; i++) {
        v.data[i] += src.data[i];
    }
}

void printMatrix(const Matrix3x4 &m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << m.data[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {
    Matrix3x4 equation;
    for (int i = 0; i < 3; i++) {
        std::cout << "ROW" << i + 1 << " (A B C D): ";
        for (int j = 0; j < 4; j++) {
            std::cin >> equation.data[i][j];
        }
    }

    for (int i = 1; i < 3; i++) {
        float upperLmnzVal = equation.data[i - 1][i - 1];
        for (int j = i; j < 3; j++) {
            float lmnzVal = equation.data[j][i - 1];

            Vector upperRow = equation.rows[i - 1];
            float factor = -lmnzVal / upperLmnzVal;
            mulVector(upperRow, factor);

            addVector(equation.rows[j], upperRow);
        }
    }

    // SHOULD BE IN ROW ECHELON FORM RIGHT NOW

    for (int i = 1; i >= 0; i--) {
        float lowerLmnzVal = equation.data[i + 1][i + 1];
        for (int j = i; j >= 0; j--) {
            float rmnzVal = equation.data[j][i + 1];

            Vector lowerRow = equation.rows[i + 1];
            float factor = -rmnzVal / lowerLmnzVal;
            mulVector(lowerRow, factor);

            addVector(equation.rows[j], lowerRow);
        }
    }

    // SHOULD BE IN DIAGONAL MATRIX RIGHT NOW

    for (int i = 0; i < 3; i++) {
        float factor = 1.0 / equation.data[i][i];
        mulVector(equation.rows[i], factor);
    }

    // SHOULD BE IN REDUCED ROW ECHELON FORM RIGHT NOW

    std::cout << "Resulting matrix: " << std::endl;
    printMatrix(equation);

    // Print resulting solutions

    std::cout << "Solutions:" << std::endl;
    std::cout << " X: " << equation.data[0][3] << std::endl;
    std::cout << " Y: " << equation.data[1][3] << std::endl;
    std::cout << " Z: " << equation.data[2][3] << std::endl;

    return 0;
}
