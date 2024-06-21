#include "Sinek.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Sinek yeni_sinek(int sayi,int x, int y)
{
    Sinek this;
     this = (Sinek)malloc(sizeof(struct SINEK));
      if (this == NULL) {  // Bellek tahsisi başarısız olursa
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }
    this->super = yeni_bocek(sayi,x,y);
    this->super->super->catismakontrol = &sinek_catisma_kontrol;
    this->super->super->gorunum = &sinek_gorunum;
    this->sineksil = &sineksil;
    return this;
}

int sinek_catisma_kontrol(Canli this,Canli diger,int habitat_satir_sayisi,int habitat_sutun_sayisi)
{
     if (this == NULL || diger == NULL) {
        return 0;  // Null kontrolü
    }

    // Sinek, Pire'yi yiyebilir
    if (diger->sayi >= 51 && diger->sayi <= 99) {
        return 1;  // Sinek, Pire'yi yiyebilir
    }

    // Sinek, Böcek'i yenebilir
    if (diger->sayi >= 10 && diger->sayi <= 20) {
        return 1;  // Sinek, Böcek'i yenebilir
    }

    // Bitki, Sinek'i yiyebilir
    if (diger->sayi >= 1 && diger->sayi <= 9) {
        return -1;  // Bitki, Sinek'i yenebilir
    }

     // Eşitlik durumu  karşılaştırma
    if (this->sayi == diger->sayi) {
       float d1 = sqrt(pow(((habitat_satir_sayisi-1)-this->x),2) + pow(((habitat_sutun_sayisi-1)-this->y),2));
        float d2 = sqrt(pow(((habitat_satir_sayisi-1)-diger->x),2) + pow(((habitat_sutun_sayisi-1)-diger->y),2));
       
       return(d1>d2) ? -1 : 1;
    }

    return (this->sayi > diger->sayi) ? 1 : -1;  // Sayısal değere dayalı karşılaştırma
}
char* sinek_gorunum()
{
    return "S";
}

void sineksil(Sinek this)
{
    if(this == NULL) return;
    if (this->super != NULL) {
        this->super->boceksil(this->super);  
    }
    free(this);
    this = NULL;
   
}