#include "Habitat.h"
#include "Canli.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Habitat yeni_Habitat()
{
    Habitat this;
    this = (Habitat)malloc(sizeof(struct HABITAT));

    if (this == NULL)
    {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }

    this->satir_sayisi = 0;
    this->sutun_sayisi = 0;
    this->HabitatYoket = &HabitatYoket;
    this->HabitatDosyadanOku = &HabitatDosyadanOku;
    this->HabitatSurecBaslat = &HabitatSurecBaslat;
    this->EkranTemizle = &EkranTemizle;
    this->HabitatGoruntule = &HabitatGoruntule;

    return this;
}

void HabitatYoket(Habitat this)
{
    if (this == NULL || this->p == NULL || this->c == NULL)
    {
        return;
    }

    int kapasite = this->satir_sayisi * this->sutun_sayisi; // Matris boyutu

    for (int i = 0; i < kapasite; i++)
    {
        if (this->p[i] != NULL && this->c[i] != NULL)
        {
            if (this->c[i]->sayi >= 1 && this->c[i]->sayi <= 9)
            {
                bitkisil((Bitki)this->p[i]);
                this->p[i] = NULL;
            }
            else if (this->c[i]->sayi >= 10 && this->c[i]->sayi <= 20)
            {
                boceksil((Bocek)this->p[i]);
                this->p[i] = NULL;
            }
            else if (this->c[i]->sayi >= 21 && this->c[i]->sayi <= 50)
            {
                sineksil((Sinek)this->p[i]);
            }
            else if (this->c[i]->sayi >= 51 && this->c[i]->sayi <= 99)
            {
                piresil((Pire)this->p[i]);
            }
            else
            {
                printf("HATA\n");
            }
        }
    }

    if (this->p != NULL)
    {
        free(this->p);
        this->p = NULL;
    }

    if (this->c != NULL)
    {
        free(this->c);
        this->c = NULL;
    }

    free(this);
    this = NULL;
}

int HabitatDosyadanOku(Habitat this, const char *dosya_yolu)
{
    if (this == NULL)
    {
        printf("Habitat nesnesi gecersiz.\n");
        return 0;
    }

    FILE *dosya = fopen(dosya_yolu, "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return 0;
    }

    int satir_sayisi = 0;
    int max_sutun_sayisi = 0;
    char satir_buffer[1024];

    while (fgets(satir_buffer, sizeof(satir_buffer), dosya) != NULL)
    {
        satir_sayisi++;
        int sutun = 0;

        char *token = strtok(satir_buffer, " \t\n"); // Boşluklar, tablar ve yeni satırlarla ayır
        while (token != NULL)
        {
            sutun++;
            token = strtok(NULL, " \t\n");
        }

        if (sutun > max_sutun_sayisi)
        {
            max_sutun_sayisi = sutun;
        }
    }

    this->satir_sayisi = satir_sayisi;
    this->sutun_sayisi = max_sutun_sayisi;
    int kapasite = satir_sayisi * max_sutun_sayisi;

    // Bellek tahsisi ve hata kontrolü
    this->p = (void **)malloc(kapasite * sizeof(void *));
    this->c = (Canli *)malloc(kapasite * sizeof(Canli));
    if (this->p == NULL || this->c == NULL)
    {

        free(this->p);
        free(this->c);
        fclose(dosya);
        printf("Bellek tahsisi basarisiz.\n");
        return 0;
    }

    rewind(dosya);

    int satir = 0;
    int sutun = 0;
    int sayac = 0;

    while (fgets(satir_buffer, sizeof(satir_buffer), dosya) != NULL)
    {
        char *token = strtok(satir_buffer, " \t\n");
        while (token != NULL && sutun < this->sutun_sayisi)
        {
            int deger = atoi(token);

            if (deger >= 1 && deger <= 9)
            {
                this->p[sayac] = yeni_Bitki(deger, satir, sutun);
                this->c[sayac] = ((Bitki)this->p[sayac])->super;
            }
            else if (deger >= 10 && deger <= 20)
            {
                this->p[sayac] = yeni_bocek(deger, satir, sutun);
                this->c[sayac] = ((Bocek)this->p[sayac])->super;
            }
            else if (deger >= 21 && deger <= 50)
            {
                this->p[sayac] = yeni_sinek(deger, satir, sutun);
                this->c[sayac] = ((Sinek)this->p[sayac])->super->super;
            }
            else if (deger >= 51 && deger <= 99)
            {
                this->p[sayac] = yeni_pire(deger, satir, sutun);
                this->c[sayac] = ((Pire)this->p[sayac])->super->super;
            }

            sutun++;
            sayac++;
            token = strtok(NULL, " \t\n");
        }

        satir++;
        sutun = 0;
    }

    fclose(dosya);
    return 1;
}

