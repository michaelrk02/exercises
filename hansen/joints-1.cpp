#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    map<string, int> buku;

    int jumlahBuku;
    cin >> jumlahBuku;

    cin.ignore();
    for (int i = 0; i < jumlahBuku; i++) {
        string judul;
        getline(cin, judul);

        if (buku.find(judul) == buku.end()) {
            buku[judul] = 1;
        } else {
            buku[judul] = buku[judul] + 1;
        }
    }

    int no_pelanggan = 1;
    while (true) {
        string pinjam;
        getline(cin, pinjam);

        if (!pinjam.compare("CL")) {
            break;
        } else {
            string judul = pinjam.substr(3, pinjam.length() - 3);
            bool njilih = true;
            if (!pinjam.substr(0, 2).compare("PM")) {
                njilih = true;
            } else {
                njilih = false;
            }

            int mode = -1; // 0:tersedia 1:dikembalikan 2:tidak ada
            if (buku.find(judul) != buku.end()) {
                if (njilih) {
                    if (buku[judul] == 0) {
                        mode = 2;
                    } else {
                        mode = 0;
                        buku[judul] = buku[judul] - 1;
                    }
                } else {
                    mode = 1;
                    buku[judul] = buku[judul] + 1;
                }
            } else {
                mode = 2;
            }

            string pesan;
            switch (mode) {
            case 0:
                pesan = "Buku Tersedia & Berhasil Dipinjam";
                break;
            case 1:
                pesan = "Terima Kasih Telah Membaca :)";
                break;
            case 2:
                pesan = "Maaf Buku Anda Tidak Tersedia, Silahkan Kembali Minggu Depan";
                break;
            }

            cout << "Pelanggan ke-" << no_pelanggan << " : " << pesan << endl;
            no_pelanggan++;
        }
    }

    return 0;
}

