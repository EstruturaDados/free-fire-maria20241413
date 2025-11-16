#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================================
//  TRABALHO DE ESTRUTURA DE DADOS
//  ALUNA: Maria Eloisa O Freitas
//  MATRÍCULA: 202408452969
//  ALUNA: Mariana Aragão
//  MATRÍCULA: 202408142943
// ==============================================

#define MAX 20

// Estrutura de um componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// declaração das funções
void cadastrarComponentes(Componente vet[], int *n);
void mostrarComponentes(Componente vet[], int n);
void bubbleSortNome(Componente vet[], int n, int *comparacoes);
void insertionSortTipo(Componente vet[], int n, int *comparacoes);
void selectionSortPrioridade(Componente vet[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente vet[], int n, char chave[], int *comparacoes);

// ==============================================
//  FUNÇÃO PRINCIPAL mostra o menu e chama a função
// ==============================================
int main() {
    Componente componentes[MAX];
    int n = 0;
    int opcao;
    int comparacoes;
    char chave[30];

    do {
        printf("
===== SISTEMA DE COMPONENTES =====
");
        printf("1. Cadastrar componentes
");
        printf("2. Mostrar componentes
");
        printf("3. Ordenar por Nome (Bubble Sort)
");
        printf("4. Ordenar por Tipo (Insertion Sort)
");
        printf("5. Ordenar por Prioridade (Selection Sort)
");
        printf("6. Buscar componente por Nome (Busca Binária)
");
        printf("0. Sair
");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &n);
                break;

            case 2:
                mostrarComponentes(componentes, n);
                break;

            case 3:
                comparacoes = 0;
                bubbleSortNome(componentes, n, &comparacoes);
                printf("
Ordenado por nome. Comparações: %d
", comparacoes);
                break;

            case 4:
                comparacoes = 0;
                insertionSortTipo(componentes, n, &comparacoes);
                printf("
Ordenado por tipo. Comparações: %d
", comparacoes);
                break;

            case 5:
                comparacoes = 0;
                selectionSortPrioridade(componentes, n, &comparacoes);
                printf("
Ordenado por prioridade. Comparações: %d
", comparacoes);
                break;

            case 6:
                printf("Digite o nome para buscar: ");
                scanf(" %29[^
]", chave);
                comparacoes = 0;
                bubbleSortNome(componentes, n, &comparacoes);
                int pos;
                pos = buscaBinariaPorNome(componentes, n, chave, &comparacoes);
                if(pos != -1)
                    printf("Componente encontrado na posição %d.
", pos+1);
                else
                    printf("Componente não encontrado.
");
                break;

            case 0:
                printf("Encerrando...
");
                break;
        }

    } while(opcao != 0);

    return 0;
}

// ==============================================
// CADASTRAR COMPONENTES
// ==============================================
void cadastrarComponentes(Componente vet[], int *n) {
    int qtd;
    printf("Quantos deseja cadastrar (máx %d)? ", MAX - *n);
    scanf("%d", &qtd);

    for(int i = 0; i < qtd && *n < MAX; i++) {
        printf("
Componente %d:
", *n + 1);

        printf("Nome: ");
        scanf(" %29[^
]", vet[*n].nome);

        printf("Tipo: ");
        scanf(" %19[^
]", vet[*n].tipo);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &vet[*n].prioridade);

        (*n)++;
    }
}

// ==============================================
// MOSTRAR COMPONENTES
// ==============================================
void mostrarComponentes(Componente vet[], int n) {
    if(n == 0) {
        printf("
Nenhum componente cadastrado.
");
        return;
    }

    printf("
===== LISTA DE COMPONENTES =====
");
    for(int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d
",
               i + 1, vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
}

// ==============================================
// BUBBLE SORT POR NOME
// ==============================================
void bubbleSortNome(Componente vet[], int n, int *comparacoes) {
    Componente temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if(strcmp(vet[j].nome, vet[j+1].nome) > 0) {
                temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
    }
}

// ==============================================
// INSERTION SORT POR TIPO
// ==============================================
void insertionSortTipo(Componente vet[], int n, int *comparacoes) {
    for(int i = 1; i < n; i++) {
        Componente chave = vet[i];
        int j = i - 1;
        while(j >= 0 && strcmp(vet[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = chave;
    }
}

// ==============================================
// SELECTION SORT POR PRIORIDADE
// ==============================================
void selectionSortPrioridade(Componente vet[], int n, int *comparacoes) {
    for(int i = 0; i < n - 1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if(vet[j].prioridade < vet[min].prioridade)
                min = j;
        }
        if(min != i) {
            Componente temp = vet[i];
            vet[i] = vet[min];
            vet[min] = temp;
        }
    }
}

// ==============================================
// BUSCA BINÁRIA POR NOME
// ==============================================
int buscaBinariaPorNome(Componente vet[], int n, char chave[], int *comparacoes) {
    int inicio = 0, fim = n - 1;

    while(inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;

        int cmp = strcmp(chave, vet[meio].nome);

        if(cmp == 0)
            return meio;
        else if(cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}
