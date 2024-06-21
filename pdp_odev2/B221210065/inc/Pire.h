#ifndef PIRE_H
#define PIRE_H
#include "Bocek.h"
struct PIRE
{
     Bocek super;
     void (*piresil)(struct PIRE *);
};
typedef struct PIRE *Pire;

Pire yeni_pire(int, int, int);
int pire_catisma_kontrol(Canli, Canli, int, int);
char *pire_gorunum();
void piresil(Pire);
#endif
