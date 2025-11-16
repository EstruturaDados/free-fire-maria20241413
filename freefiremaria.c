/*
 * Arquivo: 202408452969_Maria_Eloisa_e_Mariana_Aragão.c    
 * Grupo: Mariana Aragão (202408142943), Maria Eloisa (202408452969) 
 * Disciplina: Estruturas de Dados
 * Professor: Luiz 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

/* --------------------------------
   Estrutura do item 
   ------------------------------ */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* as funções*/
void cadastrarComponentes(Componente vet[], int *n);
void mostrarComponentes(Componente vet[], int n);
void bubbleSortNome(Componente vet[], int n, int *comparacoes);
void insertionSortTipo(Componente vet[], int n, int *comparacoes);
void selectionSortPrioridade(Componente vet[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente vet[], int n, char chave[], int *comparacoes);
int estaOrdenadoPorNome(Componente vet[], int n);

/* ---------------------------------------------------------
   Função principal
   --------------------------------------------------------- */
int main(void) {
    Componente componentes[MAX];
    int n = 0; /* quantidade de componentes cadastrados */
    int opcao;
    int comparacoes;
    clock_t inicio, fim;
    double tempo;
    char chave[30];
    int encontrado;


    do {
        printf("
===== SISTEMA DE MONTAGEM DA TORRE DE FUGA =====
");
        printf("1. Cadastrar componentes
");
        printf("2. Mostrar componentes
");
        printf("3. Ordenar por NOME (Bubble Sort)
");
        printf("4. Ordenar por TIPO (Insertion Sort)
");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)
");
        printf("6. Buscar componente por NOME (Busca Binária)
");
        printf("0. Sair
");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            /* leitura inválida: limpar e continuar */
            printf("Entrada inválida. Digite um número de 0 a 6.
");
            int c; while ((c = getchar()) != '
' && c != EOF) {}
            continue;
        }
        getchar(); /* limpar 
 */

        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &n);
                break;

            case 2:
                mostrarComponentes(componentes, n);
                break;

            case 3:
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(componentes, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("
Bubble Sort concluído.
Comparações: %d | Tempo: %.6f segundos
", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 4:
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(componentes, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("
Insertion Sort concluído.
Comparações: %d | Tempo: %.6f segundos
", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 5:
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(componentes, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("
Selection Sort concluído.
Comparações: %d | Tempo: %.6f segundos
", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 6:
                if (n == 0) {
                    printf("Nenhum componente cadastrado para buscar.
");
                    break;
                }
                printf("Digite o nome do componente para buscar: ");
                if (fgets(chave, sizeof(chave), stdin) == NULL) {
                    printf("Erro ao ler chave.
");
                    break;
                }
                chave[strcspn(chave, "
")] = '