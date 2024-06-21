#ifndef HABITAT_H
#define HABITAT_H
#include "Canli.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"

struct HABITAT
{
    int satir_sayisi; // Matrisin satır sayısı
    int sutun_sayisi; // Matrisin sütun sayısı
    Canli *c;
    void **p;
    void (*HabitatYoket)(struct HABITAT *);
    int (*HabitatDosyadanOku)(struct HABITAT *, const char *);
    void (*HabitatGoruntule)(struct HABITAT *);
    void (*HabitatSurecBaslat)(struct HABITAT *);
    void (*EkranTemizle)();
};
typedef struct HABITAT *Habitat;
Habitat yeni_Habitat();
void HabitatYoket(Habitat);
int HabitatDosyadanOku(Habitat, const char *);
void HabitatGoruntule(Habitat);
void EkranTemizle();
void HabitatSurecBaslat(Habitat);
#endif