#include "graph.h"

void run_menu()
{
    printf("╔══════════════════════════════════════╗\n");
    printf("║                                      ║\n");
    printf("║    Útvonaltervező rendszer           ║\n");
    printf("║    Kötelező nagy házi feladat | C    ║\n");
    printf("║                                      ║\n");
    printf("╚══════════════════════════════════════╝\n");

    int choice;
    do
    {
        printf("\n╔═══ Fő menü ════╗\n");
        printf("║ 1) Térkép        ║\n");
        printf("║ 2) Útvonalak     ║\n");
        printf("║ 3) Szállítások   ║\n");
        printf("║ 4) Fájl I/O      ║\n");
        printf("║ 0) Kilépés       ║\n");
        printf("╚══════════════════╝\n");
        choice = read_int("Válassz egy opciót: ");

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            printf("\n Kilépés folyamatban...\n\n");
            break;
        default:
            printf("[!] Ismeretlen opció.\n");
        }
    } while (choice != 0);
}

int main()
{
    run_menu();
    return 0;
}
