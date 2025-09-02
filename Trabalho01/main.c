#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definindo struct
struct at
{
    int matricula;
    char *nome;
    int tempo;
};
typedef struct at tAt;
// Protótipo das funções
void incluirAtletas(tAt **vAtletas, int *quantidade);
void exibirAtletasOrdemInclusao(tAt *vAtletas, int quantidade);
void exibirAtletasOrdenadosNome(tAt *vAtletas, int quantidade);
void exibirRankingTempo(tAt *vAtletas, int quantidade);
void filtrarAtletasTempoSuperior(tAt *vAtletas, int quantidade);
void liberarMemoria(tAt *vAtletas, int quantidade);
void ordenarPorNome(tAt **vOrdenado, int quantidade);
void ordenarPorTempo(tAt **vRanking, int quantidade);
void formatarTempo(int minutos, char *buffer);
void limparBuffer(); // Função para limpar Buffer de entrada
int main()
{
    tAt *vAtletas = NULL;
    int opcao, quantidade = 0;
    do
    {
        printf("\n=== SISTEMA DE GERENCIAMENTO DE ATLETAS ===\n");
        printf("1- Incluir atletas\n");
        printf("2- Exibir atletas na ordem de inclusao\n");
        printf("3- Exibir atletas ordenados por nome\n");
        printf("4- Exibir ranking por tempo de treino\n");
        printf("5- Filtrar atletas com tempo superior a um limite\n");
        printf("0- Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao)
        {
        case 1:
            incluirAtletas(&vAtletas, &quantidade);
            break;
        case 2:
            exibirAtletasOrdemInclusao(vAtletas, quantidade);
            break;
        case 3:
            exibirAtletasOrdenadosNome(vAtletas, quantidade);
            break;
        case 4:
            exibirRankingTempo(vAtletas, quantidade);
            break;
        case 5:
            filtrarAtletasTempoSuperior(vAtletas, quantidade);
            break;
        case 0:
            printf("Encerrando programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    // Liberando toda memória antes de terminar o programa
    liberarMemoria(vAtletas, quantidade);
    return 0;
}
// Implementação das funções
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void incluirAtletas(tAt **vAtletas, int *quantidade)
{
    int qtdNovos, i;
    printf("Quantos atletas deseja cadastrar? ");
    scanf("%d", &qtdNovos);
    limparBuffer();
    if (qtdNovos <= 0)
    {
        printf("Quantidade invalida!\n");
        return;
    }
    // Realocando memória para aumentar o vetor de atletas
    tAt *novoVetor = (tAt *)realloc(*vAtletas, (*quantidade + qtdNovos) * sizeof(tAt));
    if (novoVetor == NULL)
    {
        printf("Erro ao alocar memoria!");
        return;
    }
    *vAtletas = novoVetor;
    // Loop para cadastrar cada novo atleta
    for (i = *quantidade; i < *quantidade + qtdNovos; i++)
    {
        printf("\nAtleta %d: \n", i + 1);
        // Lendo o nome do atleta
        char buffer[100];
        printf("Nome: ");
        fgets(buffer, 100, stdin);
        limparBuffer();
        // Alocando memória dinamicamente para o nome do atleta
        (*vAtletas)[i].nome = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        // Copiando buffer para área alocada
        strcpy((*vAtletas)[i].nome, buffer);
        // Lendo matricula do atleta
        printf("Matricula: ");
        scanf("%d", &(*vAtletas)[i].matricula);
        limparBuffer();
        // Lendo Tempo de treino do atleta
        printf("Tempo de treino(minutos): ");
        scanf("%d", &(*vAtletas)[i].tempo);
        limparBuffer();
    }
    // Atualizando contador total de atletas
    *quantidade += qtdNovos;
    printf("%d atletas cadastrados com sucesso!\n", qtdNovos);
}
void exibirAtletasOrdemInclusao(tAt *vAtletas, int quantidade)
{
    // Declaração de variáveis
    int i;
    // Verificando se há atletas cadastrados
    if (quantidade == 0)
    {
        printf("Nenhum atleta cadastrado!\n");
        return;
    }
    printf("\n === ATLETAS NA ORDEM DE INCLUSAO ===\n");
    // Exibindo ATLETAS
    for (i = 0; i < quantidade; i++)
    {
        // Buffer para armazenar o tempo formatado
        char tempoFormatado[10];
        // Formatando o tempo
        formatarTempo(vAtletas[i].tempo, tempoFormatado);
        printf("%d.%s (Matricula: %d) - Tempo: %s\n", i + 1, vAtletas[i].nome, vAtletas[i].matricula, tempoFormatado);
    }
}
void exibirAtletasOrdenadosNome(tAt *vAtletas, int quantidade)
{
    // Declaração de variáveis
    int i;
    // Verificando se há atletas cadastrados
    if (quantidade == 0)
    {
        printf("Nenhum atleta cadastrado!");
        return;
    }
    // Criando vetor de ponteiros para os atletas
    tAt **vOrdenado = (tAt **)malloc(quantidade * sizeof(tAt *));
    if (vOrdenado == NULL)
    {
        printf("Erro ao alocar memoria!");
        return;
    }
    // Inicializando o vetor de ponteiros com os endereços dos atletas originais
    for (i = 0; i < quantidade; i++)
    {
        // Cada ponteiro aponta para um atleta do vetor original
        vOrdenado[i] = &vAtletas[i];
    }
    // Ordenando o vetor de ponteiros por nome usando a função ordenarPorNome
    ordenarPorNome(vOrdenado, quantidade);
    printf("\n === ATLETAS ORDENADOS POR NOME ===\n");
    // Exibindo os atletas na ordem do vetor de ponteiros ordenados
    for (i = 0; i < quantidade; i++)
    {
        char tempoFormatado[10];
        formatarTempo(vOrdenado[i]->tempo, tempoFormatado);
        printf("%d. %s (Matricula: %d) - Tempo %s\n", i + 1, vOrdenado[i]->nome, vOrdenado[i]->matricula, tempoFormatado);
    }
    // Liberando memória
    free(vOrdenado);
}
void exibirRankingTempo(tAt *vAtletas, int quantidade)
{
    // Declaração de variáveis
    int i;
    // Verificando se há atletas cadastrados
    if (quantidade == 0)
    {
        printf("Nenhum atleta cadastrado!");
        return;
    }
    // Criando vetor de ponteiros para os atletas
    tAt **vRanking = (tAt **)malloc(quantidade * sizeof(tAt *));
    if (vRanking == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    // Inicializando vetor de ponteiros
    for (i = 0; i < quantidade; i++)
    {
        vRanking[i] = &vAtletas[i]; // Cada ponteiro aponta para um atleta
    }
    // Ordenando o vetor de ponteiros por tempo(decrescente)
    ordenarPorTempo(vRanking, quantidade);
    printf("\n=== RANKING POR TEMPO DE TREINO ===\n");
    // Exibindo o ranking ordenado por TEMPO
    for (i = 0; i < quantidade; i++)
    {
        char tempoFormatado[10];
        formatarTempo(vRanking[i]->tempo, tempoFormatado);
        printf("%dº - %s (Matricula: %d) - Tempo: %s\n", i + 1, vRanking[i]->nome, vRanking[i]->matricula, tempoFormatado);
    }
    // Liberando a memória do vetor de ponteiros
    free(vRanking);
}
void filtrarAtletasTempoSuperior(tAt *vAtletas, int quantidade)
{
    // Declaração de variáveis
    int i, j, limite, cont = 0;
    // Verificando se há atletas cadastrados
    if (quantidade == 0)
    {
        printf("Nenhum atleta cadastrado!");
        return;
    }
    printf("Informe o tempo limite em minutos: ");
    scanf("%d", &limite);
    limparBuffer();
    for (i = 0; i < quantidade; i++)
    {
        if (vAtletas[i].tempo > limite)
        {
            // Imcrementando o contador para cada atleta que atende ao critério
            cont++;
        }
    }
    // Verificando se encontrou algum atleta com tempo superior ao limite
    if (cont == 0)
    {
        printf("Nenhum atleta com tempo superior a %d minutos.\n", limite);
        return;
    }
    // Criando vetor de ponteiros apenas para os atletas que atendem ao criterio
    tAt **vPiores = (tAt **)malloc(cont * sizeof(tAt *));
    if (vPiores == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    // Preenchendo o vetor com ponteiros para os atletas filtrados
    j = 0; // Indice para o vetor vPiores
    for (i = 0; i < quantidade; i++)
    {
        if (vAtletas[i].tempo > limite)
        {
            // Adicionando ponteiro para o atleta
            vPiores[j++] = &vAtletas[i];
        }
    }
    printf("\n === ATLETAS COM TEMPO SUPERIOR A %d MINUTOS ===\n", limite);
    // Exibindo os atletas filtrados
    for (i = 0; i < cont; i++)
    {
        char tempoFormatado[10];
        formatarTempo(vPiores[i]->tempo, tempoFormatado);
        printf("%d. %s (Matricula: %d) - Tempo: %s\n", i + 1, vPiores[i]->nome, vPiores[i]->matricula, tempoFormatado);
    }
    // Liberando memoria
    free(vPiores);
}
void liberarMemoria(tAt *vAtletas, int quantidade)
{
    // Declaração de variáveis
    int i;
    // Liberando a memoria de cada nome de atleta
    for (i = 0; i < quantidade; i++)
    {
        free(vAtletas[i].nome); // Libera a string do nome
    }
    // Liberando o vetor de atletas
    free(vAtletas);
}
void ordenarPorNome(tAt **vOrdenado, int quantidade)
{
    // Declaração de variáveis
    int i, j;
    // Algoritmo de ordenação por seleção(Selection Sort)
    for (i = 0; i < quantidade - 1; i++)
    {
        // Assumindo que o elemento atual é o menor
        int menor = i;
        for (j = i + 1; j < quantidade; j++)
        {
            // Comparando os nomes dos atletas
            int cmp = strcmp(vOrdenado[j]->nome, vOrdenado[menor]->nome);
            if (cmp < 0)
            {
                menor = j; // Encontrou um nome "menor" (alfabeticamente anterior)
            }
            else if (cmp == 0)
            {
                // Se nomes são iguais, desempata por matrícula (crescente)
                if (vOrdenado[j]->matricula < vOrdenado[menor]->matricula)
                {
                    menor = j;
                }
            }
        }
        // Trocando as posições se encontrou um elemento menor
        if (menor != i)
        {
            // Armazenando o valor na variavel temporaria
            tAt *temp = vOrdenado[i];
            // Movendo o menor para posição atual
            vOrdenado[i] = vOrdenado[menor];
            // Colocando o temporário na posição do menor
            vOrdenado[menor] = temp;
        }
    }
}
void ordenarPorTempo(tAt **vRanking, int quantidade)
{
    // Declaração de variaveis
    int i, j;
    // Algoritmo de ordenação por seleção(Selection Sort)
    for (i = 0; i < quantidade - 1; i++)
    {
        int maior = i; // Assume que o elemento atual é o maior
        for (j = i + 1; j < quantidade; j++)
        {
            // Comparando os tempos  (ordem decrescente)
            if (vRanking[j]->tempo > vRanking[maior]->tempo)
            {
                maior = j;
            }
            else if (vRanking[j]->tempo == vRanking[maior]->tempo)
            {
                // Se tempos são iguais, desempata por matrícula (crescente)
                if (vRanking[j]->matricula < vRanking[maior]->matricula)
                {
                    maior = j;
                }
            }
        }
        // Trocando as posições se encontrou um elemento maior
        if (maior != i)
        {
            // Armazenando o valor na variavel temporaria
            tAt *temp = vRanking[i];
            // Movendo o maior para posição atual
            vRanking[i] = vRanking[maior];
            // Colocando o temporário na posição do maior
            vRanking[maior] = temp;
        }
    }
}
void formatarTempo(int minutos, char *buffer)
{
    int horas = minutos / 60;
    int mins = minutos % 60;
    printf(buffer, "%02d:%02d", horas, mins);
}