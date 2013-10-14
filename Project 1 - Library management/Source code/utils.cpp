/**\file utils.cpp
 * \brief Ficheiro com a implementação de funções úteis para a interface com o utilizador.
 *
 * PROJECTO: Projecto 1 - Programação - 10-11 - MIEIC\n
 * FICHEIRO: utils.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação de funções úteis para a interface com o utilizador. \n
 *
 * AUTOR:
 * - Carlos Miguel Correia da Costa
 */



#include "utils.h"


//Limpa as flags do cin e fica à espera de um input para prosseguir.
void utils::getUserInput() {
	cout << "Prima ENTER para continuar..." << endl;

	//Limpa as flags do cin
	cin.clear();

	cin.sync(); // http://www.cplusplus.com/forum/beginner/1988/page5.html

	//String temporária para guardar os dados lidos
	string temp;

	//Obtenção de uma linha de input para continuar
	getline(cin, temp);

	cin.clear();
	cin.sync();
}

string utils::getlineCin() {
	cin.clear();
	cin.sync();

	string input;
	getline(cin, input);

	cin.clear();
	cin.sync();

	return input;
}


void utils::clearConsoleScreen() {
	for (size_t i = 0; i < 80; ++i) {
		cout << "\n";
	}

	cout << endl;
}

int utils::getIntCin(const char* message, const char* errorMessage, int min, int size) {

	int numero;
	do {
		cout << message;

		/*
		 * Enquanto cin devolver um apontador NULL (e como tal no teste do if dar true (por estar negado)),
		 * devido ao facto de estar a ler dados que não são números, (ex: caracteres...)
		 * informa ao utilizador que tem que introduzir um nº e pede para introduzir os dados novamente.
		 */
		if (!(cin >> numero)) {

			//Limpa as flags do cin
			cin.clear();

			//Extrai e ignora todos os caracteres que estavam no buffer de cin, visto que ao tentar-se introduzir
			//caracteres num int (por ex), o cin entra em estado de erro e não remove os caracteres que leu do buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage << endl;
		} else {

			//Testa se os números introduzidos estão dentro do intervalo pedido
			if (numero >= min && numero < size)
				break; //Se estiverem sai-se do loop
			else
				cout << errorMessage << endl; //Senão informasse o utilizador e pede-se novamente o nº
		}

	} while (true);

	cin.clear();
	cin.sync();

	return numero;
}


bool utils::getYesNoCin(const char* message, const char* message_erro)
{
	bool continuar = false;

	//Pergunta ao utilizador se quer continuar (S/N)
	bool opcao_incorrecta;
	string opcao;

	do {
		cout << message;

		opcao = getlineCin();
		if ((opcao == "S") || (opcao == "s")) {
			continuar = true;
			opcao_incorrecta = false;
		}
		else if ((opcao == "N") || (opcao == "n")) {
			continuar = false;
			opcao_incorrecta = false;
		}
		else {
			cout << message_erro;
			opcao_incorrecta = true;
		}
	} while (opcao_incorrecta);

	cin.clear();
	cin.sync();

	return continuar;
}

string utils::toUpper(string str) {
	for (string::size_type i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}

	return str;
}


string utils::toLower(string str) {
	for (string::size_type i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}


