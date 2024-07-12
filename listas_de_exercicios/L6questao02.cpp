//incluir cabecalho

#include<iostream>
/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

-------------------------------------
lista 06 - questao 02
-------------------------------------

***************************************************/

#include<unistd.h> //para usar o sleep()
#include<string>
#include<fstream> //para manipular arquivos

using namespace std;


int main () {
	
	string sArqNm, sTexto;
	char cLetra;
	int count = 0;
	
	cout << "\n------------------------------------------------------------" << endl;
	cout << "\n Digite o nome do arquivo .txt que deseja abrir.\nDigite apenas o nome, sem a extensao '.txt': " << endl;
	cin >> sArqNm;
	cout << "\n Digite a letra que deseja pesquisar no arquivo: ";
	cin >> cLetra;
	
	//sArqNm = "mochileiro";
	
	ifstream arqRead;
	arqRead.open(sArqNm + ".txt", ios::in);
	
	if(arqRead.is_open()) {
		system("cls");
		cout << "\n------------------------------------------------------------" << endl;
		cout << "\n >> Arquivo '" << sArqNm <<"' aberto com sucesso! <<" << endl;
		
		while (getline(arqRead, sTexto)) {
			for(int i = 0; i < sTexto.size(); i++) {
				if(sTexto[i] == cLetra)	{
					count ++;
				}
			}
		}
		cout << "\n";
		cout << "\n";
		cout << "\n A letra '" << cLetra << "' aparece " << count << " vezes no texto-arquivo '" << sArqNm << "'." << endl;
		cout << "\n------------------------------------------------------------" << endl;	
	}
	else {cout << "\n >> Nao foi possivel abrir o arquvo '" << sArqNm << "'! <<" << endl;}
	
	arqRead.close();
}
