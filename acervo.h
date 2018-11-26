
#ifndef _ACERVO_H
#define _ACERVO_H

#include "defs.h"

typedef struct acervoStruct Acervo;

#include "dijkstra.h"

Acervo * InitAcervo();

void FixDown(DijkMatrix matrix, Acervo * aux, int Idx, int N);

void HeapInsertPoint(DijkMatrix matrix, Acervo * new, point * I);

void FixUp(DijkMatrix matrix, Acervo * aux, int Idx);

point * HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * aux);


#endif