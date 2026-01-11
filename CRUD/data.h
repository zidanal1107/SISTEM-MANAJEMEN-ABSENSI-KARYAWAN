#ifndef DATA_H
#define DATA_H

// Data Karywan
struct karyawan {
    int id;             // PK
    char nama[50];
    char jabatan[30];
};

// Data Absensi
struct absensi {
    int id_karyawan;    // FK
    int tanggal;
    int bulan;
    int tahun;
    char status; // H/I/S/A
};

#endif