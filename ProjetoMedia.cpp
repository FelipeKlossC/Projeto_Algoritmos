#include <stdio.h> //biblioteca para entrada e saída
#include <string.h> //biblioteca para manipular strings

#define MAX_ALUNOS 50 //define como constante a quantidade máxima de alunos que podem ser cadastrados
#define MAX_NOME 50 //define como constante o tamanho máximo do nome do aluno
#define NUM_NOTAS 3 //define como constante quantas notas cada aluno terá

//struct aluno
//vai servir para armazenar nome, notas, média e situação (aprovado, recuperação, reprovado)
typedef struct {
	char nome[MAX_NOME];
	float notas[NUM_NOTAS];
	float media;
	char situacao[20];
} Aluno;

//funções 
void limparBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF); //descarta tudo até o final da linha
} //vai evitar bugs na hora de digitar nomes e notas alternadamente 

void calcularSituacao(Aluno *a) {
	float soma = 0.0;
	for (int i = 0; i < NUM_NOTAS; i++) {
		soma += a->notas[i]; // soma todas as notas e a setinha acessa a array de notas dentro do struct 
	}
	a->media = soma / NUM_NOTAS; //calcula a média
	if (a->media >= 6.0) {
		strcpy(a->situacao, "Aprovado");
	}
	else if (a->media >= 4.0) {
		strcpy(a->situacao, "Recuperacao");
	}
	else {
		strcpy(a->situacao, "Reprovado");
	}
		
} //recebe um aluno e atualiza sua média e situação (aprovado, recuperação, reprovado)

void cadastrarAlunos(Aluno alunos[], int *qtd) {
	int n; //quantidade de alunos para cadastrar
	printf("\nQuantos alunos deseja cadastrar? ");
	scanf("%d", &n);
	limparBuffer();

	//verificar se cabe no vetor
	if((*qtd + n) > MAX_ALUNOS) {
		printf("Capacidade de alunos para cadastro fora do limite! Limite: %d\n", MAX_ALUNOS);
		return;
	}

	//loop para cadastrar cada aluno 
	for (int i = 0; i < n; i++) {
		printf("\nCadastro de aluno %d: \n", (*qtd) + 1);
		
		printf("Nome: ");
		fgets(alunos[*qtd].nome, MAX_NOME, stdin);
		alunos[*qtd].nome[strcspn(alunos[*qtd].nome, "\n")] = 0;
		
		//entrada das notas
		for(int j = 0; j < NUM_NOTAS; j++) {
			do {
				printf("Nota %d: ", j + 1);
				scanf("%f", &alunos[*qtd].notas[j]);
				limparBuffer();
				if (alunos[*qtd].notas[j] < 0 || alunos[*qtd].notas[j] > 10) {
					printf("Nota invalida! Digite um valor entre 0 e 10.\n");
				}
			} while (alunos[*qtd].notas[j] < 0 || alunos[*qtd].notas[j] > 10);
		}

		//calcule média e situação do aluno
		calcularSituacao(&alunos[*qtd]);
		(*qtd)++; //incrementa a quantidade total de alunos
	}
} //permite digitar o nome e notas dos alunos e guarda tudo dentro do vetor

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
} //mostra na tela os nomes, médias e situações de todos os alunos

int main () {
	Aluno alunos[MAX_ALUNOS]; //da um apelido para a struct aluno e coloca a capacidade máxima de 50 como definido na constante antes da função principal
	int qtdAlunos = 0; //contador de alunos que já foram cadastrados
	int opcao; //armazena a escolha do usuário
	do {
		printf("\n===== CALCULADORA DE MEDIAS ESCOLARES =====\n");
		printf("1. Cadastrar aluno(s)\n");
		printf("2. Exibir relatorio\n");
		printf("3. Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		limparBuffer(); //evita o bug de ler espaço sempre que digita char

		switch (opcao) {
			case 1: 
				cadastrarAlunos(alunos, &qtdAlunos); 
				break; //chama função para cadastrar alunos
			case 2: 
				exibirRelatorio(alunos, qtdAlunos); 
				break; //chama função para exibir relatório
			case 3: 
				printf("\nEncerrando Programa...\n"); 
				break; //encerra o programa
			default: 
				printf("\nOpcao invalida! Tente novamente!\n"); //erro para opção inválida se o usuário digitar
		}
	} while (opcao != 3); //repete até o usuário escolher a opção 3 (sair)
	return 0;
}
