// Tipo exportado
typedef struct alt Altura;

// funçao cria - Aloca e retorna uma altura em m e cm
Altura *alt_cria(int m, int cm);
// Funçao libera- Libera a memoria de uma altura previamente criada
void alt_libera(Altura *p);
// Função acessa - Retorna os valores de ua Altura
void alt_acessa(Altura *p, int *m, int *cm);
// Função atribui - Atribui novos valores as partes de uma Altura
void alt_atribui(Altura *p, int m, int cm);
// Função exibe - Escreve na tela a altura m,cm
void alt_exibe(Altura *p);
// Função getAltur - Retorna uma string com os valores da altura no formato m,cm
char *alt_getAltura(Altura *p);
// Função compara - -1 se alt1 < alt2 0- se alt1 == alt2 +1- se alt1 >alt2
int alt_compara(Altura *p1, Altura *p2);
// Função soma
Altura *alt_soma(Altura *alt1, int cm);
// Função diferença
Altura *alt_diferenca(Altura *alt1, Altura *alt2);
// Função copia
char *alt_copia(Altura *alt1);