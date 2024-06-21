#ifndef BITKI_H
#define BITKI_H
#include "Canli.h"

struct BITKI
{
    Canli super;
    void (*bitkisil)(struct BITKI *);
};
typedef struct BITKI *Bitki;
Bitki yeni_Bitki(int, int, int);
char *bitki_gorunum();
int bitki_catisma_kontrol(Canli, Canli, int, int);
void bitkisil(Bitki);
#endif