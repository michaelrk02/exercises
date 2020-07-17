// Aljabar Boolean
//
// Deskripsi latihan:
//  Sebuah Peraga angka digital disusun oleh tujuh buah segmen
//  (selanjutnya disebut dekoder tujuh-segmen).
//
//  Piranti tersebut mengubah masukan 4-bit menjadi keluaran yang
//  dapat menunjukkan angka desimal yang dinyatakannya
//  (misalnya, jika masukan adalah 0100 (angka 4 dalam desimal),
//  maka batang/segmen yang menyala adalah a, d, c, dan e).
//  Tulislah fungsi Boolean untuk setiap segmen, dan gambarkan
//  rangkaian kombinasionalnya.
//
// Link: http://informatika.stei.itb.ac.id/~rinaldi.munir/Matdis/2019-2020/Aljabar-Boolean-2019.pdf
#include <iostream>
#include <vector>
#include <map>

#ifdef DEBUG
#define DUMP(x) ::std::cout << #x << ": " << (x) << ::std::endl
#else
#define DUMP(x)
#endif

typedef int Cell;
#define CELL(r,c)   ((((r) & 0xFFFF) << 16) | ((c) & 0xFFFF))
#define CELL_R(c)   (((c) >> 16) & 0xFFFF)
#define CELL_C(c)   ((c) & 0xFFFF)

typedef int SegID;
#define SEG_EMPTY -1
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6

// used to invert a 2-bit value stored as a >2-bit data
#define inv(x) (~x & 0x1)

// Simplified with Karnaugh map SOP
#define COMPUTE_A(w,x,y,z) (w | inv(w) & x & inv(y) | inv(y) & inv(z) | inv(w) & x & y & inv(z))
#define COMPUTE_B(w,x,y,z) (w | y | x & z | inv(w) & inv(x) & inv(y) & inv(z))
#define COMPUTE_C(w,x,y,z) (inv(w) & inv(x) | w | inv(y) & inv(z) | y & z)
#define COMPUTE_D(w,x,y,z) (w | inv(w) & x & inv(y) | inv(w) & inv(x) & y | y & inv(z))
#define COMPUTE_E(w,x,y,z) (inv(y) | w | y & z | inv(w) & x & y)
#define COMPUTE_F(w,x,y,z) (w | y & inv(z) | inv(w) & inv(x) & y | inv(w) & inv(x) & inv(y) & inv(z) | inv(w) & x & inv(y) & z)
#define COMPUTE_G(w,x,y,z) (inv(w) & y & inv(z) | inv(x) & inv(y) & inv(z))

//   0123
// 0 BBBB
// 1 A  C
// 2 A  C
// 3 DDDD
// 4 G  E
// 5 G  E
// 6 FFFF
struct Board {
    int rows, cols;
    std::vector<SegID> cells;
    std::map<SegID, bool> activated;
};

#define CELL_ASSIGN(var,segid,arr) var[segid] = std::vector<Cell>(std::begin(arr), std::end(arr))

void Board_reset(Board *brd) {
    brd->activated[SEG_EMPTY] = true;
    brd->activated[SEG_A] = false;
    brd->activated[SEG_B] = false;
    brd->activated[SEG_C] = false;
    brd->activated[SEG_D] = false;
    brd->activated[SEG_E] = false;
    brd->activated[SEG_F] = false;
    brd->activated[SEG_G] = false;
}

Board *Board_create(void) {
    Board *brd = new Board;

    brd->rows = 7;
    brd->cols = 4;
    brd->cells = std::vector<SegID>(brd->rows * brd->cols);

    std::map<SegID, std::vector<Cell>> cellMapping;

    Cell aCells[] = {CELL(1, 0), CELL(2, 0)};
    CELL_ASSIGN(cellMapping, SEG_A, aCells);

    Cell bCells[] = {CELL(0, 0), CELL(0, 1), CELL(0, 2), CELL(0, 3)};
    CELL_ASSIGN(cellMapping, SEG_B, bCells);

    Cell cCells[] = {CELL(1, 3), CELL(2, 3)};
    CELL_ASSIGN(cellMapping, SEG_C, cCells);

    Cell dCells[] = {CELL(3, 0), CELL(3, 1), CELL(3, 2), CELL(3, 3)};
    CELL_ASSIGN(cellMapping, SEG_D, dCells);

    Cell eCells[] = {CELL(4, 3), CELL(5, 3)};
    CELL_ASSIGN(cellMapping, SEG_E, eCells);

    Cell fCells[] = {CELL(6, 0), CELL(6, 1), CELL(6, 2), CELL(6, 3)};
    CELL_ASSIGN(cellMapping, SEG_F, fCells);

    Cell gCells[] = {CELL(4, 0), CELL(5, 0)};
    CELL_ASSIGN(cellMapping, SEG_G, gCells);

    Cell emptyCells[] = {CELL(1, 1), CELL(1, 2), CELL(2, 1), CELL(2, 2), CELL(4, 1), CELL(4, 2), CELL(5, 1), CELL(5, 2)};
    CELL_ASSIGN(cellMapping, SEG_EMPTY, emptyCells);

    for (std::map<SegID, std::vector<Cell>>::iterator p = cellMapping.begin();
        p != cellMapping.end();
        ++p) {
        for (int i = 0; i < p->second.size(); i++) {
            Cell c = p->second[i];
            int pos = CELL_R(c) * brd->cols + CELL_C(c);
            brd->cells[pos] = p->first;
        }
    }

    Board_reset(brd);

    return brd;
}

void Board_feed(Board *brd, int n) {
    if ((n < 0) || (n > 9)) {
        return;
    }

    unsigned int w = (n >> 3) & 0x1;
    unsigned int x = (n >> 2) & 0x1;
    unsigned int y = (n >> 1) & 0x1;
    unsigned int z = (n) & 0x1;

    brd->activated[SEG_A] = COMPUTE_A(w, x, y, z) == 1;
    brd->activated[SEG_B] = COMPUTE_B(w, x, y, z) == 1;
    brd->activated[SEG_C] = COMPUTE_C(w, x, y, z) == 1;
    brd->activated[SEG_D] = COMPUTE_D(w, x, y, z) == 1;
    brd->activated[SEG_E] = COMPUTE_E(w, x, y, z) == 1;
    brd->activated[SEG_F] = COMPUTE_F(w, x, y, z) == 1;
    brd->activated[SEG_G] = COMPUTE_G(w, x, y, z) == 1;
}

void Board_display(Board *brd) {
    for (int i = 0; i < brd->rows; i++) {
        for (int j = 0; j < brd->cols; j++) {
            SegID segid = brd->cells[i * brd->cols + j];
            if (brd->activated[segid]) {
                if (segid == SEG_EMPTY) {
                    std::cout << " ";
                } else {
                    std::cout << "#";
                }
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Board_destroy(Board *brd) {
    delete brd;
}

int main() {
    Board *brd = Board_create();
    while (true) {
        int num;
        std::cout << "Enter number (0-9): ";
        std::cin >> num;
        if ((num < 0) || (num > 9)) {
            continue;
        }

        Board_feed(brd, num);
        std::cout << "Digital representation:" << std::endl;
        Board_display(brd);
        Board_reset(brd);
    }
    Board_destroy(brd);

    return 0;
}

