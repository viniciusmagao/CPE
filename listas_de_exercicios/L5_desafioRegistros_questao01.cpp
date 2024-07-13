/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

DESAFIO REGISTROS
-------------------------------------
lista 0 - questao 01
-------------------------------------

***************************************************/


#include <iostream> //biblioteca padrao do C++
#include <string.h> //biblioteca padrao para String
#include <cstring>
#include <unistd.h> //para uso da instrucao sleep()
#include <cctype> //para usar a funcao toupper()

using namespace std; //pra retirar o std::



/*
------------------------------
CATEGORIA
*/

struct Categoria {
	int iCdCategoria;
	string sNmCategoria;
};

/*
------------------------------
SETOR
*/

struct Setor {
	int iCdSetor;
	string sNmSetor;
};

/*
------------------------------
EDIFICIO
*/

struct Edificio {
	int iCdEdificio;
	string sNmEdificio;
};

/*
------------------------------
CATEGORIA
*/

struct RamalMain {
    int iRamalNr;
    Categoria iRamalCategoria;
    Setor sRamalSetor;
    Edificio iRamalEdificio;
    int iRamalSala;
    string sRamalResp;
    string sRamalRespAteste;
};



//------------------------------
//PROTOTIPACAO DAS FUNCOES
void incluiRamal (RamalMain *pRamalOrigem, RamalMain *pVetorDeRamais);
void imprimirRamal (RamalMain *pVetorDeRamais, int i);
void impLinha();

const int iTamVetor = 10; //determina o tamanho da vetor do tipo struct RamalMain
int iQtdReg = 0; //quantidade de registros
int iRegAtual = 0;


//#MAIN
int main () {
	
	//cout << "" << endl;
	int iOpcao = 0;
	string sOpcao;
		
	RamalMain ramalOrigem;
	RamalMain vetorDeRamais[iTamVetor];

	
	RamalMain *pRamal; //ponteiro temporario
	//pRamal = &ramalOrigem; //ponteiro temporario recebe o endereco de ramalOrigem [nao utilizei, passei o endereco de ramalOrigem direto pra funcao]

	do {
		
		cout <<"#main" << endl;
		cout <<"\n";
		cout << "------------------------------------------------------------" << endl;
		cout << "  SISGRAMMA - Sistema de Gerenciamento de Ramais do MMA" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "\n" << endl;
		
		cout << "  1. Registrar um novo ramal" << endl;
		cout << "  2. Imprimir todos os ramais registrados" << endl;
		cout << "  9. Encerra SISGRAMMA" << endl;
		cout << "\n  Digite o numero da opcao desejada : ";
		cin >> iOpcao;
		
		switch (iOpcao) {
			case 1:	//#1-INCLUIR: inclui um ramal
				do {
					system("cls");
					incluiRamal (&ramalOrigem, &vetorDeRamais[iQtdReg]);
					vetorDeRamais[iQtdReg] = ramalOrigem; //salva os dados cadastrados no vetorDeRamais
					
					iQtdReg ++; //quantidade de registros
					
					cout << "\n" << endl;
					impLinha();
					cout << "Deseja cadastrar um novo ramal? [S/N] ";
					cin >> sOpcao;
					//sOpcao = toupper(sOpcao);
				} while (sOpcao != "n");
				system("cls");
				break;
			case 2: //#2-IMPRIMIR: imprimi o ramal registrado
				system("cls");
				//loop para imprimir todos os ramais registrados
				
				for (int i = 0; i < iQtdReg; i++) {
					imprimirRamal (&vetorDeRamais[i],i);
				}
				
				cout << "Foram registrados " << iQtdReg << " ramais." << endl;
    			cout << "\n" << endl;
    			sleep(3);
				system("cls");
				break;
			break;	
		};
		
	} while (iOpcao != 9);
}

