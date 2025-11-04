#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 50
#define MAX_NOME 50
#define NUM_NOTAS 3

// Estrutura para armazenar dados de cada aluno
typedef struct {
    char nome[MAX_NOME];
    float notas[NUM_NOTAS];
    float media;
    char situacao[20];
} Aluno;

// Limpa o buffer do teclado para evitar problemas de Enter salvo com fgets ou scanf
void limparBuffer() { //pesquisar
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Calcula a média e define a situacão do aluno (Aprovado, Recuperacao ou Reprovado)
Aluno calcularSituacao(Aluno a) { //pesquisar
    float soma = 0.0; //iniciada em 0
    for (int i = 0; i < NUM_NOTAS; i++) {
        soma += a.notas[i]; //acessa a struct de alunos, agora, com apelido de "a"
    }
    a.media = soma / NUM_NOTAS; //cálculo da média

    // Copia a string correta para o campo situacao usando strcpy
    // Necessário porque em C não é possível atribuir strings diretamente a arrays
    if (a.media >= 6.0) {
        strcpy(a.situacao, "Aprovado");
    } else if (a.media >= 4.0) { //acessa a struct da média do aluno
        strcpy(a.situacao, "Recuperacao");
    } else {
        strcpy(a.situacao, "Reprovado"); //acessa a struct da situação do aluno
    } //utilizando o strcpy, o campo situação da struct aluno passará a ser "reprovado"

    return a; // Retorna o aluno atualizado
}

// Cadastra novos alunos, lendo nome e notas, e retorna a quantidade atualizada
int cadastrarAlunos(Aluno alunos[], int qtd) { //alunos é um parâmetro, um vetor da struct aluno
    int n; //criação da varíavel para saber a quantia de alunos para se cadastrar
    printf("\nQuantos alunos deseja cadastrar? ");
    scanf("%d", &n);
    limparBuffer();

    if ((qtd + n) > MAX_ALUNOS) { 
        printf("Capacidade de alunos para cadastro fora do limite! Limite: %d\n", MAX_ALUNOS);
        return qtd;
    }

    for (int i = 0; i < n; i++) {
        printf("\nCadastro de aluno %d: \n", qtd + 1);

        // Lê o nome completo do aluno, incluindo espaços, usando fgets
        printf("Nome: ");
        fgets(alunos[qtd].nome, MAX_NOME, stdin);

        // Remove o '\n' que fgets deixa no final da string
        // strcspn retorna a posição do '\n' dentro da string
        alunos[qtd].nome[strcspn(alunos[qtd].nome, "\n")] = 0;

        // Lê as notas, garantindo que estejam entre 0 e 10
        for (int j = 0; j < NUM_NOTAS; j++) {
            do {
                printf("Nota %d: ", j + 1);
                scanf("%f", &alunos[qtd].notas[j]);
                limparBuffer();
                if (alunos[qtd].notas[j] < 0 || alunos[qtd].notas[j] > 10) {
                    printf("Nota invalida! Digite um valor entre 0 e 10.\n");
                }
            } while (alunos[qtd].notas[j] < 0 || alunos[qtd].notas[j] > 10); //criação de loop para ficar dando inválido
        }

        alunos[qtd] = calcularSituacao(alunos[qtd]); // Atualiza média e situação
        qtd++; // Incrementa contador de alunos
    }

    return qtd; // Retorna nova quantidade de alunos cadastrados
}

// Exibe relatório com nome, média e situação de todos os alunos
void exibirRelatorio(Aluno alunos[], int qtd) {
    if (qtd == 0) {
        printf("\nNenhum aluno cadastrado ainda.\n");
        return;
    }

    printf("\n===== Relatorio dos Alunos =====\n");
    printf("NOME\t\tMEDIA\tSITUACAO\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < qtd; i++) {
        printf("%s\t\t%.2f\t%s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }
}

// Função principal: exibe menu e chama funções de cadastro e relatório
int main() {
    Aluno alunos[MAX_ALUNOS];
    int qtdAlunos = 0; // Contador de alunos cadastrados
    int opcao;
// Cria um vetor chamado 'alunos', com até MAX_ALUNOS posições.
// Cada posição do vetor é uma struct do tipo 'Aluno',
// usada para armazenar os dados (nome, nota, situação) de cada aluno.

    do {
        printf("\n===== CALCULADORA DE MEDIAS ESCOLARES =====\n");
        printf("1. Cadastrar aluno(s)\n");
        printf("2. Exibir relatorio\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                qtdAlunos = cadastrarAlunos(alunos, qtdAlunos);
                break;
            case 2:
                exibirRelatorio(alunos, qtdAlunos);
                break;
            case 3:
                printf("\nEncerrando Programa...\n"); 
                break;
            default:
                printf("\nOpcao invalida! Tente novamente!\n");
        }
    } while (opcao != 3); //pesquisar

    return 0;
}
