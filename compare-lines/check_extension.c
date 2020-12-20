/*
    check_extension.c: berisi definisi untuk fungsi check_extension()

    File ini otomatis ter-include oleh main.c
*/

#include <string.h>

#include "stdinc.h"

#include "begin_code.h"

#ifdef CLAMP
#undef CLAMP
#endif
#define CLAMP(_Str, _Index, _Boundary) \
    ((_Index) >= (_Boundary) ? (_Str)[_Index] : 0x00)

#ifdef issep
#undef issep
#endif
#define issep(_Ch) (((_Ch) == '\\') || ((_Ch) == '/'))

#ifdef INIT_STARTING_POINT
#undef INIT_STARTING_POINT
#endif
#define INIT_STARTING_POINT(_PathStr, _Var) \
    for (_Var = strlen(_PathStr) - 1; _Var >= 0; _Var--) { \
        if (issep((_PathStr)[_Var])) { \
            _Var++; \
            break; \
        } \
    } \
    if (_Var == -1) { \
        _Var = 0; \
    }

#ifdef CHECK_HIDDEN_FILENAME
#undef CHECK_HIDDEN_FILENAME
#endif
#ifdef _WIN32
#define CHECK_HIDDEN_FILENAME(_PathStr, _StartVar) \
    while ((_PathStr)[_StartVar] == '.') { \
        _StartVar++; \
    }
#else
#define CHECK_HIDDEN_FILENAME(_PathStr, _StartVar)
#endif

/*
    Mekanisme pengecekan ekstensi:

    Linux / macOS X:
    [CONTOH NAMA FILE]          [EKSTENSI]      [BASENAME]
    - php.ini                   -> .ini         php.ini
    - /var/www/index.html       -> .html        index.html
    - mirrorlist                -> tidak ada    mirrorlist
    - /etc/pacman.d/mirrorlist  -> tidak ada    mirrorlist
    - .hide.me                  -> .me          hide.me
    - /var/www/.htaccess        -> tidak ada    htaccess

    Windows:
    [CONTOH NAMA FILE]          [EKSTENSI]      [BASENAME]
    - autoexec.bat              -> .bat         autoexec.bat
    - C:\Windows\notepad.exe    -> .exe         notepad.exe
    - ThisIsAFile               -> tidak ada    ThisIsAFile
    - C:\Windows\System32       -> tidak ada    System32
    - .htaccess                 -> .htaccess    .htaccess
    - C:\Linux Emu\.hide.me     -> .me          .hide.me

    Algoritma pengecekan ekstensi yang saya buat adalah sbb:
    1. Menentukan basename dari nama file (dapat dilihat pada contoh di atas)
    2. Membandingkan karakter-karakter pada basename dimulai dari karakter terakhir masing-masing basename dengan loop
        - Jika terdapat perbedaan karakter, increment jumlah karakter yang berbeda
        - Jika salah satu karakter yang dibandingkan adalah titik (.), maka fungsi langsung mengeluarkan hasil TRUE/FALSE di mana TRUE jika keduanya berupa titik dan tidak ada perbedaan karakter pada ekstensi (implikasinya, memiliki ekstensi yang sama)
    3. Jika salah satu basename dengan posisi perbandingan sudah keluar dari batas (kurang dari posisi karakter pertama basename atau posisi negatif), maka loop tetap berjalan dengan ketentuan sbb:
        - Jika karakter yang masih ada di dalam batas berupa titik, implikasinya adalah salah satu file tidak memilik ekstensi dan satu file lain ternyata memiliki ekstensi. Dengan demikian, fungsi langsung mengembalikan nilai FALSE
    4. Jika kedua basename dengan posisi perbandingan tidak lagi berada dalam jangkauan, maka artinya kedua file tsb tidak memiliki ekstensi, maka return TRUE (sama-sama tidak memiliki ekstensi)
*/
bool check_extension(const char *name1, const char *name2) {
    int i, j, k, u, v, diff = 0;

    INIT_STARTING_POINT(name1, u);
    INIT_STARTING_POINT(name2, v);

    TRACE("sebelum mengecek hidden filename:");
    DUMP(d, u);
    DUMP(d, v);

    CHECK_HIDDEN_FILENAME(name1, u);
    CHECK_HIDDEN_FILENAME(name2, v);

    TRACE("setelah mengecek hidden filename:");
    DUMP(d, u);
    DUMP(d, v);

    i = strlen(name1) - 1;
    j = strlen(name2) - 1;

    /* cek apakah nama file diakhiri oleh sebuah titik */
    i = name1[i] == '.' ? i - 1 : i;
    j = name2[j] == '.' ? j - 1 : j;

    for (k = MAX(i, j); k >= MIN(u, v); k--) {
        char ci, cj;

        ci = CLAMP(name1, i, u);
        cj = CLAMP(name2, j, v);
        if ((ci != 0x00) && (cj != 0x00)) {
            if (ci != cj) {
                diff++;
            }
            if ((ci == '.') || (cj == '.')) {
                return (ci == cj) && (diff == 0);
            }
        } else {
            /* dalam kasus ini kedua file seharusnya tidak memiliki ekstensi */

            /* namun jika salah satu masih memiliki ekstensi (terdapat tanda .), maka return false */
            if (MAX(ci, cj) == '.') {
                return false;
            }
        }

        i--;
        j--;
    }

    return true;
}

#include "end_code.h"

