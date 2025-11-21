#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Estrutura de um componente
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

// declaração das funções
void cadastrarComponentes(Componente vet[], int *n);
void mostrarComponentes(Componente vet[], int n);
void bubbleSortNome(Componente vet[], int n, int *comparacoes);
void insertionSortTipo(Componente vet[], int n, int *comparacoes);
void selectionSortPrioridade(Componente vet[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente vet[], int n, char chave[], int *comparacoes);
void limparBuffer(void);

/*
==============================================
 FUNÇÃO PRINCIPAL: mostra o menu e chama funções
==============================================
*/
int main() {
    Componente componentes[MAX];
    int n = 0;
    int opcao;
    int comparacoes;
    char chave[TAM_NOME];

    do {
        printf("\n===== SISTEMA DE COMPONENTES =====\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por Nome (Bubble Sort)\n");
        printf("4. Ordenar por Tipo (Insertion Sort)\n");
        printf("5. Ordenar por Prioridade (Selection Sort)\n");
        printf("6. Buscar componente por Nome (Busca Binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

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
                printf("\nOrdenado por nome. Comparações: %d\n", comparacoes);
                break;

            case 4:
                comparacoes = 0;
                insertionSortTipo(componentes, n, &comparacoes);
                printf("\nOrdenado por tipo. Comparações: %d\n", comparacoes);
                break;

            case 5:
                comparacoes = 0;
                selectionSortPrioridade(componentes, n, &comparacoes);
                printf("\nOrdenado por prioridade. Comparações: %d\n", comparacoes);
                break;

            case 6:
                if (n == 0) {
                    printf("\nNenhum componente cadastrado. Cadastre antes de buscar.\n");
                    break;
                }
                printf("Digite o nome para buscar: ");
                if (!fgets(chave, sizeof(chave), stdin)) {
                    printf("Erro na leitura.\n");
                    break;
                }
                chave[strcspn(chave, "\n")] = '\0'; // remove \n

                // Certifique-se que está ordenado por nome antes da busca
                comparacoes = 0;
                bubbleSortNome(componentes, n, &comparacoes);
                // Após ordenar, executamos busca binária com contador separado
                int compsBusca = 0;
                int pos = buscaBinariaPorNome(componentes, n, chave, &compsBusca);
                if(pos != -1)
                    printf("\nComponente encontrado na posição %d.\n", pos+1);
                else
                    printf("\nComponente não encontrado.\n");
                printf("Comparações na busca: %d\n", compsBusca);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while(opcao != 0);

    return 0;
}

// ======================
// CADASTRAR COMPONENTES
// ======================
void cadastrarComponentes(Componente vet[], int *n) {
    int maxDisponivel = MAX - *n;
    if (maxDisponivel == 0) {
        printf("\nLimite de componentes atingido (%d).\n", MAX);
        return;
    }

    int qtd;
    printf("Quantos deseja cadastrar (máx %d)? ", maxDisponivel);
    if (scanf("%d", &qtd) != 1) {
        printf("Entrada inválida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (qtd <= 0 || qtd > maxDisponivel) {
        printf("Quantidade inválida (1 a %d).\n", maxDisponivel);
        return;
    }

    for(int i = 0; i < qtd && *n < MAX; i++) {
        printf("\nComponente %d:\n", *n + 1);

        printf("Nome: ");
        if (!fgets(vet[*n].nome, sizeof(vet[*n].nome), stdin)) {
            vet[*n].nome[0] = '\0';
        } else {
            vet[*n].nome[strcspn(vet[*n].nome, "\n")] = '\0';
        }

        printf("Tipo: ");
        if (!fgets(vet[*n].tipo, sizeof(vet[*n].tipo), stdin)) {
            vet[*n].tipo[0] = '\0';
        } else {
            vet[*n].tipo[strcspn(vet[*n].tipo, "\n")] = '\0';
        }

        int pri;
        do {
            printf("Prioridade (1 a 10): ");
            if (scanf("%d", &pri) != 1) {
                printf("Entrada inválida. Use número.\n");
                limparBuffer();
                pri = -1;
                continue;
            }
            limparBuffer();
            if (pri < 1 || pri > 10) {
                printf("Prioridade fora do intervalo.\n");
            }
        } while (pri < 1 || pri > 10);

        vet[*n].prioridade = pri;
        (*n)++;
    }
    printf("\n%d componente(s) cadastrado(s). Total atual: %d\n", qtd, *n);
}

// ==============================================
// MOSTRAR COMPONENTES
// ==============================================
void mostrarComponentes(Componente vet[], int n) {
    if(n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE COMPONENTES =====\n");
    for(int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
}

// ==============================================
// BUBBLE SORT POR NOME
// ==============================================
void bubbleSortNome(Componente vet[], int n, int *comparacoes) {
    Componente temp;
    *comparacoes = 0;
    if (n <= 1) return;

    for(int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for(int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if(strcmp(vet[j].nome, vet[j+1].nome) > 0) {
                temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização: se já ordenado, interrompe
    }
}

// ==============================================
// INSERTION SORT POR TIPO
// ==============================================
void insertionSortTipo(Componente vet[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 1; i < n; i++) {
        Componente chave = vet[i];
        int j = i - 1;
        while(j >= 0) {
            (*comparacoes)++;
            if(strcmp(vet[j].tipo, chave.tipo) > 0) {
                vet[j+1] = vet[j];
                j--;
            } else {
                break;
            }
        }
        vet[j+1] = chave;
    }
}

// ==============================================
// SELECTION SORT POR PRIORIDADE
// (ordena crescente: menor prioridade -> maior prioridade)
// ==============================================
void selectionSortPrioridade(Componente vet[], int n, int *comparacoes) {
    *comparacoes = 0;
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
    *comparacoes = 0;

    while(inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
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

// limpa resto do buffer stdin
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
