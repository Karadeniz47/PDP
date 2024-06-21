#include "Bocek.h"
#include "Habitat.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Bocek yeni_bocek(int sayi, int x, int y)
{
    Bocek this;
    this = (Bocek)malloc(sizeof(struct BOCEK));
    if (this == NULL)
    { // Bellek tahsisi başarısız olursa
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }
    this->super = YeniCanli(sayi, x, y);
    if (this->super == NULL)
    { // YeniCanli başarısız olursa
        free(this);
        return NULL;
    }
    this->super->catismakontrol = &bocek_catisma_kontrol;
    this->super->gorunum = &bocek_gorunum;
    this->boceksil = &boceksil;
    return this;
}

int bocek_catisma_kontrol(Canli this, Canli diger, int habitat_satir_sayisi, int habitat_sutun_sayisi)
{
    if (this == NULL || diger == NULL)
    {
        return 0; // Null kontrolü
    }

    // Böcek, Bitki'yi yiyebilir
    if (diger->sayi >= 1 && diger->sayi <= 9)
    {
        return 1; // Böcek, Bitki'yi yiyebilir
    }

    // Böcek, Pire'yi yenebilir
    if (diger->sayi >= 51 && diger->sayi <= 99)
    {
        return 1; // Böcek, Pire'yi yiyebilir
    }

    // Böcek, Sinek tarafından yenilebilir
    if (diger->sayi >= 21 && diger->sayi <= 50)
    {
        return -1; // Sinek, Böcek'i yenebilir
    }

    // Eşitlik durumu  karşılaştırma
    if (this->sayi == diger->sayi)
    {
        float d1 = sqrt(pow(((habitat_satir_sayisi - 1) - this->x), 2) + pow(((habitat_sutun_sayisi - 1) - this->y), 2));
        float d2 = sqrt(pow(((habitat_satir_sayisi - 1) - diger->x), 2) + pow(((habitat_sutun_sayisi - 1) - diger->y), 2));

        return (d1 > d2) ? -1 : 1;
    }

    return (this->sayi > diger->sayi) ? 1 : -1; // Sayısal değere dayalı karşılaştırma
}

char *bocek_gorunum()
{
    return "C";
}

void boceksil(Bocek this)
{
    if (this == NULL)
        return;
    if (this->super != NULL)
    {
        this->super->canlisil(this->super);
    }
    free(this);
    this = NULL;
}