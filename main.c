#include <stdio.h> // Standard Input Output (printf, scanf)
#include <stdlib.h> // Standard Library (rand e srand[aleatoriedade])
#include <string.h> // String Handling (manipular Strings)
#include <time.h> // Time Library (aux no srand)
#include <locale.h> // Locale Library (formatação)

typedef struct { // Struct da Carta
    char nome[20];
    int valor;
    char naipe[10];
} Carta;

typedef struct { // Struct do Jogador
    char nome[30];
    Carta mao[3];
    int pontos;
    int rodadasVencidas;
} Jogador;

void criarBaralho(Carta baralho[]) { // Esse procedimento cria e preenche o vetor "baralho" com as cartas do jogo //
    // Paus
    baralho[0] = (Carta){"J", 1, "Paus"};
    baralho[1] = (Carta){"Q", 2, "Paus"};
    baralho[2] = (Carta){"K", 3, "Paus"};
    baralho[3] = (Carta){"A", 4, "Paus"};
    baralho[4] = (Carta){"2", 5, "Paus"};
    baralho[5] = (Carta){"3", 6, "Paus"};
    baralho[6] = (Carta){"4", 10, "Paus"}; // Manilha

    // Copas
    baralho[7] = (Carta){"J", 1, "Copas"};
    baralho[8] = (Carta){"Q", 2, "Copas"};
    baralho[9] = (Carta){"K", 3, "Copas"};
    baralho[10] = (Carta){"A", 4, "Copas"};
    baralho[11] = (Carta){"2", 5, "Copas"};
    baralho[12] = (Carta){"3", 6, "Copas"};
    baralho[13] = (Carta){"7", 9, "Copas"}; // Manilha

    // Espadas
    baralho[14] = (Carta){"J", 1, "Espadas"};
    baralho[15] = (Carta){"Q", 2, "Espadas"};
    baralho[16] = (Carta){"K", 3, "Espadas"};
    baralho[17] = (Carta){"A", 8, "Espadas"}; // Manilha
    baralho[18] = (Carta){"2", 5, "Espadas"};
    baralho[19] = (Carta){"3", 6, "Espadas"};

    // Ouros
    baralho[20] = (Carta){"J", 1, "Ouros"};
    baralho[21] = (Carta){"Q", 2, "Ouros"};
    baralho[22] = (Carta){"K", 3, "Ouros"};
    baralho[23] = (Carta){"A", 4, "Ouros"};
    baralho[24] = (Carta){"2", 5, "Ouros"};
    baralho[25] = (Carta){"3", 6, "Ouros"};
    baralho[26] = (Carta){"7", 7, "Ouros"}; // Manilha
}

void embaralharBaralho(Carta baralho[], int tamanho) { 
    for (int i = tamanho - 1; i > 0; i--) { // Percorre de trás para frente
        int j = rand() % (i + 1); // Gera um numero aleatorio entre 0 e 26
        Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp; // As cartas trocam de lugar
    }
}

void inicializarJogadores(Jogador *humano, Jogador *ia) { // Zera os pontos e atribui nome
    printf("=====================================\n");
    printf("||          TRUCO GAME CLI          ||\n");
    printf("||                                  ||\n");
    printf("||      FEITO POR CAIO NOGUEIRA     ||\n");
    printf("=====================================\n");
    printf("Digite seu nome para comecar: ");
    scanf("%s", humano->nome);
    humano->pontos = 0;
    humano->rodadasVencidas = 0;

    strcpy(ia->nome, "CPU");
    ia->pontos = 0;
    ia->rodadasVencidas = 0;
}

void distribuirCartas(Carta baralho[], Jogador *humano, Jogador *ia) { // Distribui as cartas
    for (int i = 0; i < 3; i++) {
        humano->mao[i] = baralho[i];
        ia->mao[i] = baralho[i + 3];
    }
}

void mostrarCartas(Jogador *jogador, int usadas[]) { // Imprime as cartas do jogador
    printf("\nCartas de %s:\n", jogador->nome);
    for (int i = 0; i < 3; i++) {
        if (!usadas[i]) {
            printf("%d. %s de %s (valor: %d)\n", i + 1, jogador->mao[i].nome, jogador->mao[i].naipe, jogador->mao[i].valor);
        }
    }
}

int escolherCarta(Jogador *jogador, int usadas[]) { // Função para escolher a carta que irá jogar
    int escolha;
    do {
        printf("Escolha uma carta (1-3): ");
        scanf("%d", &escolha);
        escolha--; // Corrige índice para 0-2
    } while (escolha < 0 || escolha >= 3 || usadas[escolha]);

    usadas[escolha] = 1;
    return escolha;
}

