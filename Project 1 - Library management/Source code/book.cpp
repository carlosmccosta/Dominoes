/**\file book.cpp
 * \brief Ficheiro com a implementação da classe book.
 *
 * PROJECTO: Projecto 1 - Programação - 10-11 - MIEIC\n
 * FICHEIRO: book.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe book que representa um dado livro numa dada biblioteca. \n
 *
 * AUTOR:
 * - Carlos Miguel Correia da Costa
 */

#include "book.h"



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <init-variables>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Inicialização do static data member que conta o número de livros que foram criados até um dado momento
 * de forma a poder atribuir um id único a cada um.
 */
IdentNum Book::numBooks = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </init-variables>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Constructor por default que cria um livro com um titulo da forma <"Unknown title of book with id: " + ID>,
 * com o autor da forma <"Unknown author of book with id: " + ID> e com 0 exemplares
 */
Book::Book() : ID(++numBooks), title("Unknown title of book"), author("Unknown author of book"), numAvailable(0) {}

/**
 * Constructor de Book que cria um novo livro com o titulo, autor e número de exemplares que é forneciido
 * @param bookTitle Título a atribuir ao livro
 * @param bookAuthor Autor a atribuir ai livro
 * @param bookQuantity Número de exemplares que este livro tem
 */
Book::Book(string bookTitle, string bookAuthor, unsigned int bookQuantity) : ID(++numBooks), title(bookTitle), author(bookAuthor), numAvailable(bookQuantity) {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Método que retorna o número de livros que foram criados até agora
 * @return Numero de livros criados até ao momento
 */
IdentNum Book::getNumBooks() {
	return Book::numBooks;
}

/**
 * Método que devolve o ID do livro
 * @return Retorna o ID do livro
 */
IdentNum Book::getID() const {
	return ID;
}

/**
 * Método que devolve o titulo do livro
 * @return Retorna o título do livro
 */
string Book::getTitle() const {
	return title;
}

/**
 * Método que devolve o(s) autor(es) do livro
 * @return Retorna o(s) autor(es) do livro
 */
string Book::getAuthor() const {
	return author;
}

/**
 * Método que devolve o número de exemplares disponíveis do livro
 * @return Retorna o nº de exemplares.
 */
unsigned int Book::getNumAvailable() const {
	return numAvailable;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que altera o ID do livro para o bookID dado
 * @param bookID ID a atribuir ao livro
 */
void Book::setID(IdentNum bookID) {
	ID = bookID;
}

/**
 * Método que altera o título do livro para o bookTitle dado
 * @param bookTitle Título a atribuir ao livro
 */
void Book::setTitle(string bookTitle) {
	title = bookTitle;
}

/**
 * Método que altera o(s) autor(es) do livro para o bookAuthor dado
 * @param bookAuthor Autor(es) a atribuir ao livro
 */
void Book::setAuthor(string bookAuthor) {
	author = bookAuthor;
}

/**
 * Método que altera o número de exemplares do livro para o numBooks dado
 * Só altera se numBooks >= 0
 * @param numBooks Número de exemplares a atribuir ao livro
 */
void Book::setNumAvailable(unsigned int numBooks) {
	if (numBooks >= 0) {
		numAvailable = numBooks;
	}
}

/**
 * Método que modifica a variável estática numBooks para o "num" dado desde que "num" não seja inferior ao valor de numBooks,
 * visto que não havendo eliminação de livros, caso numBooks fosse alterado para um número inferior haveria livros com o mesmo id,
 * o que deve ser evitado
 * @param num Número de livros que foram criados até ao momento na bilioteca (tem que ser > que o numBooks actual)
 */
void Book::setNumBooks(IdentNum num) {
	if (num > numBooks) {
		numBooks = num;
	}
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <bookManagement>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que acrescenta bookQuantity aos exemplares do livro
 * @param bookQuantity Número de exemplares a acrescentar aos actuais deste livro
 */
void Book::addBooks(int bookQuantity) {
	numAvailable += bookQuantity;
}

/**
 * Métode que trata do emprestimo de um livro
 * Equivale a diminuir o número de exemplares em uma unidade
 * (nunca passa abaixo de 0)
 */
void Book::loanBook() {
	if (numAvailable > 0) {
		--numAvailable;
	}
}

/**
 * Métode que trata do retorno de um livro
 * Equivale a aumentar o número de exemplares em uma unidade
 */
void Book::returnBook() {
	++numAvailable;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </bookManagement>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
