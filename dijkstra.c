

#include "defs.h"
#include "points.h"
#include "util.h"
#include "tabuleiros.h"
#include "moves.h"
#include "acervo.h"


struct Dijk_struct
{
    bool visited;
    int acum_cost;
    point * pai;
};

#include "dijkstra.h"


int get_Acum_Cost(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].acum_cost;
}

bool check_visited(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].visited;
}

point * get_Father(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].pai;
}


DijkMatrix AllocDijk(int ysize, int xsize)
{
    DijkMatrix new = (DijkMatrix) Checked_Malloc(sizeof(Dijk *) * ysize);

    for(int i = 0; i < ysize; i++)
        new[i] = (Dijk *) Checked_Malloc(sizeof(Dijk) * xsize);

    return new;
}

void FreeDijk(DijkMatrix matrix, int ysize, int xsize)
{
    for(int i = 0; i < ysize; i++)
        free(matrix[i]);

    free(matrix);
}

DijkMatrix Problema2Dijk(Problema * turist)
{
    tabuleiro * tab = getTabuleiro(turist);

    DijkMatrix new = AllocDijk(getYSize(tab), getXSize(tab));

    for(int i = 0; i < getYSize(tab); i++)
    {
        for(int j = 0; j < getXSize(tab); j++)
        {
            new[i][j].visited = false;
            new[i][j].acum_cost = INF;
            new[i][j].pai = getIpoint(turist, 0);
        }
    }

    return new;
}

point ** Possible_Jump_Points(tabuleiro * tab, point * ponto, DijkMatrix aux)
{
    point ** new = (point **) Checked_Malloc(sizeof(point *) * 8);

    point * aux0 = (point *) Checked_Malloc(getSizeOfPoint());
    aux0 = SetPoint(aux0, get_X_From_Point(ponto) + 1, get_Y_From_Point(ponto) - 2);
    if(check_Point_Acessibility(tab, aux0) && !check_visited(aux, aux0))
        new[0] = aux0;
    else
    {
        new[0] = NULL;
        free(aux0);
    }

    point * aux1 = (point *) Checked_Malloc(getSizeOfPoint());
    aux1 = SetPoint(aux1, get_X_From_Point(ponto) + 2, get_Y_From_Point(ponto) - 1);
    if(check_Point_Acessibility(tab, aux1) && !check_visited(aux, aux1))
        new[1] = aux1;
    else
    {
        new[1] = NULL;
        free(aux1);
    }


    point * aux2 = (point *) Checked_Malloc(getSizeOfPoint());
    aux2 = SetPoint(aux2, get_X_From_Point(ponto) + 2, get_Y_From_Point(ponto) + 1);
    if(check_Point_Acessibility(tab, aux2) && !check_visited(aux, aux2))
        new[2] = aux2;
    else
    {
        new[2] = NULL;
        free(aux2);
    }


    point * aux3 = (point *) Checked_Malloc(getSizeOfPoint());
    aux3 = SetPoint(aux3, get_X_From_Point(ponto) + 1, get_Y_From_Point(ponto) + 2);
    if(check_Point_Acessibility(tab, aux3) && !check_visited(aux, aux3))
        new[3] = aux3;
    else
    {
        new[3] = NULL;
        free(aux3);
    }


    point * aux4 = (point *) Checked_Malloc(getSizeOfPoint());
    aux4 = SetPoint(aux4, get_X_From_Point(ponto) - 1, get_Y_From_Point(ponto) + 2);
    if(check_Point_Acessibility(tab, aux4) && !check_visited(aux, aux4))
        new[4] = aux4;
    else
    {
        new[4] = NULL;
        free(aux4);
    }

    point * aux5 = (point *) Checked_Malloc(getSizeOfPoint());
    aux5 = SetPoint(aux5, get_X_From_Point(ponto) - 2, get_Y_From_Point(ponto) + 1);
    if(check_Point_Acessibility(tab, aux5) && !check_visited(aux, aux5))
        new[5] = aux5;
    else
    {
        new[5] = NULL;
        free(aux5);
    }

    point * aux6 = (point *) Checked_Malloc(getSizeOfPoint());
    aux6 = SetPoint(aux6, get_X_From_Point(ponto) - 2, get_Y_From_Point(ponto) - 1);
    if(check_Point_Acessibility(tab, aux6) && !check_visited(aux, aux6))
        new[6] = aux6;
    else
    {
        new[6] = NULL;
        free(aux6);
    }

    point * aux7 = (point *) Checked_Malloc(getSizeOfPoint());
    aux7 = SetPoint(aux7, get_X_From_Point(ponto) - 1, get_Y_From_Point(ponto) - 2);
    if(check_Point_Acessibility(tab, aux7) && !check_visited(aux, aux7))
        new[7] = aux7;
    else
    {
        new[7] = NULL;
        free(aux7);
    }

    return new;
}

void Free_Possible_Jump_Points(point ** vect)
{
    for(int i = 0; i < 8; i++)
        if(vect[i] != NULL)
            free(vect[i]);
}

bool  EmptyHeap(Acervo * aux)
{
    for( int i=0, i < 8, i++)
    {
        
    }


}

void DijkstraAlgoritm(Problema * turist)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo();

    point * ORIGIN_POINT = getIpoint(turist, 0);
    point * DESTINY_POINT = getIpoint(turist, 1);

    point ** ppoints = Possible_Jump_Points(getTabuleiro(turist), ORIGIN_POINT, matrix);


    for(int i = 0; i < 8; i++)
    {
        if(ppoints[i] != NULL)
        {
            matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost = GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);
            HeapInsertPoint(matrix, heap_tree, ppoints[i]);
        }
    }


    matrix[get_Y_From_Point(ORIGIN_POINT)][get_X_From_Point(ORIGIN_POINT)].acum_cost = 0;
    

    while(getIPointFromHeap(heap_tree,0) != NULL)
    {
        printf("ola\n");
        point * min = HeapDeleteMaxPoint(matrix, heap_tree);
        if(min != NULL && matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost != INF)
        {
            for(int i = 0; i < 8; i++)
            {
                int aux = 0;
                if(ppoints[i] != NULL)
                {
                    if((aux = (matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i])) <
                                                            matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost))
                    {
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost = aux;
                        FixDown(matrix,heap_tree,i,getFree(heap_tree)- 1);
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai = min;

                    }

                }
            }
        }
    }



    // Free_Possible_Jump_Points(pontos);
    // free(pontos);

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree);

}
