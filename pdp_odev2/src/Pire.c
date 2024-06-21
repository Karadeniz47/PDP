#include "Pire.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Pire yeni_pire(int sayi,int x, int y)
{
    Pire this;
     this = (Pire)malloc(sizeof(struct PIRE));
     if (this == NULL) {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }
    this->super = yeni_bocek(sayi,x,y);
    
    this->super->super->catismakontrol = &pire_catisma_kontrol;
    this->super->super->gorunum = &pire_gorunum;
    this->piresil = &piresil;
    return this;
}
int pire_catisma_kontrol(Canli this,Canli diger,int habitat_satir_sayisi,int habitat_sutun_sayisi)
{
    if (this == NULL || diger == NULL) {
        return 0;  // Null kontrolü
    }

     // Sinek, Pire'yi yenebilir
    if (diger->sayi >= 21 && diger->sayi <= 50) {
        return -1;  
    }

    // Böcek, Pire'yi yenebilir
    if (diger->sayi >= 10 && diger->sayi <= 20) {
        return -1;  
    }
    //Bitki Pire yi yenebilir
    if(diger->sayi>=1 && diger->sayi<=9)
    {
        return -1;
    }

    // Eşitlik  karşılaştırma
    if (this->sayi == diger->sayi) {
       
       float d1 = sqrt(pow(((habitat_satir_sayisi-1)-this->x),2) + pow(((habitat_sutun_sayisi-1)-this->y),2));
        float d2 = sqrt(pow(((habitat_satir_sayisi-1)-diger->x),2) + pow(((habitat_sutun_sayisi-1)-diger->y),2));
       
       return(d1>d2) ? -1 : 1;
    }

    return (this->sayi > diger->sayi) ? 1 : -1;  // Sayısal değere dayalı karşılaştırma

}

char* pire_gorunum()
{
    return "P";
}
void piresil(Pire this)
{
    if(this == NULL) return;
    if (this->super != NULL) {  
        this->super->boceksil(this->super);
    }
    free(this);
    this = NULL;
   
}