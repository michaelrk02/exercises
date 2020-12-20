/* baris di bawah ini dapat di comment/tidak tergantung penggunaan */
#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdinc.h"

#include "begin_code.h"

#ifdef MAXLINECHARS
#undef MAXLINECHARS
#endif
#define MAXLINECHARS    511

#ifdef LINEBUFSIZE
#undef LINEBUFSIZE
#endif
#define LINEBUFSIZE     (MAXLINECHARS + 1)

int main() {
    puts("Ketuk Ctrl+C untuk keluar dari program sewaktu-waktu");
    while (true) {
        FILE *fp1, *fp2;
        char fname1[512], fname2[512];
        queue_t q;

        q_init(&q, free);

        printf("Masukkan nama file 1: ");
        scanf("%511[^\n]%*c", fname1);

        printf("Masukkan nama file 2: ");
        scanf("%511[^\n]%*c", fname2);

        if (!check_extension(fname1, fname2)) {
            char choice;

            puts("File tersebut memiliki tipe yang berbeda");
            printf("Apakah ingin lanjut mengecek? (y/N) ");
            scanf("%c%*c", &choice);

            if (!((choice == 'Y') || (choice == 'y'))) {
                continue;
            }
        }

        fp1 = fopen(fname1, "r");
        fp2 = fopen(fname2, "r");
        if ((fp1 != NULL) && (fp2 != NULL)) {
            int lineno = 1;
            char linebuf1[LINEBUFSIZE], linebuf2[LINEBUFSIZE];
            int similarities = 0;

            puts("Membaca file ...");
            while (true) {
                int read1, read2;
                linedata_t *data;

                DUMP(d, lineno);
                memset(linebuf1, 0, LINEBUFSIZE);
                memset(linebuf2, 0, LINEBUFSIZE);

                read1 = fscanf(fp1, "%" STRINGIZE(MAXLINECHARS) "[^\n]", linebuf1);
                read2 = fscanf(fp2, "%" STRINGIZE(MAXLINECHARS) "[^\n]", linebuf2);
                if ((read1 != EOF) && (read2 != EOF)) {
                    if ((read1 == 0) || (read2 == 0)) {
                        break;
                    }
                    DUMP(d, read1);
                    DUMP(d, read2);

                    /* cek jika line yang discan melebihi kapasitas, maka atur posisi kursor menjadi setelah posisi newline berikutnya */
                    if (linebuf1[MAXLINECHARS - 1] != 0x00) {
                        char ch;
                        while ((ch = (char)fgetc(fp1)) != '\n') {
                        }
                    } else {
                        fscanf(fp1, "%*c");
                    }
                    if (linebuf2[MAXLINECHARS - 1] != 0x00) {
                        char ch;
                        while ((ch = (char)fgetc(fp2)) != '\n') {
                        }
                    } else {
                        fscanf(fp2, "%*c");
                    }

                    DUMP(s, linebuf1);
                    DUMP(s, linebuf2);

                    if (strcmp(linebuf1, linebuf2) == 0) {
                        data = (linedata_t *)malloc(sizeof(linedata_t));
                        data->number = lineno;
                        strcpy(data->contents, linebuf1);
                        q_enqueue(&q, data);
                        similarities++;
                    }

                    lineno++;
                } else {
                    break;
                }
            }

            printf("Terdapat %d kesamaan baris dalam kedua file tersebut\n", similarities);

            while (true) {
                int choice;

                puts("Tindakan:");
                puts(" [1] Tampilkan kesamaan");
                puts(" [lainnya] Kembali");
                printf("Pilihan: ");
                scanf("%d%*c", &choice);

                if (choice == 1) {
                    puts("=== DATA KESAMAAN ===");
                    q_print(&q);
                } else {
                    break;
                }
            }
        } else {
            ERROR("kedua file tidak dapat dibuka");
        }

        if (fp1 != NULL) {
            fclose(fp1);
        }
        if (fp2 != NULL) {
            fclose(fp2);
        }
    }

    return 0;
}

#include "end_code.h"

#include "check_extension.c"
#include "stack.c"
#include "queue.c"

