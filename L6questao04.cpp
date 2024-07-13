/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

-------------------------------------
lista 06 - questao 04
-------------------------------------

Faça um programa que funcione como um diario de classe. Ao cadastrar um aluno, e criado 
um arquivo cujo nome e o mesmo do aluno (nome_do_aluno.txt ). A primeira linha do 
arquivo e sempre uma matricula , que e informada no cadastro. Ao ser iniciado, e mostrado 
na tela um menu com as seguintes opçoes:
 1. Cadastrar aluno
 2. Adicionar nota de um aluno
 3. Calcular media de um aluno
 4. Fechar o programa
Se o usuario escolher a opçao 2, o nome e a nota do aluno devem ser informados para o 
programa, que salvara o valor em uma nova linha no arquivo correspondente aquele aluno. 
Se o usuario escolher a opçao 3, novamente deve ser informado o nome do aluno, para que 
o programa leia o arquivo, calcule a media e imprima na tela.
Nas opçoes 1 e 2 (2 e 3?), caso seja informado o nome de um aluno nao cadastrado, isso deve ser 
informado ao usuario. O programa deve sempre voltar ao menu ate que seja solicitada a 
opçao 4.

***************************************************/


#include <iostream>
#include <string>
#include <unistd.h> //para utilizar a funcao sleep()
#include <iomanip> //para usar setprecision()
#include <fstream>

using namespace std;


//variaveis globais
string aux = "";
string iOpcao = "null";

//struct-registro com as informacoes de um aluno
struct alunoModelo {
	string sMatricula;
	string sNome;
	float fNota;
};

//prototipacao das funcoes
void cabecalho (string iOpcao);
void gravaCadastro(alunoModelo *aluno, string iOpcao);
void calculaMedia(alunoModelo *aluno);


//main
int main () {

//declaracao das variaveis
int iSeqMat = 1;
string sYesNo = "N";
alunoModelo aluno;

	do {
		cabecalho(iOpcao);
		cin >> iOpcao;
		
		//cadastra aluno
		if(iOpcao == "1"){
				iSeqMat++;			
				//adiciona 0's a esquerda no numero da matricula
				for (int i =0; i < 4-to_string(iSeqMat).size(); i++){
					aux += "0";
				}
				//completa o codigo da matricula com o 'A' de aluno
				aluno.sMatricula = "A" + aux + to_string(iSeqMat);
				
				do {
					cabecalho(iOpcao);
					cout << "Digite o nome do aluno: ";
					cin >> aluno.sNome;
					cabecalho(iOpcao);
					cout << "Confirma a matricula de " << aluno.sNome << " ? [S/N] ";
					cin >> sYesNo;
				}while(sYesNo != "s");
				
				cabecalho(iOpcao);
				//grava o cadastro do aluno no arquivo .txt
				gravaCadastro(&aluno, iOpcao);
				
				cout << ">> Aluno cadastrado! <<" << endl;
				cout << "\n";
				cout << "Matricula (automatica): " << aluno.sMatricula << endl;
				cout << "Nome: " << aluno.sNome;
				sleep(2);
				iOpcao = "null";
		}
		
		//inclui nota
		else if(iOpcao == "2"){
				cabecalho(iOpcao);
				cout << "Informe o nome do aluno e sua nota" << endl;
				cout << "\n";
				cout << "Nome: ";
				cin >> aluno.sNome;
				cout << "Nota: ";
				cin >> aluno.fNota;
				
				//grava as informacoes no arquivo do aluno
				gravaCadastro(&aluno, iOpcao);
				cabecalho(iOpcao);
				iOpcao = "null";
		}
		
		//calcula media
		else if (iOpcao == "3"){
			cabecalho(iOpcao);
			cout << "Informe o nome do aluno " << endl;
			cout << "\n";
			cout << "Nome: ";
			cin >> aluno.sNome;
			//calcula a media
			calculaMedia(&aluno);
		}
		
		//mensagem quando o usuario digita uma opcao invalida
		else if(iOpcao != "4"){
			cout << "\nDigite o numero correspondente a uma das opcao acima..." << endl;
		}
	}while (iOpcao != "4");
	
	cabecalho(iOpcao);
	return 0;
}

