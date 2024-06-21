#ifndef SINEK_H
#define SINEK_H
#include "Bocek.h"
struct SINEK
{
    Bocek super;
    void (*sineksil)(struct SINEK *);
};
typedef struct SINEK *Sinek;
Sinek yeni_sinek(int, int, int);
int sinek_catisma_kontrol(Canli, Canli, int, int);
char *sinek_gorunum();
void sineksil(Sinek);
#endif
