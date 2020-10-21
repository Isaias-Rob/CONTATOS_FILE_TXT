// DESENVOLVIDO POR ISAIAS ROBERTO DE LIMA E SILVA


#include<stdio.h>							   
#include<stdlib.h>
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<cstdio>

using namespace std;
struct Dados
{
	string nome, email, telefone; // DADOS PARA CADASTRO DE CONTATO
};
struct ElementoDaLista_Simples {
	Dados contato;
	struct ElementoDaLista_Simples* prox; // LISTA ENCADEADA SIMPLES (NAO-CIRCULAR)
} *Head;

// DECLARAÇÃO DAS FUNÇÕES
int menu();
void InserirInicio(string nomef, string emailf, string telefonef);
void Listar();
void quicksort(ElementoDaLista_Simples** vet, int p, int u);
int particao(ElementoDaLista_Simples** vet, int p, int u);
void troca(ElementoDaLista_Simples** vet, int i, int j);
int Remover(string nomef);





int  main() {
	int op, c, d = 0, x = 0;
	string temp, nome, email, telefone; // VARIAVES LOCAIS PARA INSERÇÃO
	setlocale(LC_ALL, "Portuguese");
	Head = NULL;
	ifstream arquivo; // ARQUIVO EM FORMATO DE ENTRADA, PREENCHER LISTA SE HOUVER DADOS DISPONIVEIS
	ofstream arquivout; // ARQUIVO EM FORMATO DE SAIDA, SALVAR NO DISCO APOS ENCERRAR PROGRAMA
	arquivo.open("contatos.txt"); // ABRINDO PARA PREENCHIMENTO
	if(!(arquivo.is_open()))
	{
		cout << "Houve um erro ao abrir o arquivo.txt, nao ha informacoes no disco a serem carregadas" << endl;
		system("Pause");
		arquivo.close();
	}
	else
	{
		while(getline(arquivo, temp)) // A CADA QUEBRA DE LIHA
		{
			x++; // VARIAVEL DE CONTROLE PARA SABER EM QUAL LINHA ESTA (1- NOME, 2- EMAIL E 3- TELEFONE)
			if(x == 1)
			{
				nome = temp;
			}
			else if(x==2)
			{
				email = temp;
			}
			else
			{
				telefone = temp;
				x = 0;
				InserirInicio(nome, email, telefone); // INSERINDO SEMPRE NO INICIO
			}
		
		}
	}
	arquivo.close(); // SOMENTE NECESSARIO AO INICIAR O PROGRAMA
	arquivout.open("contatos.txt", ios::app); // ABRINDO EM MODO DE SAIDA, INDO AO FINAL DO ARQUIVO PARA COLOCAR DADOS
	if(!(arquivout.is_open()))
	{
		cout << "Houve um erro ao abrir o arquivo.txt, informacoes nao serao salvas no disco, o programa deve ser encerrado" << endl;
		system("Pause");
		return 0;
	}
	while (1) {
		op = menu(); // FUNÇAO INT PARA RETORNAR OPÇAO DO MENU
		switch (op) {
		case 1:
			printf("Digite o nome: "); // CADASTRO DE CONTATOS
			getline(cin, nome);
			arquivout << nome << endl; // SALVANDO NAS LINHAS DO ARQUIVO
			printf("Digite o email: ");
			getline(cin, email);
			arquivout << email << endl;
			printf("Digite o telefone: ");
			getline(cin, telefone);
			arquivout << telefone << endl;
			InserirInicio(nome, email, telefone); // INSERÇAO PADRAO - INICIO DA LISTA
			break;
		case 2:
			int res;
			printf("Digite o nome do contato a ser removido (exatamente como foi escrito): ");
			getline(cin, nome); // REMOÇAO POR NOME
			res = Remover(nome); // VALOR PARA SABER SE FOI REMOVIDO COM SUCESSO
			if (res == 1)
			{
				printf("Contato removido.\n");
				arquivout.close(); // SE FOI REMOVIDO, UM NOVO ARQUIVO ALTERADO FOI CRIADO, FECHAR PARA EFETUAR TROCA
				remove("contatos.txt"); // DELETANDO ARQUIVO ANTIGO
				rename("novo.txt", "contatos.txt"); // RENOMEANDO DE VOLTA PARA NOME PADRAO
				arquivout.open("contatos.txt", ios::app); // REABRINDO
			}
			else
				printf("Contato nao encontrado, Verifique a ortografia e tente novamente\n");
			system("Pause");
			break;
		case 3:
			Listar(); // LISTAGEM DOS CONTATOS NA LISTA
			break;
		case 4:
			arquivout.close();
			return 0; // SAIR DO PROGRAMA
		default:
			printf("Invalido\n");
		}
	}
	return 0;
}

