#include <iostream>
#include <cstdlib>

#include "library.h"


//boost
#ifdef USE_BOOST
	#include "librarySerialization.h"
#endif

using namespace std;


int main ()
{
	Library library("users.txt","books.txt");

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <loadLibrary>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	bool loadLibrary = utils::getYesNoCin("Deseja carregar a biblioteca? (S/N): ", "Introduza Sim (S) ou Nao (N)!!\n\n");


	if (loadLibrary) {
#ifdef USE_BOOST
		//**********************************************************  <boost>  *********************************************************
		bool loadSucesseful = true;
		do {
			cout << "Introduza o nome do ficheiro de onde quer carregar a biblioteca: ";
			string filename = utils::getlineCin();
			if (boost::serialization::loadLibrary(filename, library)) {
				loadSucesseful = true;
			} else {
				loadSucesseful = false;
				cout << "O nome do ficheiro que especificou não existe!!\n" << endl;
			}
		} while (!loadSucesseful);
		//**********************************************************  </boost>  *********************************************************
#else
		library.loadBooks();
		library.loadUsers();
#endif
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </loadLibrary>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	utils::clearConsoleScreen();

	int op = 0;

	do {
		//show menu

		cout << "**** Seja bem vindo a biblioteca PROGRAMACAO TP1 ****\n";
		cout << "#### Area de Administracao ####\n\n";
		cout << "1 - Registar Utilizador\n";
		cout << "2 - Adicionar livro\n";
		cout << "3 - Listar todos os utilizadores\n";
		cout << "4 - Listar todos os livros\n";
		cout << "5 - Pesquisar por utilizador\n";
		cout << "6 - Pesquisar por livro\n";
		cout << "7 - Mudar estado de um utilizador\n";
		cout << "\n#### Area de Utlizador ####\n\n";
		cout << "8 - Requisitar Livro\n";
		cout << "9 - Devolver Livro\n";

		cout<< "\n0 - Sair\n\n";


		/*
		 * não convem usar o que está feito em baixo, porque se o user meter caracteres o programa termina...
		 * visto que <op> fica a NULL por cin não conseguir ler um número...
		 */
		/*
		cout<< "\nOpcao: ";
		cin >> op; // read user option
		cin.ignore(1000, '\n');
		*/

		op = utils::getIntCin("Opção: ", "Introduza um número entre 0 e 9!!\n", 0, 10);

		switch(op) {
			case 0: {
				//sai fora do do while em baixo
				break;
			}

			case 1: {
				library.registerUserCLI();
				break;
			}

			case 2: {
				library.addBookCLI();
				break;
			}

			case 3: {
				library.listAllUsersCLI();
				break;
			}

			case 4: {
				library.listAllBooksCLI();
				break;
			}

			case 5: {
				library.searchUserCLI();
				break;
			}

			case 6: {
				library.searchBookCLI();
				break;
			}

			case 7: {
				library.changeUserStateCLI();
				break;
			}

			case 8: {
				library.requestBookCLI();
				break;
			}

			case 9: {
				library.returnBookCLI();
				break;
			}


			default: {
				cout << "\nIntroduza um número entre 0 e 9!!\n" << endl;
				utils::getUserInput();
			}

		}
	} while (op != 0);



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <saveLibrary>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	utils::clearConsoleScreen();
	bool saveLibrary = utils::getYesNoCin("Deseja guardar a biblioteca? (S/N): ", "Introduza Sim (S) ou Nao (N)!!\n\n");

	if (saveLibrary) {
#ifdef USE_BOOST
		//**********************************************************  <boost>  *********************************************************
		cout << "Introduza o nome do ficheiro para onde quer guardar a biblioteca: ";
		string filename = utils::getlineCin();
		boost::serialization::saveLibrary(filename, library);
		//**********************************************************  <boost>  *********************************************************
#else
		library.saveBooks();
		library.saveUsers();
#endif
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </saveLibrary>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	return 0;
}
