/**\file user.cpp
 * \brief Ficheiro com a implementação da classe user.
 *
 * PROJECTO: Projecto 1 - Programação - 10-11 - MIEIC\n
 * FICHEIRO: user.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe user que representa um dado utilizador de uma biblioteca. \n
 *
 * AUTOR:
 * - Carlos Miguel Correia da Costa
 */

#include "user.h"




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <init-variables>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Inicialização do static data member que conta o número de users que foram criados até um dado momento
 * de forma a poder atribuir um id único a cada um.
 */
IdentNum User::numUsers = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </init-variables>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Constructor por default de user
 * Inicializa o name no formato : "Unnamed user with id: " + ID
 * e coloca o user activo na biblioteca
 */
User::User() : ID(++numUsers), name("Unnamed user with id: "), active(true) {}

/**
 * Constructor de User que inicializa o nome a "name"
 * @param name Nome a atribuir ao User que vai ser criado
 */
User::User(string nome) : ID(++numUsers), name(nome), active(true) {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Método que retorna o número de users que foram criados até agora
 */
IdentNum User::getNumUsers() {
	return User::numUsers;
}

/**
 * Método que devolve o ID do user.
 * @return Retorna ID do user
 */
IdentNum User::getID() const {
	return ID;
}

/**
 * Método que devolve o nome do user
 * @return Retorna o nome do user
 */
string User::getName() const {
	return name;
}

/**
 * Método que permite determinar se um user está activo na biblioteca
 * P.S. Só users activos podem requesitar livros
 * @return Retorna true caso o user esteja activo
 */
bool User::isActive() const {
	return active;
}

/**
 * Método que devolve o vector de IdentNum que contem os ids dos livros que o user requesitou à biblioteca
 * @return vector<IdentNum> com os ids dos livros requesitados pelo user.
 */
vector<IdentNum> User::getRequestedBooks() const {
	return requestedBooks;
}

/**
 * Método que permite saber se o user requesitou livros
 * @return true caso o user tenha requesitado livros à bilioteca
 */
bool User::hasBooksRequested() const {
	return !requestedBooks.empty();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Método que altera o ID do user para o userID fornecido
 * @param userID ID a ser atribuido ao user
 */
void User::setID(IdentNum userID) {
	ID = userID;
}

/**
 * Método que altera o nome do user para o userName dado
 * @param userName nome a atribuir ao user
 */
void User::setName(string userName) {
	name = userName;
}

/**
 * Método que altera o estado do user perante a biblioteca de acordo com o status que é dado
 * @param status true caso se queira que o user possa requesitar livros na biblioteca
 */
void User::setActive(bool status) {
	active = status;
}

/**
 * Método que altera o vector que contem os ids dos livros que o user requesitou à biblioteca pelo booksRequestedByUser
 * @param booksRequestedByUser vector que irá substituir o vector<IdentNum> actual do user
 */
void User::setRequestedBooks(const vector<IdentNum> & booksRequestedByUser) {
	requestedBooks = booksRequestedByUser;
}

/**
 * Método que modifica a variável estática numUsers da class User para o valor num
 * P.S. Caso num seja menor que numUsers, não altera numUsers, visto que não havendo eliminação de users,
 * caso numUsers fosse colocado para um valor inferior ao actual, iria haver users com ids iguais, o que não deve ser permitido
 * @param num Número de users que existem registados (tem que ser maior que o número actual)
 */
void User::setNumUsers(IdentNum num) {
	if (num > numUsers) {
		numUsers = num;
	}
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <bookManagement>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que acrescenta o bookID ao vector<IdentNum> do user caso este esteja activo
 * P.S. Equivale a uma requisição de um livro por parte do user à bilbioteca
 * @param bookID id do livro a acrescentar
 */
void User::borrowBook(IdentNum bookID) {
	if (active) {
		requestedBooks.push_back(bookID);
	}
}


/**
 * Método que retira o livro com o bookID do vector<IdentNum> que contem os livros requisitados pelo user
 * Caso o utilizador não tenha um livro com esse id lança uma excepção (ElementDoesntExistsException<IdentNum>)
 * P.S. Equivale ao user retornar o livro à bilioteca
 * P.S. 2 - Só remove esse id se o user tiver requesitado o livro
 * @param bookID
 */
void User::returnBook(IdentNum bookID) throw(ElementDoesntExistsException<IdentNum>) {
	for (vector<IdentNum>::iterator bookIter = requestedBooks.begin(); bookIter != requestedBooks.end(); ++bookIter) {
		if (bookID == (*bookIter)) {
			//remove id do livro
			requestedBooks.erase(bookIter);
			//o método apenas deve retornar um livro, por isso não vale a pena continuar a pesquisar o vector se já se encontrou o id que se ia remover
			return;
		}
	}

	stringstream message;
	message << "O livro com o ID" << bookID << "não existe!!!";
	//caso não encontre um user com o id especificado lança uma excepção
	throw ElementDoesntExistsException<IdentNum>(bookID, message.str().c_str());
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </bookManagement>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
