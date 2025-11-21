/*
================================================================================
    🔥 FREE FIRE - DESAFIO DA TORRE DE RESGATE 🔥
================================================================================
    Missão Final: Escapar da Ilha!
    
    A última safe zone está se fechando... Apenas os sobreviventes mais 
    habilidosos chegaram até aqui. Para escapar da ilha, você precisa montar
    uma torre de resgate com os componentes certos, na ordem exata!
    
    Sua missão: Organizar os componentes e encontrar a peça-chave que ativa
    a torre de resgate antes que a zona se feche completamente!
    
    Desenvolvedora: Sistema de Priorização Avançada
    Versão: 1.0 - Nível Mestre
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// ============================================================================
// CONSTANTES DO SISTEMA
// ============================================================================
#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20
#define MIN_PRIORIDADE 1
#define MAX_PRIORIDADE 10

// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

/**
 * Struct Componente - Representa cada peça necessária para montar a torre
 * nome: Identificação do componente (ex: "Chip Central", "Antena")
 * tipo: Categoria do componente (ex: "Controle", "Suporte", "Propulsão")
 * prioridade: Nível de importância (1-10, sendo 10 o mais crítico)
 */
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

/**
 * Enum para critérios de ordenação
 */
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// ============================================================================
// VARIÁVEIS GLOBAIS PARA ANÁLISE DE DESEMPENHO
// ============================================================================
int comparacoes_globais = 0;

// ============================================================================
// PROTÓTIPOS DE FUNÇÕES
// ============================================================================

// Funções de cadastro e exibição
void cadastrarComponentes(Componente componentes[], int *total);
void mostrarComponentes(Componente componentes[], int total);
void mostrarBanner();
void limparBuffer();

// Algoritmos de ordenação
void bubbleSortNome(Componente componentes[], int total, int *comparacoes);
void insertionSortTipo(Componente componentes[], int total, int *comparacoes);
void selectionSortPrioridade(Componente componentes[], int total, int *comparacoes);

// Busca binária
int buscaBinariaPorNome(Componente componentes[], int total, char nome[]);

// Funções auxiliares
void trocarComponentes(Componente *a, Componente *b);
void medirTempoOrdenacao(void (*algoritmo)(Componente[], int, int*), 
                         Componente componentes[], int total, const char *nomeAlgoritmo);
void pausar();

