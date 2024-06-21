#ifndef BOCEK_H
#define BOCEK_H
#include "Canli.h"
struct BOCEK
{
     Canli super;
     void (*boceksil)(struct BOCEK *);
};
typedef struct BOCEK *Bocek;
Bocek yeni_bocek(int, int, int);
int bocek_catisma_kontrol(Canli, Canli, int, int);
char *bocek_gorunum();
void boceksil(Bocek);
#endif