int escolherCartaIA(Jogador *ia, int usadasIA[], int jogadorJaJogou, Carta cartaHumano) { // CPU (Tomada de Decisão)
    int melhor = -1;
    int menor = 999;
    for (int i = 0; i < 3; i++) {
        if (usadasIA[i]) continue;

        if (jogadorJaJogou && ia->mao[i].valor > cartaHumano.valor) {
            if (melhor == -1 || ia->mao[i].valor < ia->mao[melhor].valor)
                melhor = i;
        }

        if (ia->mao[i].valor < menor) {
            menor = ia->mao[i].valor;
        }
    }

    int escolha = melhor != -1 ? melhor : -1;
    if (escolha == -1) {
        for (int i = 0; i < 3; i++) {
            if (!usadasIA[i] && ia->mao[i].valor == menor) {
                escolha = i;
                break;
            }
        }
    }

    usadasIA[escolha] = 1;
    return escolha;
}

int determinarVencedorRodada(Carta cartaHumano, Carta cartaIA) { // Compara as cartas e determina um vencedor
    printf("\nVoce jogou: %s de %s\n", cartaHumano.nome, cartaHumano.naipe);
    printf("IA jogou: %s de %s\n", cartaIA.nome, cartaIA.naipe);

    if (cartaHumano.valor > cartaIA.valor) {
        printf("Voce venceu a rodada!\n");
        return 1;
    } else if (cartaHumano.valor < cartaIA.valor) {
        printf("IA venceu a rodada!\n");
        return 2;
    } else {
        printf("Rodada empatada!\n");
        return 0;
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    Carta baralho[27];
    Jogador jogadorHumano, jogadorIA;

    inicializarJogadores(&jogadorHumano, &jogadorIA);

    int partida = 1;
    while (jogadorHumano.rodadasVencidas < 3 && jogadorIA.rodadasVencidas < 3 && partida <= 5) {
        printf("\n========== MAO %d ==========\n", partida);
        criarBaralho(baralho);
        embaralharBaralho(baralho, 27);
        distribuirCartas(baralho, &jogadorHumano, &jogadorIA);

        int usadasHumano[3] = {0}, usadasIA[3] = {0};
        jogadorHumano.pontos = 0;
        jogadorIA.pontos = 0;

        int quemComeca = rand() % 2; // 0 humano, 1 IA

        for (int rodada = 0; rodada < 3; rodada++) {
            printf("\n--- Rodada %d ---\n", rodada + 1);

            int escolhaHumano, escolhaIA;

            if (quemComeca == 0) {
                mostrarCartas(&jogadorHumano, usadasHumano);
                escolhaHumano = escolherCarta(&jogadorHumano, usadasHumano);
                escolhaIA = escolherCartaIA(&jogadorIA, usadasIA, 1, jogadorHumano.mao[escolhaHumano]);
            } else {
                escolhaIA = escolherCartaIA(&jogadorIA, usadasIA, 0, jogadorHumano.mao[0]); // jogador ainda não jogou
                mostrarCartas(&jogadorHumano, usadasHumano);
                escolhaHumano = escolherCarta(&jogadorHumano, usadasHumano);
            }

            int resultado = determinarVencedorRodada(jogadorHumano.mao[escolhaHumano], jogadorIA.mao[escolhaIA]);
            if (resultado == 1) jogadorHumano.pontos++;
            else if (resultado == 2) jogadorIA.pontos++;

            if (jogadorHumano.pontos == 2 || jogadorIA.pontos == 2) break;
            quemComeca = 1 - quemComeca;
        }

        if (jogadorHumano.pontos > jogadorIA.pontos) {
            jogadorHumano.rodadasVencidas++;
            printf("\nVocê venceu a mao!\n");
        } else if (jogadorIA.pontos > jogadorHumano.pontos) {
            jogadorIA.rodadasVencidas++;
            printf("\nIA venceu a mao!\n");
        } else {
            printf("\nEmpate na mao!\n");
        }

        partida++;
        printf("Placar: %s %d x %d %s\n", jogadorHumano.nome, jogadorHumano.rodadasVencidas, jogadorIA.rodadasVencidas, jogadorIA.nome);
    }

    printf("\n=== FIM DO JOGO ===\n");
    if (jogadorHumano.rodadasVencidas > jogadorIA.rodadasVencidas)
        printf("%s venceu o jogo!\n", jogadorHumano.nome);
    else
        printf("A IA venceu o jogo!\n");

    return 0;
}

// chcp 65001 no terminal (Acentuação)

