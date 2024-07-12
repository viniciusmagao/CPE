/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

-------------------------------------
lista 06 - questao 03
-------------------------------------
Em uma pesquisa medica, foram colhidas as medidas de altura (em metros) e peso (em 
quilogramas) de um grupo de pessoas e foram salvas, respectivamente, nos arquivos 
altura.txt e peso.txt. Cada pessoa e identificada por um codigo composto por numeros e 
letras.  Nos arquivos, e informado o codigo da pessoa em uma linha e sua medida na 
seguinte. Faça um programa em C++ que leia esses arquivos e imprima na tela qual pessoa 
tem maior altura e qual pessoa tem maior peso.

***************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //para usar setprecision()
#include <unistd.h> //para usar o sleep()

using namespace std;

int main() {
	
	//declaracao das variaveis
	ifstream arqAltura, arqPeso;
	string sCdPessoaTemp, sCdPessoaAltura, sCdPessoaPeso, str;
	int idLinha = 0;
	float fMaiorAltura = 0;
	float fMaiorPeso = 0;
	float fMedidaTemp = 0;
	
	cout << "\n--------------------------------" << endl;
		
	//abro o arquico altura.txt
	arqAltura.open ("altura.txt", ios::in);

	//verifico se o arquivo abriu corretamente		
	if(!arqAltura.is_open()) {
		cout << "\nNao foi possivel abrir o arquivo altura.txt!" << endl;
		sleep(2);
	} 
	else {
		cout << "\nArquivo altura.txt aberto!" << endl;
		sleep(2);
		
		//inicia a leitura do arquivo altura.txt
		while (getline(arqAltura, str)) {
		//para identificar qual linha esta sendo lida
		idLinha ++;
		idLinha = (idLinha%2);
		
			switch (idLinha) {
				case 0: //medida da pessoa
					fMedidaTemp = stof(str);
					//se a medida anterior foi maior que maior medida, salvo o codigo da pessoa e sua medida
					if(fMedidaTemp > fMaiorAltura) {
						sCdPessoaAltura = sCdPessoaTemp;
						fMaiorAltura = fMedidaTemp;
					}
					break;
					
				case 1:	//codigo da pessoa
					sCdPessoaTemp = str;
					break;
			}
		}
	}
	//fecha o arquivo altura.txt
	arqAltura.close();
	
	//zera a variavel temporaria
	fMedidaTemp = 0;
	
	//abro o arquivo peso.txt
	arqPeso.open ("peso.txt", ios::in);
	
	//verifico se o arquivo abriu corretamente
	if(!arqPeso.is_open()) {
		cout << "\nNao foi possivel abrir o arquivo peso.txt!" << endl;
		sleep(2);
	} 
	else {
		cout << "\nArquivo peso.txt aberto!" << endl;
		sleep(2);
		
		//inicia a leitura do arquivo peso.txt
		while (getline(arqPeso, str)) {
		//para identificar qual linha esta sendo lida
		idLinha ++;
		idLinha = (idLinha%2);
		
			switch (idLinha) {
				case 0: //medida da pessoa
					fMedidaTemp = stof(str);
					//se a medida anterior foi maior que fMaiorMedida, salvo o codigo da pessoa e sua medida
					if(fMedidaTemp > fMaiorPeso) {
						sCdPessoaPeso = sCdPessoaTemp;
						fMaiorPeso = fMedidaTemp;
					}
					break;
					
				case 1:	//codigo da pessoa
					sCdPessoaTemp = str;
					break;
			}
		}
	}
	//fecha o arquivo peso.txt
	arqPeso.close();
	
	//imprimi o resultado na tela
	system("cls");
	cout << "\n--------------------------------" << endl;
	cout << "\n";
	cout << fixed << setprecision(2);
	cout << "MAIOR ALTURA" << endl;
	cout << "Pessoa: " << sCdPessoaAltura << endl;
	cout << "Altura: " << fMaiorAltura << " m."<< endl;
	cout << "\n";
	cout << "MAIOR PESO" << endl;
	cout << "Pessoa: " << sCdPessoaPeso << endl;
	cout << "Peso: " << fMaiorPeso << endl;	
	cout << "\n--------------------------------" << endl;
	return 0;
}
