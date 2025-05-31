#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char nome[20];
    int valor;
    char naipe[10];
} Carta;

typedef struct {
    char nome[30];
    Carta mao[3];
    int pontos;
} Jogador;

void criarBaralho(Carta baralho[]) {
    // Paus
    baralho[0] = (Carta){"J (Valete)", 1, "Paus"};
    baralho[1] = (Carta){"Q (Rainha)", 2, "Paus"};
    baralho[2] = (Carta){"K (Rei)", 3, "Paus"};
    baralho[3] = (Carta){"A", 4, "Paus"};
    baralho[4] = (Carta){"2", 5, "Paus"};
    baralho[5] = (Carta){"3", 6, "Paus"};
    baralho[6] = (Carta){"4", 10, "Paus"}; // Manilha (Zap)

    // Copas
    baralho[7] = (Carta){"J (Valete)", 1, "Copas"};
    baralho[8] = (Carta){"Q (Rainha)", 2, "Copas"};
    baralho[9] = (Carta){"K (Rei)", 3, "Copas"};
    baralho[10] = (Carta){"A", 4, "Copas"};
    baralho[11] = (Carta){"2", 5, "Copas"};
    baralho[12] = (Carta){"3", 6, "Copas"};
    baralho[13] = (Carta){"7", 9, "Copas"}; // Manilha (7 de Copas)

    // Espadas
    baralho[14] = (Carta){"J (Valete)", 1, "Espadas"};
    baralho[15] = (Carta){"Q (Rainha)", 2, "Espadas"};
    baralho[16] = (Carta){"K (Rei)", 3, "Espadas"};
    baralho[17] = (Carta){"A", 8, "Espadas"}; // Manilha (A de Espadas)
    baralho[18] = (Carta){"2", 5, "Espadas"};
    baralho[19] = (Carta){"3", 6, "Espadas"};

    // Ouros
    baralho[20] = (Carta){"J (Valete)", 1, "Ouros"};
    baralho[21] = (Carta){"Q (Rainha)", 2, "Ouros"};
    baralho[22] = (Carta){"K (Rei)", 3, "Ouros"};
    baralho[23] = (Carta){"A", 4, "Ouros"};
    baralho[24] = (Carta){"2", 5, "Ouros"};
    baralho[25] = (Carta){"3", 6, "Ouros"};
    baralho[26] = (Carta){"7", 7, "Ouros"}; // Manilha (7 de Ouro)
}

void embaralharBaralho(Carta baralho[], int tamanho) {
    srand(time(NULL));

    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}

void inicializarJogadores(Jogador *humano, Jogador *ia) {
    printf("Digite seu nome: ");
    scanf("%s", humano->nome);
    humano->pontos = 0;

    strcpy(ia->nome, "CPU");
    ia->pontos = 0;
}

void distribuirCartas(Carta baralho[], Jogador *humano, Jogador *ia) {
    for (int i = 0; i < 3; i++) {
        humano->mao[i] = baralho[i];
        ia->mao[i] = baralho[i + 3];
    }
}

int main() {
    Carta baralho[27];
    Jogador jogadorHumano, jogadorIA;

    criarBaralho(baralho);
    embaralharBaralho(baralho, 27); 

    inicializarJogadores(&jogadorHumano, &jogadorIA);
    distribuirCartas(baralho, &jogadorHumano, &jogadorIA);

    printf("Baralho embaralhado:\n\n");
    for (int i = 0; i < 27; i++) {
        printf("%2d. %s de %s (valor: %d)\n", i + 1, baralho[i].nome, baralho[i].naipe, baralho[i].valor);
    }

    printf("Cartas de %s:\n", jogadorHumano.nome);
    for (int i = 0; i < 3; i++) {
        printf("- %s de %s (valor: %d)\n", jogadorHumano.mao[i].nome, jogadorHumano.mao[i].naipe, jogadorHumano.mao[i].valor);
    }

    return 0;
}
