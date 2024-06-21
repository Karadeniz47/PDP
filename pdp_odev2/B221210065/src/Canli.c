#include "Canli.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

Canli YeniCanli(int sayi, int x, int y)
{
    Canli this;
    this = (Canli)malloc(sizeof(struct CANLI));
    if (this == NULL)
    {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return NULL;
    }
    this->sayi = sayi;
    this->x = x;
    this->y = y;
    this->canlisil = &canlisil;
    return this;
}

void canlisil(Canli this)
{
    if (this != NULL)
    {
        free(this);
    }
    this = NULL;
}