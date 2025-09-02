#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TAD_matriz.h"

void preenche_acessos(Matriz *m)
{
    srand(time(NULL));

    for (int i = 0; i < linhasMatriz(m); i++)
    {
        for (int j = 0; j < colunasMatriz(m); j++)
        {
            int valor = rand() % 11;
            atribuiMatriz(m, i, j, valor);
        }
    }
}

double calcular_media_hora(const Matriz *m, int hora)
{
    if (hora < 0 || hora >= colunasMatriz(m))
        return 0;

    long long soma = 0;
    for (int i = 0; i < linhasMatriz(m); i++)
    {
        soma += acessaMatriz(m, i, hora);
    }
    return (double)soma / linhasMatriz(m);
}

long long total_dia(const Matriz *m, int dia)
{
    if (dia < 0 || dia >= linhasMatriz(m))
        return 0;

    long long total = 0;
    for (int j = 0; j < colunasMatriz(m); j++)
    {
        total += acessaMatriz(m, dia, j);
    }
    return total;
}

void maior_utilizacao(const Matriz *m, int *dia, int *hora, int *max_uso)
{
    *max_uso = -1;
    for (int i = 0; i < linhasMatriz(m); i++)
    {
        for (int j = 0; j < colunasMatriz(m); j++)
        {
            int uso = acessaMatriz(m, i, j);
            if (uso > *max_uso)
            {
                *max_uso = uso;
                *dia = i;
                *hora = j;
            }
        }
    }
}

int main()
{
    Matriz *m = criaMatriz(7, 14);
    if (!m)
    {
        printf("Erro ao criar a matriz.\n");
        return 1;
    }

    preenche_acessos(m);

    printf("Matriz de utilização dos equipamentos (7 dias x 14 horas):\n");
    imprimeMatriz(m);

    int hora = 9 - 8;
    double media = calcular_media_hora(m, hora);
    printf("\nMédia de utilização às 9h: %.2f\n", media);

    int dia = 2;
    long long total = total_dia(m, dia);
    printf("\nTotal de utilizações no dia 2 (terça-feira): %lld\n", total);

    int max_uso, max_dia, max_hora;
    maior_utilizacao(m, &max_dia, &max_hora, &max_uso);
    printf("\nMaior número de utilizações: %d no dia %d, hora %d (das %dh às %dh)\n",
           max_uso, max_dia, max_hora, max_hora + 8, max_hora + 9);

    liberaMatriz(m);

    return 0;
}