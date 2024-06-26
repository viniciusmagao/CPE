/*  
Trabalho de Computacao para Engenharia
Projeto Escolhido - Bingo

Autores: 
1. Arthur Ramos
2. Mateus
3. Pedro Henrique Dias Avelar
4. Vinicius Magao de Oliveira

Data: 25/06/2024
*/


#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
//using namespace std;


const int MENOR_PEDRA = 1;
const int MAIOR_PEDRA = 60;
const int NUM_PEDRAS = MAIOR_PEDRA - MENOR_PEDRA + 1;

struct jogador_bingo {
    int cartela[5][5];
    std::string nome_jogador;
    bool ganhou;
};

//#1 PREENCHE: cartela
void preenche_cartela (jogador_bingo& jogador);
//#2 SORTEIA: gera um numero aleatorio
int sorteia_numero ();
//#3 VERIFICA: numero na cartela
bool checa_numero_cartela_repetido (jogador_bingo& jogador,  int numero);
//#3 IMPRIMI: cartela
void imprime_cartela (jogador_bingo &jogador, int n_sorteados[], int n_pedras);
//#5 VERIFICA: numero sorteado
bool checa_numero_sorteado_repetido (int n_sorteados[], int n_pedras,  int numero);
//#6 IMPRIMI: imprimi os numeros sorteados
void imprime_numeros_sorteados (int n_sorteados[], int n_pedras);
//#7 VERIFICA: verifica linha da cartela
void avalia_linha (jogador_bingo& jogador, int linha, int n_pedras, int n_sorteados[]);
//#8 VERIFICA: verifica coluna da cartela
void avalia_coluna (jogador_bingo& jogador, int coluna, int n_pedras, int n_sorteados[]);

int numeros_sorteados[NUM_PEDRAS];
int numero_sorteado;
bool numero_sorteado_valido = false;


