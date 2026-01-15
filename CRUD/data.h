#ifndef DATA_H
#define DATA_H

#include <stdio.h>

// Data Karywan
struct karyawan {
    int id;             // PK
    char nama[50];
    char jabatan[30];
    int no;
};

// Data Absensi
struct absensi {
    int id_karyawan;    // FK
    int tanggal;
    int bulan;
    int tahun;
    char status; // H/I/S/A
};

// File handling
// File handling (declared extern to avoid multiple definitions)
extern FILE *fp_karyawan;
extern const char fileName_karyawan[];
extern FILE *temp;
extern const char fileName_temp[];

// Panggil function karyawan
void menu_karyawan(struct karyawan* k);
void tambah_k(struct karyawan* k);

// Panggil function clear
void clear(void);

#endif