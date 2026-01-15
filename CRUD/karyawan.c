#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Define file handling variables here to avoid multiple definitions
FILE *fp_karyawan;
const char fileName_karyawan[] = "karyawan.csv";
FILE *temp;
const char fileName_temp[] = "temp.csv";

/* ===============================
   TAMBAH KARYAWAN
   =============================== */
void tambah_k(struct karyawan *k) {
    char line[200];

    while (1) {
        int jml_k = 0;

        fp_karyawan = fopen(fileName_karyawan, "a+");
        if (!fp_karyawan) {
            printf("%s tidak dapat dibuka\n", fileName_karyawan);
            return;
        }

        /* Tulis header jika file kosong */
        fseek(fp_karyawan, 0, SEEK_END);
        if (ftell(fp_karyawan) == 0) {
            fprintf(fp_karyawan, "No;ID;Nama;Jabatan\n");
        }

        /* Hitung jumlah karyawan */
        rewind(fp_karyawan);
        fgets(line, sizeof(line), fp_karyawan); // skip header
        while (fgets(line, sizeof(line), fp_karyawan)) {
            jml_k++;
        }

        /* Ambil semua ID untuk validasi unik */
        int *cek_id = malloc(sizeof(int) * (jml_k > 0 ? jml_k : 1));
        int cek = 0;

        rewind(fp_karyawan);
        fgets(line, sizeof(line), fp_karyawan);
        while (fgets(line, sizeof(line), fp_karyawan)) {
            int no, id;
            if (sscanf(line, "%d;%d;", &no, &id) == 2) {
                cek_id[cek++] = id;
            }
        }

        clear();
        printf("=== Tambah Karyawan ===\n");

        printf("Nama    : ");
        scanf(" %49[^\n]", k->nama);

        /* Validasi ID unik */
        while (1) {
            int ada = 0;
            printf("ID      : ");
            scanf("%d", &k->id);

            int i;
            for (i = 0; i < cek; i++) {
                if (k->id == cek_id[i]) {
                    ada = 1;
                    break;
                }
            }

            if (ada)
                printf("ID sudah digunakan!\n");
            else
                break;
        }

        printf("Jabatan : ");
        scanf(" %29[^\n]", k->jabatan);

        printf("\nSimpan data (y/n)? ");
        char c;
        scanf(" %c", &c);

        if (c == 'n' || c == 'N') {
            free(cek_id);
            fclose(fp_karyawan);
            continue;
        }

        fprintf(fp_karyawan, "%d;%d;%s;%s\n",
                jml_k + 1, k->id, k->nama, k->jabatan);

        free(cek_id);
        fclose(fp_karyawan);
        break;
    }

    printf("\nData berhasil disimpan\n");
    printf("Tekan enter...");
    getchar(); getchar();
}

/* ===============================
   LIHAT / EDIT / HAPUS
   =============================== */
void lihat_data_k(struct karyawan *k) {
    char line[200];

    fp_karyawan = fopen(fileName_karyawan, "r");
    if (!fp_karyawan) {
        printf("Data karyawan masih kosong\n");
        getchar(); getchar();
        return;
    }

    clear();
    printf("==================== DATA KARYAWAN ===================\n");
    printf("%-5s %-10s %-25s %-20s\n", "No", "ID", "Nama", "Jabatan");
    printf("------------------------------------------------------\n");

    fgets(line, sizeof(line), fp_karyawan); // skip header
    while (fgets(line, sizeof(line), fp_karyawan)) {
        int no, id;
        char nama[50], jabatan[30];
        if (sscanf(line, "%d;%d;%49[^;];%29[^\n]",
                   &no, &id, nama, jabatan) == 4) {
            printf("%-5d %-10d %-25s %-20s\n",
                   no, id, nama, jabatan);
        }
    }
    fclose(fp_karyawan);

    printf("======================================================\n");
    printf("1. Edit\n2. Hapus\n0. Kembali\n");

    while (1) {
        char pilih;
        printf("Pilih: ");
        scanf(" %c", &pilih);

        /* ============ EDIT ============ */
        if (pilih == '1') {
            int id_edit, ditemukan = 0;

            printf("Masukkan ID: ");
            scanf("%d", &id_edit);

            fp_karyawan = fopen(fileName_karyawan, "r");
            temp = fopen(fileName_temp, "w");

            fgets(line, sizeof(line), fp_karyawan);
            fputs(line, temp);

            while (fgets(line, sizeof(line), fp_karyawan)) {
                int no, id;
                char nama[50], jabatan[30];

                sscanf(line, "%d;%d;%49[^;];%29[^\n]",
                       &no, &id, nama, jabatan);

                if (id == id_edit) {
                    ditemukan = 1;
                    int p;
                    printf("1. Nama\n2. Jabatan\nPilih: ");
                    scanf("%d", &p);

                    if (p == 1) {
                        printf("Nama baru: ");
                        scanf(" %49[^\n]", nama);
                    } else if (p == 2) {
                        printf("Jabatan baru: ");
                        scanf(" %29[^\n]", jabatan);
                    }
                }

                fprintf(temp, "%d;%d;%s;%s\n", no, id, nama, jabatan);
            }

            fclose(fp_karyawan);
            fclose(temp);

            if (!ditemukan) {
                printf("ID tidak ditemukan\n");
                remove(fileName_temp);
            } else {
                remove(fileName_karyawan);
                rename(fileName_temp, fileName_karyawan);
                printf("Data berhasil diubah\n");
            }
            break;
        }

        /* ============ HAPUS ============ */
        else if (pilih == '2') {
            int id_hapus, ditemukan = 0, no_baru = 1;

            printf("Masukkan ID: ");
            scanf("%d", &id_hapus);

            fp_karyawan = fopen(fileName_karyawan, "r");
            temp = fopen(fileName_temp, "w");

            fgets(line, sizeof(line), fp_karyawan);
            fputs(line, temp);

            while (fgets(line, sizeof(line), fp_karyawan)) {
                int no, id;
                char nama[50], jabatan[30];

                sscanf(line, "%d;%d;%49[^;];%29[^\n]",
                       &no, &id, nama, jabatan);

                if (id == id_hapus) {
                    ditemukan = 1;
                    continue;
                }

                fprintf(temp, "%d;%d;%s;%s\n",
                        no_baru++, id, nama, jabatan);
            }

            fclose(fp_karyawan);
            fclose(temp);

            if (!ditemukan) {
                printf("ID tidak ditemukan\n");
                remove(fileName_temp);
            } else {
                remove(fileName_karyawan);
                rename(fileName_temp, fileName_karyawan);
                printf("Data berhasil dihapus\n");
            }
            break;
        }

        else if (pilih == '0') {
            return;
        }

        else {
            printf("Pilihan tidak valid\n");
        }
    }

    printf("Tekan enter...");
    getchar(); getchar();
}

/* ===============================
   MENU KARYAWAN
   =============================== */
void menu_karyawan(struct karyawan *k) {
    while (1) {
        clear();
        printf("=== MENU MANAJEMEN KARYAWAN ===\n");
        printf("1. Tambah Karyawan\n");
        printf("2. Lihat Data Karyawan\n");
        printf("0. Keluar\n");
        printf("Pilih: ");

        int pilih;
        scanf("%d", &pilih);

        if (pilih == 1)
            tambah_k(k);
        else if (pilih == 2)
            lihat_data_k(k);
        else if (pilih == 0)
            return;
        else {
            printf("Pilihan tidak valid\n");
            getchar(); getchar();
        }
    }
}
