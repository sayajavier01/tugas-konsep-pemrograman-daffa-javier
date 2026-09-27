#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bersihkanBuffer();
int mintaTebakan();
int mintaTaruhan(int total_token);
int mintaKonfirmasiLanjut();
int prosesRonde(int sistem_pilih, int tebakan_user);
void jalankanPermainan();


void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int mintaTebakan() {
    int tebakan;
    printf("Masukkan tebakan Anda (1 / 0): ");

   
    if (scanf("%d", &tebakan) != 1) {
        printf("--> Input tidak valid! Masukkan angka 0 atau 1.\n");
        bersihkanBuffer();
        return mintaTebakan(); // Rekursi
    }

    bersihkanBuffer();
 
    if (tebakan == 0 || tebakan == 1) {
        return tebakan;
    }

    printf("--> Input di luar jangkauan! Pilih 1 atau 0.\n");
    return mintaTebakan(); 
}


int mintaTaruhan(int total_token) {
    int taruhan;
    printf("Masukkan jumlah token yang dipasang (1 - %d): ", total_token);

    if (scanf("%d", &taruhan) != 1) {
        printf("--> Input tidak valid! Masukkan nilai berupa angka.\n");
        bersihkanBuffer();
        return mintaTaruhan(total_token);
    }

    bersihkanBuffer();

    if (taruhan < 1 || taruhan > total_token) {
        printf("--> Jumlah token tidak sesuai jangkauan (1 - %d)!\n", total_token);
        return mintaTaruhan(total_token); 
    }

    return taruhan;
}

int mintaKonfirmasiLanjut() {
    char pil;
    printf("\nMain lagi? (y/n): ");
    
    if (scanf(" %c", &pil) != 1) {
        bersihkanBuffer();
        return mintaKonfirmasiLanjut();
    }

    bersihkanBuffer(); 

    if (pil == 'y' || pil == 'Y') {
        return 1; 
    } else if (pil == 'n' || pil == 'N') {
        return 0; 
    }

    printf("--> Pilihan tidak valid! Harap masukkan 'y' atau 'n'.\n");
    return mintaKonfirmasiLanjut(); 
}


int prosesRonde(int sistem_pilih, int tebakan_user) {
    if (tebakan_user == sistem_pilih) {
        printf("\n========================================\n");
        printf("TEBAKAN BENAR! Angka sistem adalah %d.\n", sistem_pilih);
        return 1; 
    } else {
        printf("\n========================================\n");
        printf("TEBAKAN SALAH! Angka sistem adalah %d.\n", sistem_pilih);
        return 0; 
    }
}


void jalankanPermainan() {
    int total_token = 20; 

    printf("========================================\n");
    printf("           BINER ROULETTE (50:50)       \n");
    printf("========================================\n");
    printf("Selamat datang! Modal awal Anda: %d Token\n", total_token);

    while (total_token > 0) {
        printf("\n----------------------------------------\n");
        printf("JUMLAH TOKEN ANDA SAAT INI: %d\n", total_token);

        
        int taruhan = mintaTaruhan(total_token);
        
        int sistem_pilih = rand() % 2;
       
        int tebakan_user = mintaTebakan();

        int hasil = prosesRonde(sistem_pilih, tebakan_user);

        if (hasil == 1) {
            total_token += taruhan;
            printf("Hasil: Anda menang %d token!\n", taruhan);
        } else {
            total_token -= taruhan;
            printf("Hasil: Token Anda hangus %d.\n", taruhan);
        }

        printf("Sisa token Anda sekarang: %d\n", total_token);
        printf("========================================\n");

        if (total_token > 0) {
            int lanjut = mintaKonfirmasiLanjut();
            if (!lanjut) {
                printf("\nTerimakasih telah bermain! Token akhir Anda: %d\n", total_token);
                break;
            }
        }
    }

    if (total_token <= 0) {
        printf("\n========================================\n");
        printf("GAME OVER! Token Anda telah habis (0).\n");
        printf("========================================\n");
    }
}

int main() {

    srand((unsigned int)time(NULL));

    jalankanPermainan();

    return 0;
}