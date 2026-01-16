#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

FILE *fp_absensi;
const char fileName_absensi[] = "absensi.csv";

void absensi(struct absensi *a, struct karyawan *k) {
    char line[200];
    int id_ditemukan;

    /* ================= CEK ID KARYAWAN ================= */
    while (1) {
        clear();
        printf("=== ABSENSI KARYAWAN ===\n");
        printf("Masukkan ID Karyawan : ");
        scanf("%d", &a->id_karyawan);

        fp_karyawan = fopen(fileName_karyawan, "r");
        if (!fp_karyawan) {
            printf("File karyawan tidak ditemukan!\n");
            getchar(); getchar();
            return;
        }

        id_ditemukan = 0;
        fgets(line, sizeof(line), fp_karyawan); // skip header

        while (fgets(line, sizeof(line), fp_karyawan)) {
            int no, id;
            char nama[50], jabatan[30];

            if (sscanf(line, "%d;%d;%49[^;];%29[^\n]",
                       &no, &id, nama, jabatan) == 4) {
                if (id == a->id_karyawan) {
                    id_ditemukan = 1;
                    break;
                }
            }
        }
        fclose(fp_karyawan);

        if (!id_ditemukan) {
            printf("ID tidak ditemukan!\n");
            getchar(); getchar();
        } else {
            break;
        }
    }

    /* ================= INPUT TANGGAL ================= */
    printf("Tanggal (1-31)        : ");
    scanf("%d", &a->tanggal);

    printf("Bulan (1-12)          : ");
    scanf("%d", &a->bulan);

    printf("Tahun                : ");
    scanf("%d", &a->tahun);

    while (1) {
        printf("Status (H/I/S/A)      : ");
        scanf(" %c", &a->status);

        if (a->status == 'H' || a->status == 'I' ||
            a->status == 'S' || a->status == 'A') {
            break;
        }
        printf("Masukkan H / I / S / A!\n");
    }

    /* ================= SIMPAN KE FILE ================= */
    fp_absensi = fopen(fileName_absensi, "a+");
    if (!fp_absensi) {
        printf("Gagal membuka file absensi!\n");
        getchar(); getchar();
        return;
    }

    fseek(fp_absensi, 0, SEEK_END);
    if (ftell(fp_absensi) == 0) {
        fprintf(fp_absensi, "ID;Tanggal;Bulan;Tahun;Status\n");
    }

    fprintf(fp_absensi, "%d;%d;%d;%d;%c\n",
            a->id_karyawan,
            a->tanggal,
            a->bulan,
            a->tahun,
            a->status);

    fclose(fp_absensi);

    printf("\nAbsensi berhasil dicatat...\n");
    getchar(); getchar();
}