// Menu
void exibirMenu();
void menuOrdenacao(Componente componentes[], int total);
void menuBusca(Componente componentes[], int total);

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    Componente componentes[MAX_COMPONENTES];
    int totalComponentes = 0;
    int opcao;
    
    system("chcp 65001 > nul"); // Configura codificação UTF-8 para Windows
    
    mostrarBanner();
    
    do {
        exibirMenu();
        printf("\n🎯 Escolha sua ação: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &totalComponentes);
                break;
            case 2:
                if(totalComponentes == 0) {
                    printf("\n⚠️  Nenhum componente cadastrado! Cadastre primeiro.\n");
                } else {
                    mostrarComponentes(componentes, totalComponentes);
                }
                pausar();
                break;
            case 3:
                if(totalComponentes == 0) {
                    printf("\n⚠️  Nenhum componente cadastrado! Cadastre primeiro.\n");
                } else {
                    menuOrdenacao(componentes, totalComponentes);
                }
                break;
            case 4:
                if(totalComponentes == 0) {
                    printf("\n⚠️  Nenhum componente cadastrado! Cadastre primeiro.\n");
                } else {
                    menuBusca(componentes, totalComponentes);
                }
                pausar();
                break;
            case 0:
                printf("\n🏝️  Escapando da ilha... Até a próxima batalha, sobrevivente! 🔥\n\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
                pausar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================================

/**
 * Exibe o banner inicial do jogo
 */
void mostrarBanner() {
    system("cls");
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║          🔥 FREE FIRE - TORRE DE RESGATE 🔥                       ║\n");
    printf("╠════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                    ║\n");
    printf("║     ⚠️  ÚLTIMA SAFE ZONE SE FECHANDO! ⚠️                          ║\n");
    printf("║                                                                    ║\n");
    printf("║  Missão: Monte a torre de resgate para escapar da ilha!          ║\n");
    printf("║  Organize os componentes e encontre a peça-chave!                ║\n");
    printf("║                                                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    pausar();
}

/**
 * Exibe o menu principal
 */
void exibirMenu() {
    system("cls");
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║     🎮 MENU PRINCIPAL - TORRE DE RESGATE  ║\n");
    printf("╠═══════════════════════════════════════════╣\n");
    printf("║                                           ║\n");
    printf("║  [1] 📦 Cadastrar Componentes            ║\n");
    printf("║  [2] 📋 Listar Componentes               ║\n");
    printf("║  [3] 🔄 Ordenar Componentes              ║\n");
    printf("║  [4] 🔍 Buscar Componente-Chave          ║\n");
    printf("║  [0] 🚪 Sair do Sistema                  ║\n");
    printf("║                                           ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
}

/**
 * Limpa o buffer do teclado
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Pausa a execução até o usuário pressionar ENTER
 */
void pausar() {
    printf("\n⏸️  Pressione ENTER para continuar...");
    getchar();
}

/**
 * Cadastra componentes no sistema
 */
void cadastrarComponentes(Componente componentes[], int *total) {
    system("cls");
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║     📦 CADASTRO DE COMPONENTES             ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    printf("Quantos componentes deseja cadastrar? (máx. %d): ", MAX_COMPONENTES);
    int qtd;
    scanf("%d", &qtd);
    limparBuffer();
    
    if(qtd <= 0 || qtd > MAX_COMPONENTES) {
        printf("\n❌ Quantidade inválida!\n");
        pausar();
        return;
    }
    
    *total = qtd;
    
    for(int i = 0; i < qtd; i++) {
        printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("🔧 Componente %d/%d\n", i+1, qtd);
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        printf("Nome: ");
        fgets(componentes[i].nome, TAM_NOME, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
        
        printf("Tipo (ex: Controle, Suporte, Propulsão): ");
        fgets(componentes[i].tipo, TAM_TIPO, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
        
        do {
            printf("Prioridade (%d a %d): ", MIN_PRIORIDADE, MAX_PRIORIDADE);
            scanf("%d", &componentes[i].prioridade);
            limparBuffer();
            
            if(componentes[i].prioridade < MIN_PRIORIDADE || 
               componentes[i].prioridade > MAX_PRIORIDADE) {
                printf("⚠️  Prioridade deve estar entre %d e %d!\n", 
                       MIN_PRIORIDADE, MAX_PRIORIDADE);
            }
        } while(componentes[i].prioridade < MIN_PRIORIDADE || 
                componentes[i].prioridade > MAX_PRIORIDADE);
    }
    
    printf("\n✅ %d componentes cadastrados com sucesso!\n", qtd);
    pausar();
}

/**
 * Exibe todos os componentes cadastrados
 */
void mostrarComponentes(Componente componentes[], int total) {
    system("cls");
    printf("\n╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║              📋 LISTA DE COMPONENTES DA TORRE                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ Nº  │ Nome                         │ Tipo               │ Prioridade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    for(int i = 0; i < total; i++) {
        printf("│ %-3d │ %-28s │ %-18s │     %2d     │\n", 
               i+1, 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
    printf("\n📊 Total: %d componente(s)\n", total);
}

/**
 * Troca dois componentes de posição
 */
void trocarComponentes(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ============================================================================
// ALGORITMOS DE ORDENAÇÃO
// ============================================================================

/**
 * Bubble Sort - Ordena componentes por NOME (ordem alfabética)
 * Complexidade: O(n²)
 */
void bubbleSortNome(Componente componentes[], int total, int *comparacoes) {
    *comparacoes = 0;
    
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            (*comparacoes)++;
            if(strcmp(componentes[j].nome, componentes[j+1].nome) > 0) {
                trocarComponentes(&componentes[j], &componentes[j+1]);
            }
        }
    }
}

/**
 * Insertion Sort - Ordena componentes por TIPO (ordem alfabética)
 * Complexidade: O(n²)
 */
void insertionSortTipo(Componente componentes[], int total, int *comparacoes) {
    *comparacoes = 0;
    
    for(int i = 1; i < total; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        while(j >= 0) {
            (*comparacoes)++;
            if(strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j+1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j+1] = chave;
    }
}

/**
 * Selection Sort - Ordena componentes por PRIORIDADE (ordem decrescente)
 * Complexidade: O(n²)
 */
void selectionSortPrioridade(Componente componentes[], int total, int *comparacoes) {
    *comparacoes = 0;
    
    for(int i = 0; i < total - 1; i++) {
        int indiceMaior = i;
        
        for(int j = i + 1; j < total; j++) {
            (*comparacoes)++;
            if(componentes[j].prioridade > componentes[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        
        if(indiceMaior != i) {
            trocarComponentes(&componentes[i], &componentes[indiceMaior]);
        }
    }
}

/**
 * Mede o tempo de execução de um algoritmo de ordenação
 */
void medirTempoOrdenacao(void (*algoritmo)(Componente[], int, int*), 
                         Componente componentes[], int total, const char *nomeAlgoritmo) {
    int comparacoes = 0;
    clock_t inicio, fim;
    double tempo_cpu;
    
    printf("\n⏱️  Executando %s...\n", nomeAlgoritmo);
    
    inicio = clock();
    algoritmo(componentes, total, &comparacoes);
    fim = clock();
    
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║     📊 ANÁLISE DE DESEMPENHO               ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    printf("║ Algoritmo: %-28s║\n", nomeAlgoritmo);
    printf("║ Comparações: %-26d║\n", comparacoes);
    printf("║ Tempo: %.6f segundos             ║\n", tempo_cpu);
    printf("╚════════════════════════════════════════════╝\n");
    
    printf("\n✅ Ordenação concluída!\n");
    mostrarComponentes(componentes, total);
}

/**
 * Menu de ordenação
 */
void menuOrdenacao(Componente componentes[], int total) {
    int opcao;
    
    system("cls");
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║     🔄 MENU DE ORDENAÇÃO                  ║\n");
    printf("╠═══════════════════════════════════════════╣\n");
    printf("║                                           ║\n");
    printf("║  [1] 📝 Ordenar por NOME (Bubble Sort)   ║\n");
    printf("║  [2] 🏷️  Ordenar por TIPO (Insertion)    ║\n");
    printf("║  [3] ⭐ Ordenar por PRIORIDADE (Selection)║\n");
    printf("║  [0] ⬅️  Voltar                          ║\n");
    printf("║                                           ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    
    printf("\n🎯 Escolha o critério de ordenação: ");
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            medirTempoOrdenacao(bubbleSortNome, componentes, total, "Bubble Sort (Nome)");
            break;
        case 2:
            medirTempoOrdenacao(insertionSortTipo, componentes, total, "Insertion Sort (Tipo)");
            break;
        case 3:
            medirTempoOrdenacao(selectionSortPrioridade, componentes, total, "Selection Sort (Prioridade)");
            break;
        case 0:
            return;
        default:
            printf("\n❌ Opção inválida!\n");
    }
    
    pausar();
}

// ============================================================================
// BUSCA BINÁRIA
// ============================================================================

/**
 * Busca Binária - Localiza um componente por NOME
 * IMPORTANTE: A lista DEVE estar ordenada por nome antes de usar!
 * Complexidade: O(log n)
 */
int buscaBinariaPorNome(Componente componentes[], int total, char nome[]) {
    int esquerda = 0;
    int direita = total - 1;
    int comparacoes = 0;
    
    while(esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(componentes[meio].nome, nome);
        
        if(resultado == 0) {
            printf("\n📊 Comparações realizadas: %d\n", comparacoes);
            return meio; // Encontrado!
        }
        
        if(resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    printf("\n📊 Comparações realizadas: %d\n", comparacoes);
    return -1; // Não encontrado
}

/**
 * Menu de busca binária
 */
void menuBusca(Componente componentes[], int total) {
    char nomeBusca[TAM_NOME];
    char resposta;
    
    system("cls");
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║     🔍 BUSCA BINÁRIA - COMPONENTE CHAVE    ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    printf("⚠️  ATENÇÃO: A busca binária requer que a lista esteja\n");
    printf("    ordenada por NOME. Deseja ordenar agora? (S/N): ");
    scanf("%c", &resposta);
    limparBuffer();
    
    if(resposta == 'S' || resposta == 's') {
        int comp;
        bubbleSortNome(componentes, total, &comp);
        printf("\n✅ Lista ordenada por nome!\n\n");
        mostrarComponentes(componentes, total);
    }
    
    printf("\n🔑 Digite o nome do componente-chave: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    printf("\n🔍 Buscando '%s'...\n", nomeBusca);
    
    int indice = buscaBinariaPorNome(componentes, total, nomeBusca);
    
    if(indice != -1) {
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║     ✅ COMPONENTE-CHAVE ENCONTRADO!        ║\n");
        printf("╚════════════════════════════════════════════╝\n\n");
        printf("📍 Posição: %d\n", indice + 1);
        printf("📝 Nome: %s\n", componentes[indice].nome);
        printf("🏷️  Tipo: %s\n", componentes[indice].tipo);
        printf("⭐ Prioridade: %d\n", componentes[indice].prioridade);
        printf("\n🎉 Torre de resgate ativada! Preparando evacuação... 🚁\n");
    } else {
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║     ❌ COMPONENTE NÃO ENCONTRADO!          ║\n");
        printf("╚════════════════════════════════════════════╝\n\n");
        printf("⚠️  O componente '%s' não está na lista.\n", nomeBusca);
        printf("💡 Verifique se o nome está correto e tente novamente.\n");
    }
}
