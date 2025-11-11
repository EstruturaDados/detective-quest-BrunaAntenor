#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada sala da mansão
typedef struct sala {
    char nome[50];
    struct sala *esquerda;
    struct sala *direita;
} Sala;

// -----------------------------------------------------------
// Função: criarSala
// Cria dinamicamente uma nova sala com o nome informado
// -----------------------------------------------------------
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a sala.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0'; // Garante terminação
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// -----------------------------------------------------------
// Função: explorarSalas
// Permite que o jogador navegue interativamente pela mansão
// -----------------------------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    while (1) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Caso seja uma sala sem saídas (folha)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim! Não há mais caminhos.\n");
            break;
        }

        // Mostra opções disponíveis
        printf("Escolha o caminho:\n");
        if (atual->esquerda != NULL)
            printf(" (e) Ir para a esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf(" (d) Ir para a direita -> %s\n", atual->direita->nome);
        printf(" (s) Sair do jogo\n");
        printf("Sua escolha: ");

        // scanf com verificação de retorno
        if (scanf(" %c", &escolha) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            // Limpa buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("Você decidiu encerrar a exploração.\n");
            break;
        } else {
            printf("Caminho inválido! Tente novamente.\n");
        }
    }
}

// -----------------------------------------------------------
// Função: liberarSalas
// Libera recursivamente todas as salas da mansão
// -----------------------------------------------------------
void liberarSalas(Sala *raiz) {
    if (raiz == NULL)
        return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// -----------------------------------------------------------
// Função principal: main
// Monta manualmente a árvore da mansão e inicia a exploração
// -----------------------------------------------------------
int main(void) {
    // Criação das salas (nós da árvore)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *quarto = criarSala("Quarto Secreto");

    // Conectando as salas (estrutura da mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->direita = quarto;

    // Inicia a exploração
    printf("=== Detective Quest: Exploração da Mansão ===\n");
    explorarSalas(hall);

    // Liberação da memória
    liberarSalas(hall);

    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}