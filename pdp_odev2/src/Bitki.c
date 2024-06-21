#include "Bitki.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Bitki yeni_Bitki(int sayi, int x, int y)
{
    Bitki this;
    this = (Bitki)malloc(sizeof(struct BITKI));
    if (this == NULL)
    { // Bellek tahsisi başarısız olursa
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }
    this->super = YeniCanli(sayi, x, y);
    if (this->super == NULL)
    { // Canlı tahsisi başarısız olursa
        free(this);
        return NULL;
    }
    this->super->catismakontrol = &bitki_catisma_kontrol;
    this->super->gorunum = &bitki_gorunum;
    this->bitkisil = &bitkisil;

    return this;
}

int bitki_catisma_kontrol(Canli this, Canli diger, int habitat_satir_sayisi, int habitat_sutun_sayisi)
{
    if (this == NULL || diger == NULL)
    {
        return 0; // Null kontrolü
    }

    // Bitki'nin Sinek ve Pire ile çatışma durumu
    if (diger->sayi >= 21 && diger->sayi <= 50)
    {
        return 1; // Bitki, Sinek'i yiyebilir
    }
    else if (diger->sayi >= 51 && diger->sayi <= 99)
    {
        return 1; // Bitki, Pire'yi de yiyebilir
    }

    // Böcekler bitkileri yiyebilir
    if (diger->sayi >= 10 && diger->sayi <= 20)
    {
        return -1; // Böcek, Bitki'yi yiyebilir
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

char *bitki_gorunum()
{

    return "B";
}

void bitkisil(Bitki this)
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