int menu() { // FUNÇAO DE MENU
	int op, c;
	system("Cls");
	printf("1.Criar Contato\n");
	printf("2.Remover Contato\n");
	printf("3.Listar Contatos\n");
	printf("4.Sair\n");
	printf("Digite sua escolha: ");
	scanf("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.
	system("Cls");
	return op;
}

void InserirInicio(string nomef, string emailf, string telefonef) // INSERÇAO
{
	ElementoDaLista_Simples* NovoElemento; // ELEMENTO PARA INSERIR
	NovoElemento = new ElementoDaLista_Simples;
	NovoElemento->contato.nome = nomef;
	NovoElemento->contato.email = emailf;
	NovoElemento->contato.telefone = telefonef;

	if (Head == NULL) // SE FOR PRIMEIRA INSERÇAO (HEAD VALENDO NULL)
	{
		Head = NovoElemento;
		Head->prox = NULL;
	}
	else
	{
		NovoElemento->prox = Head; // NOVO ELEMENTO PASSA A SER O HEAD
		Head = NovoElemento;
	}
}



int Remover(string nomef)
{
	ElementoDaLista_Simples* ElementoVarredura; // VARREDURA NA LISTA
	ElementoVarredura = new ElementoDaLista_Simples;
	ElementoDaLista_Simples* Anterior; // ANTERIOR AO VALOR QUE SERA REMOVIDO
	Anterior = new ElementoDaLista_Simples;
	string temp;
	int i = 0;
	bool encontrado = false; // CONTROLE 
	ofstream novoarq; // ARQUIVO NOVO EM MODO DE SAIDA
	ifstream oldarq; // ARQUIVO VELHO EM MODO DE ENTRADA
	novoarq.open("novo.txt", ios::app); // ABRINDO NOVO ARQUIVO
	oldarq.open("contatos.txt"); // ABRINDO VELHO ARQUIVO (PRINCIPAL)
	ElementoVarredura = Head; // COMEÇANDO PELO HEAD
	while (ElementoVarredura != NULL) {
		if (ElementoVarredura->contato.nome == nomef) { // COMPARANDO AS STRINGS
			if (ElementoVarredura == Head) {
				Head = ElementoVarredura->prox; // SE FOR O HEAD, O PROXIMO ELEMENTO SE TORNA O HEAD
				delete ElementoVarredura; // DELETAR
				while(getline(oldarq, temp))
				{
					if(temp == nomef)
					{
						encontrado = true; // SE ENCONTROU, VERDADEIRO
					}
					if(encontrado == true) // CASO TENHA ENCONTRADO, É PRECISO PULAR AS PROXIMAS 3 LINHAS POIS NELAS ESTÃO OS DADOS
					{
						i++;
						if(i > 2)
						{
							encontrado = false; // APOS ISSO, CONTINUAR A PREENCHER O NOVO ARQUIVO
						}
					}
					else
					{
						novoarq << temp << endl; // PREENCHENDO NOVO ARQUIVO
					}						
				}
				oldarq.close();
				novoarq.close();
				return 1;
			}
			else {
				Anterior->prox = ElementoVarredura->prox; // SE NAO FOR O HEAD, O ANTERIOR DEVE PULAR ESSE ELEMENTO E APONTAR PARA O SEGUINTE
				delete ElementoVarredura; // DELETAR
				while(getline(oldarq, temp))
				{
					if(temp == nomef) // MESMO CODIGO, MAS PRECISA SER APLICADO POR CONTA DA LISTA, VISTO QUE SÃO DUAS CONDIÇOES DIFERENTES PARA A LISTA E UMA PARA O AQRUIVO
					{
						encontrado = true;
					}
					if(encontrado == true)
					{
						i++;
						if(i > 2)
						{
							encontrado = false;
						}
					}
					else
					{
						novoarq << temp << endl;
					}						
				}
				oldarq.close();
				novoarq.close();
				return 1;
			}
		}
		else {
			Anterior = ElementoVarredura; // ENQUANTO NAO ACHA, PULA PARA O PROXIMO PARA COMPARAÇAO
			ElementoVarredura = ElementoVarredura->prox;
		}
	}
	return 0; // NAO ACHOU, RETORNAR 0
}


void Listar() // FUNÇAO DE LISTAGEM
{
	int menu, c, a = 0;
	ElementoDaLista_Simples* ElementoVarredura; // VARRER A LISTA
	ElementoVarredura = new ElementoDaLista_Simples;
	ElementoDaLista_Simples** vetor; // PONTEIRO PARA PONTEIRO (CASO SEJA SOLICITADO ORDEM ALFABETICA)
	ElementoVarredura = Head;
	if (ElementoVarredura == NULL) { // SE NAO HOUVER ELEMENTOS, RETORNAR
		return;
	}
	do
	{
		system("CLS");
		cout << "Deseja filtrar por ordem alfabetica?\n1 para sim e 2 para nao" << endl;
		fflush(stdin); // LIMPAR BUFFER POR CAUSA DO GETLINE NA MAIN
		cin >> menu;
		while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.
	} while (menu < 1 || menu > 2); 
	if (menu == 1) // CASO ORDEM ALFABETICA SOLICITADA
	{
		while (ElementoVarredura != NULL)
		{
			a++; // CONTAR QUANTOS ELEMENTOS EXISTEM NA LISTA
			ElementoVarredura = ElementoVarredura->prox;
		}
		vetor = new ElementoDaLista_Simples * [a]; // CRIAR VETOR DE PONTEIROS COM A QUANTIDADE DE INDICES QUE EXISTEM NA LISTA
		ElementoVarredura = Head;
		a = 0; // ZERAR A PARA COMEÇAR A CONTABILIZAR OS ENDEREÇOS
		while (ElementoVarredura != NULL)
		{
			vetor[a] = ElementoVarredura; // SALVANDO OS ENDEREÇOS NA ORDEM EM QUE A LISTA ESTÁ
			a++; // CONTROLE DE INDICE
			ElementoVarredura = ElementoVarredura->prox;

		}
		quicksort(vetor, 0, a - 1); // FUNÇAO QUICKSORT POR MEIO DE PONTEIROS
		for (int i = 0; i < a; i++) { // PRINTAR OS VALORES ARRUMADOS (NAO ALTERA OS VALORES ORIGINAIS NA ORDEM DE CADASTRO)
			cout << "=======================================================================" << endl;
			cout << "Nome: " << vetor[i]->contato.nome << endl;
			cout << "E-mail: " << vetor[i]->contato.email << endl;
			cout << "Telefone: " << vetor[i]->contato.telefone << endl;
			cout << "=======================================================================" << endl;
			cout << endl;
		}
	}
	else
	{
		while (ElementoVarredura != NULL) {
			cout << "=======================================================================" << endl; // PRINTAR VALORES NA ORDEM DE CADASTRO
			cout << "Nome: " << ElementoVarredura->contato.nome << endl;
			cout << "E-mail: " << ElementoVarredura->contato.email << endl;
			cout << "Telefone: " << ElementoVarredura->contato.telefone << endl;
			cout << "=======================================================================" << endl;
			cout << endl;
			ElementoVarredura = ElementoVarredura->prox;
		}
	}
	printf("\n");

	system("pause");
	return;
}

void quicksort(ElementoDaLista_Simples** vet, int p, int u) //QUICKSORT COM PONTEIROS
{
	int m;
	if (p < u)
	{
		m = particao(vet, p, u);
		quicksort(vet, p, m);
		quicksort(vet, m + 1, u);
	}
}


int particao(ElementoDaLista_Simples** vet, int p, int u) //encontra o pivo, faz varreduras e trocas
{
	int pivo_pos, i, j;
	ElementoDaLista_Simples* pivo;
	pivo_pos = (p + u) / 2;
	pivo = vet[pivo_pos]; // SALVANDO O ENDEREÇO DO DADO E NAO O DADO

	i = p - 1;
	j = u + 1;
	while (i < j)
	{
		do //testa os valores da direita
		{
			j--;
		} while (vet[j]->contato.nome > pivo->contato.nome); // TESTANDO OS VALORES DO ENDEREÇO

		do //testa os valores da esquerda
		{
			i++;
		} while (vet[i]->contato.nome < pivo->contato.nome); // TESTANDO OS VALORES DO ENDEREÇO

		if (i < j)
			troca(vet, j, i); // REALIZAR A TROCA
	}
	return j;
}

void troca(ElementoDaLista_Simples** vet, int i, int j) // TROCA POR MEIO DE ENDEREÇOS
{
	ElementoDaLista_Simples* aux; // AUXILIAR COMO PONTEIRO
	aux = vet[i]; // NAO HA COPIA DE DADOS, SOMENTE UM VETOR TROCANDO OS ENDEREÇOS DOS VALORES ORIGINAIS EM UM VETOR TEMPORARIO
	vet[i] = vet[j];
	vet[j] = aux;
}