/*
#1-INCLUIR: inclui um ramal
*/
void incluiRamal (RamalMain *pRamalOrigem, RamalMain *pVetorDeRamais) {
	
	int iTemp; //variavel temporaria para verificar as validade do ramal
	bool userError = false; //marcador pra saber se o usuario digitou algum dado fora da especificacao

	cout <<"#registro" << endl;
	cout <<"\n";
	cout << "------------------------------------------------------------" << endl;
	cout << "  REGISTRO DE RAMAL" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
	cout << "  Digite os dados do seu ramal\n" << endl;
    
    //valida o ramal digitado
	do {
	
	cout << "  Ramal..................: ";
    cin >> iTemp;
	    
	    if (iTemp < 1000 || iTemp >2999) {
			userError = true;			
			system("cls");
			cout <<"#registro" << endl;
			cout <<"\n";
	    	cout << "------------------------------------------------------------" << endl;
			cout << "  REGISTRO DE RAMAL" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << "\n" << endl;
	    	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	    	cout << "\n\t>> Ramal fora do intervalo permitido! <<" <<endl;
	    	cout << "\n! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	    	cout << "\nDigite um ramal entre 1000 e 2999\n" << endl;
	    	
		}
		
	} while (iTemp < 1000 || iTemp > 2999);
	
	//quando o usuario digitar um ramal valido, apos um erro, limpa a tela pra voltar a fluxo do registro
	if(userError) {
		system("cls");
		cout <<"#registro" << endl;
		cout <<"\n";
		cout << "------------------------------------------------------------" << endl;
		cout << "  REGISTRO DE RAMAL" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "\n" << endl;
		cout << "  Ramal..................: " << iTemp << endl;
	}
	
	
	pRamalOrigem->iRamalNr = iTemp; //salva o numero do ramal na struct
	cout << "  Categoria..............: ";
    cin >> pRamalOrigem->iRamalCategoria.iCdCategoria; //salva o numero da categoria na struct
    cout << "  Setor..................: ";
    cin >> pRamalOrigem->sRamalSetor.iCdSetor;
    cout << "  Edificio...............: ";
    cin >> pRamalOrigem->iRamalEdificio.iCdEdificio;
    cout << "  Sala:..................: ";
    cin >> pRamalOrigem->iRamalSala;
    cout << "  Responsavel pelo ramal.: ";
    cin >> pRamalOrigem->sRamalResp;
    cout << "  Responsavel pelo ateste: ";
    cin >> pRamalOrigem->sRamalRespAteste;

}


//#2-IMPRIMIR: imprimi o ramal registrado
void imprimirRamal (RamalMain *pVetorDeRamais,int i) {
	
	//system("cls");
	cout << "#imprimir" << endl;
	cout <<"\n";
	
	cout << "------------------------------------------------------------" << endl;
	cout << "  INFORMACOES GERAIS DO RAMAL - " << i+1 << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
	   
	cout << "  Ramal...................: " << pVetorDeRamais->iRamalNr << endl;
    cout << "  Categoria...............: " << pVetorDeRamais->iRamalCategoria.iCdCategoria << " " << pVetorDeRamais->iRamalCategoria.sNmCategoria << endl;
    cout << "  Setor...................: " << pVetorDeRamais->sRamalSetor.iCdSetor << " " << pVetorDeRamais->sRamalSetor.sNmSetor << endl;
    cout << "  Edificio................: " << pVetorDeRamais->iRamalEdificio.iCdEdificio << " " << pVetorDeRamais->iRamalEdificio.sNmEdificio << endl;
    cout << "  Sala....................: " << pVetorDeRamais->iRamalSala << endl;
    cout << "  Responsavel pelo ramal..: " << pVetorDeRamais->sRamalResp << endl;
    cout << "  Responsavel pelo ateste.: " << pVetorDeRamais->sRamalRespAteste << endl;
 	cout << "\n" << endl;
	impLinha(); 	
}

//#9-IMPRIMIR: imprime uma linha
void impLinha(){
	cout << "------------------------------------------------------------" << endl;
}
