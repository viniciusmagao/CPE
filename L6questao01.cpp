/***************************************************

DISCIPLINA: COMPUTACAO PARA ENGENHARIA
PROFESSOR: WESIN ALVES
ALUNO: VINICIUS MAGAO DE OLIVEIRA
MATRICULA: 241037687

-------------------------------------
lista 06 - questao 01
-------------------------------------
Faça um programa em C++ que realize a soma dos vetores contidos no arquivo 
vetores.txt. Considere que em cada linha estao escritas todas as posiçoes de um mesmo vetor. O 
resultado da soma deve ser salvo em um novo arquivo chamado soma.txt Seu programa 
deve funcionar independentemente da quantidade de vetores  e de seus tamanhos.

***************************************************/

#include<iostream> //biblioteca padrao do C++
#include<string> //biblioteva padrao para string
#include<fstream> //biblioteca para ler e escrever em arquivos

using namespace std;


int main () {

	string str = ""; 
	string strNum = "";
	int iNum = 0;
	
	//abre o arquivo vetores.txt no modo leitura
	ifstream arqRead;
    arqRead.open("vetores.txt", ios::in);
	//abre o arquivo soma.txt no modo escrita
	ofstream arqWrt;
    arqWrt.open("soma.txt", ios::out);
	
	//verifica se o arquivo foi aberto com sucesso
	if(arqRead.is_open()){
        cout << "\n--------------------------------------------------" << endl;
		cout << "\n>> Arquivo aberto com sucesso! <<" << endl;

        //comeca a leitura do arquivo
        while(getline(arqRead, str)) {
            
            //faz o loop nessa linha lida ate o final da string str
            for(int i = 0; i < str.size(); i++){
        
                if(str[i] == ' ') {
                    //quando tem um espaco entre um numero e outro, iNum recebe a soma dele mesmo mais o proximo numero que foi 'acumulado' em strNum
                    iNum += stoi(strNum);
                    strNum = "";
                }
                else {
                    //acumula o numero em strNum, caso o numero tenha mais de um algarismo
                    strNum += str[i];
                }
            }
            iNum += stoi(strNum);
        //grava no arquivo soma.txt o resultado da soma do vetor da linha
        arqWrt << "\nA soma do vetor [" << str << "] e: " << iNum << "\n";
        cout << "\n--------------------------------------------------" << endl;
        cout << "\nA soma do vetor [" << str << "] e: " << iNum << "\n";
        
        strNum = "";
        iNum = 0;
        }
        //avisa ao usuario que o resultado foi salvo no arquivo soma.txt
        cout << "\n--------------------------------------------------" << endl;
        cout << "\n# O resultado foi salvo no arquivo soma.txt" << endl;
    } 
    else {
		cout << "\n--------------------------------------------------" << endl;
        cout << "\n>> Arquivo nao abriu... :( <<" << endl;
        cout << "\nVerifique se o arquivo 'vetores.txt' exite no diretorio." << endl;
	}
    //fecha os dois arquivos abertos
	arqRead.close();
	arqWrt.close();
}
