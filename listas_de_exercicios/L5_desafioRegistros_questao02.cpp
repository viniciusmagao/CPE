/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

DESAFIO REGISTROS
-------------------------------------
lista 05 - questao 02
-------------------------------------

***************************************************/


#include <iostream> //biblioteca padrao do C++
#include <string> //biblioteca padrao para String
#include <cstring>
#include <unistd.h> //para uso da instrucao sleep()
#include <cctype> //para usar a funcao toupper()

#define TAMANHO_VETOR 2

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


/*
------------------------------
PROTOTIPACAO DAS FUNCOES
*/

//#0-MAIN
void mainCabecalho();

//#1-INCLUIR
void incluirRamal (RamalMain *pRamalOrigem, RamalMain *pVetorDeRamais);
void incluirRamalCabecalho();
void incluirRamalErroMemoriaCheia();
void incluirRamalErroForaIntervalo();
void incluirRamalErroRamalExistente();

//#3-IMPRIMIR
void imprimirRamal (RamalMain *pVetorDeRamais, int i);
void imprimirRamalCabecalho();

//#4-PESQUISAR
void pesquisarRamal (RamalMain *pVetorDeRamais, int iTipoPesq);
void pesquisarRamalCabecalho();

//#9-OUTRAS
bool verificarRamal (RamalMain *pVetorDeRamais, int iTemp);
int verificarRamalReturnI (RamalMain *pVetorDeRamais, int iTemp);
void imprimirLinha();
void erroNaoHaRamalRegistrado();



int iQtdReg = 0; //quantidade de registros
int iRegAtual = 0;


//#MAIN
int main () {
	
	int iOpcao = 0;
	string sOpcao = "n";
		
	RamalMain ramalOrigem;
	RamalMain vetorDeRamais[TAMANHO_VETOR];

	//inicializa o vetorDeRamais
	for(int i = 0; i < TAMANHO_VETOR; i++) {
		vetorDeRamais[i].iRamalNr = 0;
		vetorDeRamais[i].iRamalCategoria.iCdCategoria = 0;
		vetorDeRamais[i].sRamalSetor.iCdSetor = 0;
		vetorDeRamais[i].iRamalEdificio.iCdEdificio = 0;
		vetorDeRamais[i].iRamalSala = 0;
		vetorDeRamais[i].sRamalResp = "";
		vetorDeRamais[i].sRamalRespAteste = "";
	}
	//inicializa o ramalOrigem
		ramalOrigem.iRamalNr = 0;
		ramalOrigem.iRamalCategoria.iCdCategoria = 0;
		ramalOrigem.sRamalSetor.iCdSetor = 0;
		ramalOrigem.iRamalEdificio.iCdEdificio = 0;
		ramalOrigem.iRamalSala = 0;
		ramalOrigem.sRamalResp = "";
		ramalOrigem.sRamalRespAteste = "";

	do {
	
		mainCabecalho();
		cout << "  1. Registrar um novo ramal" << endl;
		cout << "  2. Imprimir todos os ramais registrados" << endl;
		cout << "  3. Pesquisar" << endl;
		cout << "\n";
		cout << "  9. Encerra SISGRAMMA" << endl;
		cout << "\n  Digite o numero da opcao desejada : ";
		cin >> iOpcao;
	
			switch (iOpcao) {
				//#1-INCLUIR: inclui um ramal
				case 1:
					do {
						//verifica se o vetor de ramais ja esta cheio
						if(iQtdReg == TAMANHO_VETOR){
							incluirRamalErroMemoriaCheia();
							break;
						}
						//inclui um novo ramal
						else {
							incluirRamal (&ramalOrigem, &vetorDeRamais[0]); //preciso passar a posicao 0 do vetorDeRamais
							vetorDeRamais[iQtdReg] = ramalOrigem; //salva os dados cadastrados no vetorDeRamais
							iQtdReg ++; //incrementea a quantidade de registros
											
							cout << "\n" << endl;
							imprimirLinha();
							cout << "Deseja cadastrar um novo ramal? [S/N] ";
							cin >> sOpcao;
							//sOpcao = toupper(sOpcao);
						}
					} while (sOpcao != "n");
					system("cls");
					break;

				//#3-IMPRIMIR: imprimi o ramal registrado
				case 2:
					imprimirRamalCabecalho();
						if (iQtdReg != 0) {
							//loop para imprimir todos os ramais registrados
							for (int i = 0; i < iQtdReg; i++) {
								imprimirRamal (&vetorDeRamais[i],i);
							}
							imprimirLinha();
							cout << "  Foram registrados " << iQtdReg << " ramais." << endl;
							cout << "\n" << endl;
							sleep(3);
						}
						else {
							erroNaoHaRamalRegistrado();
						}
					break;
				
				//#4-PESQUISAR
				case 3:
					int iPesqTipo = 0;
					int iPesqRamal = 0;
					int iPos = 0;
					
					do {
						pesquisarRamalCabecalho();
						if (iQtdReg == 0){
							pesquisarRamalCabecalho();
							erroNaoHaRamalRegistrado();
						}
						cout << "  1. Ramal" << endl;
						cout << "  2. Setor" << endl;
						cout << "  3. Edificio" << endl;
						cout << "  4. Responsavel pelo ramal" << endl;
						cout << "  5. Responsavel pelo ateste" << endl;
						cout << "\n";
						cout << "  9. Voltar" << endl;
						cout << "\n";
						cout << "  Selecione a forma de pesquisa que deseja utilizar: ";
						cin >> iPesqTipo;
						
						switch (iPesqTipo) {
							//1.RAMAL
							case 1:
								pesquisarRamalCabecalho();
								cout << "\n  Ramais registrados:" << endl;
								
								//lista todos os ramais registrados
								for(int i = 0; i < iQtdReg; i++){
									pesquisarRamal(&vetorDeRamais[i], iPesqTipo);	
								}
								cout << "\n";
								cout << "\n  Digite o ramal desejado: ";
								cin >> iPesqRamal;
								
								//pesquisa o ramal escolhido
								iPos = verificarRamalReturnI(&vetorDeRamais[0], iPesqRamal);
									imprimirRamalCabecalho();
									imprimirRamal(&vetorDeRamais[iPos], iPos);
									imprimirLinha();
									sleep(3);
								
							//2.SETOR	
							case 2:
								
							case 3:
								
							case 4:
								
							case 5:
								
							break;
						}
						
						
						
						
					} while (iPesqTipo != 9);
				break;	
			};
	} while (iOpcao != 9);
}

