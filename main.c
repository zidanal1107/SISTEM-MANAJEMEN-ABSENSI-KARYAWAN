#include <stdio.h>
#include "CRUD/data.h"

struct karyawan k = {0};
struct absensi a = {0};

int main() {
    while (1) {
        clear();
        printf("=== MENU UTAMA ===\n");
        printf("1. Manajemen Karyawan\n2. Manajemen Absensi\n3. Rekap Absensi\n0. Keluar\n");
        printf("Pilih: ");
        int pilih;
        scanf("%d", &pilih);

        switch (pilih) {
        case 1:
            menu_karyawan(&k);
            break;
        case 2:
            absensi(&a, &k);
            break;
        case 3:
            rekap();
            break;
        case 0:
            printf("\nProgram selesai!\n");
            return 0;
        default:
            printf("Pilihan hanya ada (0-3)");
            break;
        }
    }
    return 0;
}