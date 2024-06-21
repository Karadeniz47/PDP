#ifndef CANLI_H
#define CANLI_H

struct CANLI
{
    int sayi;
    int x;
    int y;
    char *(*gorunum)();
    int (*catismakontrol)(struct CANLI *, struct CANLI *, int, int);
    void (*canlisil)(struct CANLI *);
};
typedef struct CANLI *Canli;
Canli YeniCanli(int, int, int);
void canlisil(Canli);
#endif