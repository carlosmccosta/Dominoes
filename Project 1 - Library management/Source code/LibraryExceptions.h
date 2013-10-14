/**\file LibraryExceptions.h
 * \brief Classe que contém a informação associada a todas as excepcoes implementadas.
 *
 * PROJECTO: Projecto 1 - Programação - 10-11 - MIEIC\n
 * FICHEIRO: LibraryExceptions.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a todas as excepcoes implementadas. \n
 *
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 */


#ifndef LIBRARYEXCEPTIONS_H_
#define LIBRARYEXCEPTIONS_H_


#include <iostream>
#include <string>
#include <exception>

using std::ostream;
using std::string;
using std::exception;



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <LibraryExceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * \brief Superclasse de tratamento de excepções.
 * \details Subclasse de std::exception para no programa ser possível fazer catch das excepções da std e das excepções criadas para o programa.
 */
class LibraryExceptions: public exception {
protected:
	const char* errorMessage;

public:
	explicit LibraryExceptions(const char* pStr) : errorMessage(pStr) {}

	/**
	 * Destrutor que garante que não irá lançar uma excepção,
	 * porque a classe std::exception, obriga a que as subclasses que fazem override às suas funções, não podem lançar excepções.
	 * Isso inclui os destrutores e a função what().
	 * Caso não fosse feito o compilador iria dar o erro "looser throw specifier...".
	 */
	virtual ~LibraryExceptions() throw() {}
	const char* what() const throw() { return errorMessage; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </LibraryExceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ElementAlreadyExistsException: public LibraryExceptions {
private:
	T elementoRepetido;
public:
	explicit ElementAlreadyExistsException(T elemento_repetido, const char* pStr = "Elemento já existe!") :
		LibraryExceptions(pStr), elementoRepetido(elemento_repetido) {}
	virtual ~ElementAlreadyExistsException() throw() {}

	T getElementoRepetido() const { return elementoRepetido; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ElementDoesntExistsException: public LibraryExceptions {
private:
	T elementoInexistente;
public:
	explicit ElementDoesntExistsException(T elementoInexistente, const char* pStr = "Elemento não existe!") :
		LibraryExceptions(pStr), elementoInexistente(elementoInexistente) {}
	virtual ~ElementDoesntExistsException() throw() {}

	T getElementoInexistente() const { return elementoInexistente; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um vector se encontra vazio.
class EmptyContainerException: public LibraryExceptions {
public:
	explicit EmptyContainerException(const char* pStr = "O container que está a tentar aceder está vazio!") : LibraryExceptions(pStr) {}
	virtual ~EmptyContainerException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que um dado ficheiro que de dados está corrupto ou num formato desconhecido.
class CorruptedFileException: public LibraryExceptions {
private:
	char* filename;

public:
	explicit CorruptedFileException(const char* pStr = "Ficheiro com os dados corrompido!") : LibraryExceptions(pStr) {}
	string getFilename() const { return filename; }
	virtual ~CorruptedFileException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que não foi possível abrir o ficheiro especificado.
class FileDoesntExistException: public LibraryExceptions {
private:
	char* filename;

public:
	explicit FileDoesntExistException(const char* pStr = "Não foi possível abrir o ficheiro!") : LibraryExceptions(pStr) {}
	virtual ~FileDoesntExistException() throw() {}
	string getFilename() const { return filename; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#endif /* LIBRARYEXCEPTIONS_H_ */