//calcula a media de todas as notas registradas para o aluno
void calculaMedia(alunoModelo *aluno){
	
	int qtdAvaliacoes = 0;
	float somaNotas = 0;
	
	//abre o arquivo do aluno para leitura
	ifstream arqIn;
	arqIn.open(aluno->sNome + ".txt");
	if(!arqIn.is_open()){
		iOpcao = "error";
		cabecalho(iOpcao);
		iOpcao = "null";
	}
	//calcula a media do aluno
	else {
		while(getline(arqIn, aux)){
			if(aux.substr(0, 6)=="Nota P"){
				//acumula as notas que aluno tem
				somaNotas += stof(aux.substr(8,4));
				//atualiza a quantidade de avaliacoes registradas
				qtdAvaliacoes = stoi(aux.substr(6,1));
			}
		}
		//fixa o numero de casas decimais em 2 digitos
		cout << fixed << setprecision(2);
		cout << "\nA media do aluno " << aluno->sNome << " e " << (somaNotas/qtdAvaliacoes) << endl;
		cout << "\n";
		cout << "------------------------------------------------------------" << endl;
		sleep(5);
		iOpcao = "null";
	}
	arqIn.close();
}


//cria e escreve em arquivo .txt o cadastro do aluno
void gravaCadastro(alunoModelo *aluno, string iOpcao){
	
	int iP = 1;
		
	//grava cadastro
	if(iOpcao == "1"){
		//cria um arquivo para escrita
		ofstream arqAluno;
		arqAluno.open(aluno->sNome + ".txt", ios::out);
		arqAluno << "Matricula: " << aluno->sMatricula << "\n"	;
		arqAluno << "Nome: " << aluno->sNome << "\n"	;
		arqAluno.close();
	}
	
	//grava nota
	else if(iOpcao == "2"){
		//abre o arquivo para leitura e verifica se o aluno ja tem alguma nota registrada e qual o numero da prova
		ifstream arqAluno;
		arqAluno.open(aluno->sNome + ".txt", ios::in);
		if(arqAluno.is_open()){
			while(getline(arqAluno, aux)){
				if(aux.substr(0, 6)=="Nota P"){
					iP = stoi(aux.substr(6,1)) + 1;
				}
			}
			arqAluno.close();
			
			//abre o arquivo para escrita, acrescenta uma linha no final do arquivo e registra a nota
			ofstream arqAluno;
			arqAluno.open(aluno->sNome + ".txt", ios::app);
			arqAluno << "Nota P" << iP << ": " << aluno->fNota << "\n";
			arqAluno.close();
			
			cout << ">> Nota registrada! <<" << endl;
			cout << "\n" << endl;
			
			//mostra como esta o cadastro-historico do aluno
			cout << "# historico do aluno #\n";
			cout << "\n";
			ifstream arqIn;
			arqIn.open(aluno->
			sNome + ".txt", ios::in);
			while(getline(arqIn, aux)){
				cout << aux << endl;
			}
			cout << "\n";
			cout << "------------------------------------------------------------" << endl;
			sleep(3);
			arqIn.close();
		}
		//caso de aluno nao cadastrado
		else {
			iOpcao = "error";
			cabecalho(iOpcao);
		}
	}
}

//cabecalhos das telas
void cabecalho (string iOpcao) {
	//main
	if(iOpcao == "null"){
			system("cls");
			cout << "#main" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << "\n";
			cout << "Digite a opcao desejada: " << endl;
			cout << "\n";
			cout << "1. Cadastrar aluno" << endl;
			cout << "2. Adicionar nota de um aluno" << endl;
			cout << "3. Calcular media de um aluno" << endl;
			cout << "4. Fechar o programa" << endl;
			cout << "\n";
			cout << "------------------------------------------------------------" << endl;
	}
	//cadastro
	else if(iOpcao == "1"){
			system("cls");
			cout << "#cadastro" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << "\n";
	}
	//inclui nota
	else if(iOpcao == "2"){
			system("cls");
			cout << "#nota" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << "\n";
	}
	//calcula media
	else if(iOpcao == "3"){
			system("cls");
			cout << "#media" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << "\n";
	}
	//encerra programa
	else if(iOpcao == "4"){
		system("cls");
		cout << "#exit" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "Programa encerrado!" << endl;
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "------------------------------------------------------------" << endl;
	}
	//aluno nao cadastrado
	else if(iOpcao == "error"){
		system("cls");
		cout << "#error" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "\n";
		cout << "\n";
		cout << ">> Aluno nao cadastrado! <<" << endl;
		cout << "\nUtilize a opcao '1. Cadastrar aluno' primeiro." << endl;
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "------------------------------------------------------------" << endl;
		sleep(3);
	}
}