int main () {

    //declara jogadores
    jogador_bingo a;
    jogador_bingo b;
    jogador_bingo c;
    jogador_bingo d;
    
    //abertura do jogo
    std::cout << "\n>> ---------------------------------------------- <<\n";
    std::cout <<"\nBem Vindo(a) ao Bingo da Computacao para Engenharia!\n";
    std::cout << "\n>> ---------------------------------------------- <<\n" << std::endl;
	std::cout <<"Para comecar, precisamos que cada jogador informe seus dados e preencha sua cartela." << std::endl;
    
    //identifica os jogadores
	std::cout << "\nPreencha os dados do primeiro jogador..." << std::endl;
    preenche_cartela(a);
    std::cout << "\nPreencha os dados do segundo jogador..." << std::endl;
    preenche_cartela(b);
    std::cout << "\nPreencha os dados do terceiro jogador..." << std::endl;
    preenche_cartela(c);
    std::cout << "\nPreencha os dados do quarto jogador..." << std::endl;
    preenche_cartela(d);
    
    //imprime as cartelas de cada jogador
    imprime_cartela(a, numeros_sorteados, 1);
    imprime_cartela(b, numeros_sorteados, 1);
    imprime_cartela(c, numeros_sorteados, 1);
    imprime_cartela(d, numeros_sorteados, 1);
    
    //Para cada pedra sorteada, serao feitas iteracoes para avaliar se houve vencedor
    for (int i = 0; i < NUM_PEDRAS; i++){
        std::cout << "\nComecando o sorteio da " << i+1 << "a pedra!" << std::endl; 
        numero_sorteado_valido = false;
        
        //loop para garantir que o numero sorteado nao seja repetido
        while (numero_sorteado_valido == false){
        	//#2 SORTEIA: sorteia um numero aleatorio 
            numero_sorteado = sorteia_numero ();
            if (checa_numero_sorteado_repetido(numeros_sorteados, i, numero_sorteado) == false) {
                std::cout << "\nO " << i+1 << "o numero sorteado eh: " << numero_sorteado << "!!!" << std::endl;
                numero_sorteado_valido = true; 
                numeros_sorteados[i] = numero_sorteado;
                std::cout << "--------------------------------\n";
				std::cout << "\nNumeros sorteados ate o momento:\n" << std::endl;
                //#6 IMPRIMI: imprimi os numeros sorteados
                imprime_numeros_sorteados(numeros_sorteados, i+1);
                std::cout << "--------------------------------\n";
            };
        };
    
	    //cinco iteracoes para avaliar as 5 linhas / 5 colunas das cartelas dos 4 jogadores;  
	    for (int j = 0; j < 5; j ++){
	        avalia_linha (a,j,i,numeros_sorteados);
	        avalia_coluna (a,j,i,numeros_sorteados);
	        avalia_linha (b,j,i,numeros_sorteados);
	        avalia_coluna (b,j,i,numeros_sorteados);
	        avalia_linha (c,j,i,numeros_sorteados);
	        avalia_coluna (c,j,i,numeros_sorteados);
	        avalia_linha (d,j,i,numeros_sorteados);
	        avalia_coluna (d,j,i,numeros_sorteados);
    	};
	
	    //verifica se algum jogador ganhou
	    if (a.ganhou == true || b.ganhou == true || c.ganhou == true || d.ganhou == true){
	        if (a.ganhou == true){
	            std::cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << a.nome_jogador << " <<<" << std::endl;
	            imprime_cartela(a, numeros_sorteados, i);
	        };
	        if (b.ganhou == true){
	            std::cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << b.nome_jogador << " <<<" << std::endl;
	            imprime_cartela(b, numeros_sorteados, i);
	        };
	        if (c.ganhou == true){
	            std::cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << c.nome_jogador << " <<<" << std::endl;
	            imprime_cartela(c, numeros_sorteados, i);
	        };
	        if (d.ganhou == true){
	            std::cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << d.nome_jogador << " <<<" << std::endl;
	            imprime_cartela(d, numeros_sorteados, i);
	        };
	        return 0;
		};
	};
	return 0;
}

//#1 PREENCHE: funcao para preencher o nome do jogador e os numeros da cartela
void preenche_cartela (jogador_bingo& jogador){
    bool numero_valido = false;
    int numero_digitado = 0;
    
    //inicializacao da cartela
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            jogador.cartela[i][j] = 0;
        };
    };

    //nome do jogador
    std::cout << "Digite o seu nome: ";
    std::cin >> jogador.nome_jogador;
    jogador.ganhou = false;
        
    //preenchimento da cartela AUTOMATICO
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            numero_valido = false;
            while (numero_valido == false){
				//#2 SORTEIA: sorteia um numero aleatorio 
				numero_digitado = sorteia_numero();
				//#3 VERIFICA: verifica se um numero existe na cartela
                if (checa_numero_cartela_repetido (jogador, numero_digitado) == true || numero_digitado > MAIOR_PEDRA || numero_digitado < MENOR_PEDRA){
					//nao faz nada, apenas volta pro inicio do while
				}
                else {
                    jogador.cartela[i][j] = numero_digitado;
                    numero_valido = true;
                };
            };
        };
    };
    
    /*
    //preenchimento da cartela MANUAL
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            numero_valido = false;
            while (numero_valido == false){
				std::cout << "Digite o numero da posicao [" << i << "] [" << j << "]: ";
                std::cin >> numero_digitado;
                //#3 VERIFICA: verifica se um numero existe na cartela
                if (checa_numero_cartela_repetido (jogador, numero_digitado) == true){
                    std::cout << "\n>> ATENCAO! <<\n" << std::endl;
					std::cout << "Numero repetido!\nDigite outro por favor...\n" << std::endl;
                    std::cout << "Sua cartela ate o momento:" << std::endl;
                    imprime_cartela(jogador, numeros_sorteados, 1);
                } else if (numero_digitado > MAIOR_PEDRA || numero_digitado < MENOR_PEDRA) {
                    std::cout << "\n>> ATENCAO! <<\n" << std::endl;
                    std::cout << "Numero fora do aceitado! Precisa estar entre " << MENOR_PEDRA << " e " << MAIOR_PEDRA << ".\nDigite outro por favor...\n" << std::endl;
                } else {
                    jogador.cartela[i][j] = numero_digitado;
                    numero_valido = true;
                };
            }
        }
    }
	*/
}

