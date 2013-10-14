#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

/**\file Exceptions.h
 * \brief Ficheiro com as excepções usadas no programa.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <iostream>
#include <string>
#include <exception>

using std::ostream;
using std::string;
using std::exception;



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <Exceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * \brief Superclasse de tratamento de excepções.
 * \details Subclasse de std::exception para no programa ser possível fazer catch das excepções da std e das excepções criadas para o programa.
 */
class Exceptions: public exception {
protected:
	const char* errorMessage;

public:
	explicit Exceptions(const char* pStr) : errorMessage(pStr) {}

	/**
	 * Destrutor que garante que não irá lançar uma excepção,
	 * porque a classe std::exception, obriga a que as subclasses que fazem override às suas funções, não podem lançar excepções.
	 * Isso inclui os destrutores e a função what().
	 * Caso não fosse feito o compilador iria dar o erro "looser throw specifier...".
	 */
	virtual ~Exceptions() throw() {}
	const char* what() const throw() { return errorMessage; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </Exceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que não foi possível abrir o ficheiro especificado.
class FileDoesntExistException: public Exceptions {
private:
	char* filename;

public:
	explicit FileDoesntExistException(const char* pStr = "\nO nome do ficheiro que introduziu nao existe!\n") : Exceptions(pStr) {}
	virtual ~FileDoesntExistException() throw() {}
	string getFilename() const { return filename; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <FileAlreadyExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza um dado ficheiro já existe com aquele nome.
class FileAlreadyExistException: public Exceptions {
private:
	char* filename;

public:
	explicit FileAlreadyExistException(const char* pStr = "\nO nome do ficheiro que introduziu ja existe!\n") : Exceptions(pStr) {}
	virtual ~FileAlreadyExistException() throw() {}
	string getFilename() const { return filename; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </FileAlreadyExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ElementAlreadyExistsException: public Exceptions {
private:
	T elementoRepetido;
public:
	explicit ElementAlreadyExistsException(T elemento_repetido, const char* pStr = "Elemento já existe!") :
		Exceptions(pStr), elementoRepetido(elemento_repetido) {}
	virtual ~ElementAlreadyExistsException() throw() {}

	T getElementoRepetido() const { return elementoRepetido; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ElementDoesntExistsException: public Exceptions {
private:
	T elementoInexistente;
public:
	explicit ElementDoesntExistsException(T elementoInexistente, const char* pStr = "Elemento não existe!") :
		Exceptions(pStr), elementoInexistente(elementoInexistente) {}
	virtual ~ElementDoesntExistsException() throw() {}

	T getElementoInexistente() const { return elementoInexistente; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um vector se encontra vazio.
class EmptyContainerException: public Exceptions {
public:
	explicit EmptyContainerException(const char* pStr = "O container que está a tentar aceder está vazio!") : Exceptions(pStr) {}
	virtual ~EmptyContainerException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que um dado ficheiro que de dados está corrupto ou num formato desconhecido.
class CorruptedFileException: public Exceptions {
private:
	char* filename;

public:
	explicit CorruptedFileException(const char* pStr = "Ficheiro com os dados corrompido!") : Exceptions(pStr) {}
	string getFilename() const { return filename; }
	virtual ~CorruptedFileException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ExOutOfRange>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um elemento que se está a tentar aceder está fora do domínio do contentor.
class ExOutOfRange: public Exceptions {
public:
	explicit ExOutOfRange(const char* pStr = "Valor fora do domínio do vector!") : Exceptions(pStr) {}
	virtual ~ExOutOfRange() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ExOutOfRange>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ExNoInterval>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que o intervalo fornecido é inválido
class ExNoInterval: public Exceptions {
public:
	explicit ExNoInterval(const char* pStr = "O intervalo começa e acaba em zero!") : Exceptions(pStr) {}
	virtual ~ExNoInterval() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ExNoInterval>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#endif /* EXCEPTIONS_H_ */
