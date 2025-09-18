#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== STRUCT ==================== //
// Estrutura que representa um território
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

// ==================== FUNÇÕES ==================== //

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do Territorio %d\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", mapa[i].nome); // permite espaços no nome

        printf("Digite a cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n===== Lista de Territorios =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exercito: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
}

// Função para exibir menu de territórios disponíveis para ataque
void exibirMenuAtaque(Territorio* mapa, int qtd) {
    printf("\n===== TERRITORIOS DISPONIVEIS PARA ATAQUE =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s (%s) - Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nERRO: Nao e permitido atacar um territorio da mesma cor!\n");
        return;
    }

    printf("\n=== INICIO DA BATALHA ===\n");
    printf("%s (%s) esta atacando %s (%s)!\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    // Rolagem de dados (1 a 6) para ambos os lados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado Atacante: %d | Dado Defensor: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA: %s conquistou %s!\n", atacante->nome, defensor->nome);

        // Transferência de tropas e cor
        int tropasConquistadoras = atacante->tropas / 2;
        defensor->tropas = tropasConquistadoras;
        atacante->tropas -= tropasConquistadoras;
        strcpy(defensor->cor, atacante->cor);
        
        printf("Tropas transferidas: %d\n", tropasConquistadoras);
    } else {
        printf("DERROTA: %s defendeu com sucesso!\n", defensor->nome);
        // Atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("%s perdeu uma tropa. Tropas restantes: %d\n", 
                   atacante->nome, atacante->tropas);
        }
    }
    printf("=== FIM DA BATALHA ===\n");
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ==================== MAIN ==================== //
int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int qtd;
    printf("Digite o numero de territorios a serem cadastrados: ");
    scanf("%d", &qtd);

    // Valida quantidade mínima de territórios
    if (qtd < 2) {
        printf("Erro: Eh necessario pelo menos 2 territorios para o jogo!\n");
        return 1;
    }

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, qtd);

    // Exibe territórios cadastrados
    printf("\n===== TERRITORIOS CADASTRADOS =====\n");
    exibirTerritorios(mapa, qtd);

    // Loop principal de ataques
    char continuar = 's';
    int turno = 1;
    
    while (continuar == 's' || continuar == 'S') {
        printf("\n\n=== TURNO %d ===\n", turno);
        
        // Exibe menu com territórios disponíveis
        exibirMenuAtaque(mapa, qtd);

        // Seleção de territórios para ataque
        int idxAtacante, idxDefensor;
        printf("\nESCOLHA O ATAQUE:\n");
        printf("Numero do territorio ATACANTE: ");
        scanf("%d", &idxAtacante);
        printf("Numero do territorio DEFENSOR: ");
        scanf("%d", &idxDefensor);

        // Validação de índices
        if (idxAtacante < 1 || idxAtacante > qtd || idxDefensor < 1 || idxDefensor > qtd) {
            printf("\nERRO: Territorio invalido! Escolha numeros entre 1 e %d.\n", qtd);
        } else if (idxAtacante == idxDefensor) {
            printf("\nERRO: Nao e possivel atacar o proprio territorio!\n");
        } else {
            // Executa o ataque
            atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
            
            // Exibe situação atualizada
            printf("\n===== SITUACAO ATUALIZADA POS-BATALHA =====\n");
            exibirTerritorios(mapa, qtd);
        }

        // Pergunta se deseja continuar
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        turno++;
    }

    // Libera memória alocada
    liberarMemoria(mapa);
    printf("\nMemoria liberada. Jogo encerrado!\n");

    return 0;
}