//#2 SORTEIA: gera um numero aleatorio
int sorteia_numero () {
	return MENOR_PEDRA + (rand ()% NUM_PEDRAS);
}

//#3 VERIFICA: verifica se um determinado numero existe na cartela; se sim retorna true, se nao retorna false
bool checa_numero_cartela_repetido (jogador_bingo& jogador, int numero){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (jogador.cartela[i][j] == numero){
                return true;
            };
        };
    };
    return false;
}

//#4 IMPRIMI: imprime a cartela do jogador
void imprime_cartela (jogador_bingo& jogador, int n_sorteados[], int n_pedras){
    std::cout <<"\nCartela gerada para: " << jogador.nome_jogador << "\n" << std::endl;
	for (int i = 0; i < 5; i++){
        std::cout << "|";
        for (int j = 0; j < 5; j++){
            if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[i][j])==true){
            std::cout << "*";
            	//acrescenta um 0 a esquerda para numeros menores que 10
            	if(jogador.cartela[i][j] < 10){
        		std::cout << "0" << jogador.cartela[i][j] << "|";
				} else {
				std::cout << jogador.cartela[i][j] << "|";	
				}
			} 
			//acrescenta um 0 a esquerda para numeros menores que 10
			else if(jogador.cartela[i][j] < 10){
        		std::cout << " 0" << jogador.cartela[i][j] << "|";
			} else {
				std::cout << " " << jogador.cartela[i][j] << "|";	
			}
        };
        std::cout << std::endl;
    };
}

//#5 VERIFICA: verifica se o numero ja foi sorteado; se sim retorna true, se nao retorna false
bool checa_numero_sorteado_repetido (int n_sorteados[], int n_pedras, int numero){
    for (int i = 0; i < n_pedras; i++){
        if (n_sorteados[i] == numero){
            return true;
        };
    };
    return false;
}

//#6 IMPRIMI: imprimi os numeros sorteados
void imprime_numeros_sorteados (int n_sorteados[], int n_pedras){
    int count = 0;
	for (int i = 0; i < n_pedras; i++){
		//quebra a lista de numeros sorteados, mostra 10 numeros por linha
		if(count == 10){
    		std::cout << "\n";
    		count = 0;
		} 
		//acrescenta um 0 a esquerda para numeros menores que 10
		else if(n_sorteados[i] < 10){
        	std::cout << "0" << n_sorteados[i] << " ";
        	count++;
			} 
		else {
			std::cout << n_sorteados[i] << " ";
			count++;
		}
    };
    std::cout << std::endl;
}

//#7 VERIFICA: verifica se uma determinada LINHA da cartela possui 5 acertos
void avalia_linha (jogador_bingo& jogador, int linha, int n_pedras, int n_sorteados[]){
    int acertos = 0;
    for (int i = 0; i < 5; i++){
        if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[linha][i]) == true){
            acertos++;
        }; 
    };
    if (acertos == 5) {
        jogador.ganhou = true;
    };
}

//#8 VERIFICA: verifica se uma determinada COLUNA da cartela possui 5 acertos
void avalia_coluna (jogador_bingo& jogador, int coluna, int n_pedras, int n_sorteados[]){
    int acertos = 0;
    for (int i = 0; i < 5; i++){
        if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[i][coluna]) == true){
            acertos++;
        }; 
    };
    if (acertos == 5) {
        jogador.ganhou = true;
    };
}