//#4-PESQUISAR: pesquisa uma informacao nos ramais registrados
void pesquisarRamal (RamalMain *pVetorDeRamais, int iPesqTipo) {
	switch (iPesqTipo) {
		case 1:
			cout << "\n  " << pVetorDeRamais->iRamalNr;
			break;
		case 2:
			cout << "\n  " << pVetorDeRamais->sRamalSetor.iCdSetor << " - " << pVetorDeRamais->sRamalSetor.sNmSetor;
			break;
		case 3:
			cout << "\n  " << pVetorDeRamais->iRamalEdificio.iCdEdificio << " - " << cout << "\n" << pVetorDeRamais->iRamalEdificio.sNmEdificio;
			break;
		case 4:
			cout << "\n  " << pVetorDeRamais->sRamalResp;
			break;
		case 5:
			cout << "\n  " << pVetorDeRamais->sRamalRespAteste;
			break;
		break;
	}
}


//#1-INCLUIR: inclui um ramal

void incluirRamal (RamalMain *pRamalOrigem, RamalMain *pVetorDeRamais) {
	
	int iTemp = 0; //variavel temporaria para verificar as validade do ramaL
	
    //valida o ramal digitado
	do {
		incluirRamalCabecalho();
		cout << "  Digite os dados do seu ramal\n" << endl;
		cout << "  Ramal..................: ";
	    cin >> iTemp;
	    
	    //verifica se o ramal esta dentro do intervalo de numeros permitido
	    if (iTemp < 1000 || iTemp >2999) {			
			incluirRamalErroForaIntervalo();
			continue;	    	
		}
		
		//verifica se o ramal ja foi registrado
		if (verificarRamal(pVetorDeRamais, iTemp)) {
			incluirRamalErroRamalExistente();
	    	iTemp = 1;
	    	continue;
		}
	} while (iTemp < 1000 || iTemp > 2999);
	
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

//#2-VERIFICA: checa se o ramal digitado ja existe na lista de ramais registrados
bool verificarRamal (RamalMain *pVetorDeRamais, int iTemp) {
	for (int i = 0; i < TAMANHO_VETOR; i++) {
		if(pVetorDeRamais[i].iRamalNr == iTemp){
			return true;
		}
	}
	return false;
}

//#2.1-VERIFICA: checa se o ramal digitado ja existe na lista de ramais registrados e retorna a posicao dele no vetor
int verificarRamalReturnI (RamalMain *pVetorDeRamais, int iTemp) {
	for (int i = 0; i < TAMANHO_VETOR; i++) {
		if(pVetorDeRamais[i].iRamalNr == iTemp){
			return i;
		}
	}
	return 9999;
}

//#3-IMPRIMIR: imprimi o ramal registrado
void imprimirRamal (RamalMain *pVetorDeRamais, int i) {

	cout << "  Ramal...................: " << pVetorDeRamais->iRamalNr << endl;
    cout << "  Categoria...............: " << pVetorDeRamais->iRamalCategoria.iCdCategoria << " " << pVetorDeRamais->iRamalCategoria.sNmCategoria << endl;
    cout << "  Setor...................: " << pVetorDeRamais->sRamalSetor.iCdSetor << " " << pVetorDeRamais->sRamalSetor.sNmSetor << endl;
    cout << "  Edificio................: " << pVetorDeRamais->iRamalEdificio.iCdEdificio << " " << pVetorDeRamais->iRamalEdificio.sNmEdificio << endl;
    cout << "  Sala....................: " << pVetorDeRamais->iRamalSala << endl;
    cout << "  Responsavel pelo ramal..: " << pVetorDeRamais->sRamalResp << endl;
    cout << "  Responsavel pelo ateste.: " << pVetorDeRamais->sRamalRespAteste << endl;
 	cout << "\n" << endl;
}

//#9-IMPRIMIR: imprime uma linha
void imprimirLinha() {
	cout << "------------------------------------------------------------" << endl;
}

void mainCabecalho() {
	system("cls");
	cout << "#main" << endl;
	cout << "\n";
	cout << "------------------------------------------------------------" << endl;
	cout << "  SISGRAMMA - Sistema de Gerenciamento de Ramais do MMA" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
}
void incluirRamalCabecalho() {
	system("cls");
	cout << "#registro" << endl;
	cout << "\n";
	cout << "------------------------------------------------------------" << endl;
	cout << "  1. REGISTRO DE RAMAL" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
}
void incluirRamalErroMemoriaCheia() {
	incluirRamalCabecalho();
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n  >> Memoria cheia! <<" <<endl;
    cout << "\n  Nao e possivel incluir mais um ramal!" <<endl;
    cout << "\n";
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n";
    sleep(3);
}
void incluirRamalErroForaIntervalo() {
	incluirRamalCabecalho();
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n  >> Ramal fora do intervalo permitido! <<" <<endl;
	cout << "\n";
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n";
	cout << "\nDigite um ramal entre 1000 e 2999\n" << endl;
	sleep(3);
}
void incluirRamalErroRamalExistente() {
	incluirRamalCabecalho();
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n  >> Este numero ja pertence a um ramal registrado! <<" <<endl;
	cout << "\n";
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n";
	cout << "\nDigite outro numero para o seu ramal entre 1000 e 2999\n" << endl;
	sleep(3);
}
void imprimirRamalCabecalho() {
	system("cls");
	cout << "#imprimir" << endl;
	cout << "\n";
	cout << "------------------------------------------------------------" << endl;
	cout << "  2. INFORMACOES GERAIS DO RAMAL" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
}
void pesquisarRamalCabecalho() {
	system("cls");
	cout << "#pesquisar" << endl;
	cout << "\n";
	cout << "------------------------------------------------------------" << endl;
	cout << "  3. PESQUISA DE RAMAIS" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n" << endl;
}
void erroNaoHaRamalRegistrado() {
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n  >> Nao ha ramais registrados! <<" <<endl;
    cout << "\n";
	cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
	cout << "\n";
    sleep(3);
}
