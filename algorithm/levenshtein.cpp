// Levenshtein distance - DP approach
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int editDistanceEx(std::vector<int> &storage, const std::string &a, const std::string &b, int i, int j) {
    if (storage[i * b.size() + j] != -1) {
        return storage[i * b.size() + j];
    }
    if (std::min(i, j) == 0) {
        int dist = std::max(i, j);
        storage[i * b.size() + j] = dist;
        return dist;
    }
    int dist = std::min(
        std::min(
            editDistanceEx(storage, a, b, i - 1, j) + 1,
            editDistanceEx(storage, a, b, i, j - 1) + 1
        ),
        editDistanceEx(storage, a, b, i - 1, j - 1) + (a[i - 1] != b[j - 1] ? 1 : 0)
    );
    storage[i * b.size() + j] = dist;
    return dist;
}

int editDistance(const std::string &a, const std::string &b) {
    std::vector<int> storage((a.size() + 1) * (b.size() + 1), -1);
    return editDistanceEx(storage, a, b, a.size(), b.size());
}

int main() {
    std::string a, b;
    std::cout << "Enter two words: ";
    std::cin >> a >> b;
    std::cout << "Levenshtein distance: " << editDistance(a, b) << std::endl;

    return 0;
}

