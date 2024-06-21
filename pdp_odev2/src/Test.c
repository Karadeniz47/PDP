#include <stdio.h>
#include <conio.h>
#include "Habitat.h"
int main()
{
    Habitat h = yeni_Habitat();
    h->HabitatDosyadanOku(h,"Veri.txt");
    h->HabitatGoruntule(h);
    while (!_kbhit()) {
        // Bekle
    }
    getch();
     h->HabitatSurecBaslat(h);
     h->HabitatYoket(h);
}
