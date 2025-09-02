#include <stdio.h>
#include "TAD_Altura.h"

int main()
{
    Altura *a1 = alt_cria(1, 77);
    Altura *a2 = alt_cria(1, 80);
    // Exibindo
    printf("Altura 1: ");
    alt_exibe(a1);
    printf("\nAltura 2: ");
    alt_exibe(a2);
    // Comparando
    int cmp = alt_compara(a1, a2);
    printf("\nComparacao: %d\n", cmp);
    // Somando 30cm a altura
    Altura *soma = alt_soma(a1, 30);
    printf("Somando 30cm da a1: ");
    alt_exibe(soma);

    // Diferença
    Altura *dif = alt_diferenca(a1, a2);
    printf("\nDiferença entre a1 e a2: ");
    alt_exibe(dif);
    // Copia
    Altura *copia = alt_copia(a1);
    printf("\nCopia da altura 1: ");
    alt_exibe(copia);
    // getAltura
    char *str = alt_getAltura(a1);
    printf("\nString da altura 1: %s", str);
    alt_exibe(str);
    // Liberando memória
    alt_libera(a1);
    alt_libera(a2);
    alt_libera(soma);
    alt_libera(dif);
    alt_libera(copia);

    return 0;
}