void EkranTemizle()
{
    printf("\033[H\033[J");
}

void HabitatSurecBaslat(Habitat this)
{
    if (this == NULL || this->c == NULL || this->p == NULL)
    {
        printf("Geçersiz Habitat veya Matris.\n");
        return;
    }

    void *p1 = NULL;
    void *p2 = NULL;
    int sayac1 = 0;
    int sayac2 = 1;
    int sonuc = 0;
    int kapasite = this->satir_sayisi * this->sutun_sayisi;
    Canli c1 = NULL;
    Canli c2 = NULL;
    for (int i = 0; i < kapasite - 1; i++)
    {
        c1 = this->c[sayac1];
        c2 = this->c[sayac2];
        if (c1 != NULL && c2 != NULL)
        {
            sonuc = c1->catismakontrol(c1, c2, this->satir_sayisi, this->sutun_sayisi);
            if (sonuc == 1) // c1 kazanır
            {
                if (c2->sayi >= 1 && c2->sayi <= 9)
                {

                    bitkisil((Bitki)this->p[sayac2]);
                }
                else if (c2->sayi >= 10 && c2->sayi <= 20)
                {
                    boceksil((Bocek)this->p[sayac2]);
                }
                else if (c2->sayi >= 21 && c2->sayi <= 50)
                {
                    sineksil((Sinek)this->p[sayac2]);
                }
                else if (c2->sayi >= 51 && c2->sayi <= 99)
                {
                    piresil((Pire)this->p[sayac2]);
                }
                else
                {
                    printf("HATA\n");
                    return;
                }
                this->p[sayac2] = NULL;
                this->c[sayac2] = NULL;

                sayac2++;
                this->EkranTemizle();
                HabitatGoruntule(this);
            }
            else if (sonuc == -1) // c2 kazanır
            {
                if (c1->sayi >= 1 && c1->sayi <= 9)
                {

                    bitkisil((Bitki)this->p[sayac1]);
                }
                else if (c1->sayi >= 10 && c1->sayi <= 20)
                {
                    boceksil((Bocek)this->p[sayac1]);
                }
                else if (c1->sayi >= 21 && c1->sayi <= 50)
                {
                    sineksil((Sinek)this->p[sayac1]);
                }
                else if (c1->sayi >= 51 && c1->sayi <= 99)
                {
                    piresil((Pire)this->p[sayac1]);
                }
                else
                {
                    printf("HATA\n");
                    return;
                }
                this->p[sayac1] = NULL;
                this->c[sayac1] = NULL;

                sayac1 = sayac2;
                sayac2++;

                this->EkranTemizle();
                HabitatGoruntule(this);
            }
            else
            {
                printf("HATA\n");
                return;
            }
        }
    }
    if (sonuc == 1)
    {
        printf("Kazanan : %s : (%d,%d) \n", this->c[sayac1]->gorunum(), this->c[sayac1]->x, this->c[sayac1]->y);
    }

    if (sonuc == -1)
    {
        sayac2--;
        printf("Kazanan : %s : (%d,%d) \n", this->c[sayac2]->gorunum(), this->c[sayac2]->x, this->c[sayac2]->y);
    }
}

void HabitatGoruntule(Habitat this)
{

    if (this != NULL && this->c != NULL)
    {
        int sayac = 0; // Genel sayaç
        int kapasite = this->satir_sayisi * this->sutun_sayisi;

        for (int i = 0; i < this->satir_sayisi; i++)
        {
            for (int j = 0; j < this->sutun_sayisi; j++)
            {
                if (sayac < kapasite && this->c[sayac] != NULL)
                { // İçerik kontrolü
                    printf("%s ", this->c[sayac]->gorunum());
                }
                else
                {
                    printf("X "); // Boş alanlar için
                }
                sayac++;
            }
            printf("\n"); // Satır sonu
        }
    }
    else
    {
        printf("Gecersiz Habitat veya Canli Matrisi.\n");
    }
}
