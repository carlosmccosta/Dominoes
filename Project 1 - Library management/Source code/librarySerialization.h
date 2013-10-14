/**\file librarySerialization.h
 * \brief Ficheiro com as funções usadas na serialização da classe Library para usar com o boost
 *
 * PROJECTO: Projecto 1 - Programação - 10-11 - MIEIC\n
 * FICHEIRO: librarySerialization.h \n
 * DESCRIÇÃO: Ficheiro com as funções usadas na serialização da classe Library para usar com o boost. \n
 *
 * AUTOR:
 * - Carlos Miguel Correia da Costa
 */

#ifndef LIBRARYSERIALIZATION_H_
#define LIBRARYSERIALIZATION_H_

#include <fstream>
#include <string>

using namespace std;


#include "defs.h"
#include "library.h"
#include "book.h"
#include "user.h"
//class Library;
//class Book;
//class User;


//boost
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>



#ifdef USE_BOOST_GETS
	BOOST_SERIALIZATION_SPLIT_FREE(User)
	BOOST_SERIALIZATION_SPLIT_FREE(Book)
	BOOST_SERIALIZATION_SPLIT_FREE(Library)
#endif

namespace boost {
namespace serialization {


#ifdef USE_BOOST_FRIEND
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <with friends>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	template<class Archive>
	void serialize(Archive & archive, User & user, const unsigned int version) {
		archive & User::numUsers;
		archive & user.ID;
		archive & user.name;
		archive & user.active;
		archive & user.requestedBooks;
	}


	template<class Archive>
	void serialize(Archive & archive, Book & book, const unsigned int version) {
		archive & Book::numBooks;
		archive & book.ID;
		archive & book.title;
		archive & book.author;
		archive & book.numAvailable;
	}

	template<class Archive>
	void serialize(Archive & archive, Library & library, const unsigned int version) {
		archive & library.users;
		archive & library.books;
		archive & library.filenameUsers;
		archive & library.filenameBooks;
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </with friends>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif


#ifdef USE_BOOST_GETS
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <with gets>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	template<class Archive>
	void save(Archive & archive, const User & user, const unsigned int version) {
		IdentNum numUsers = (IdentNum)User::getNumUsers;
		IdentNum ID = user.getID();
		string name = user.getName();
		bool active = user.isActive();
		vector<IdentNum> books = user.getRequestedBooks();

		archive & numUsers & ID & name & active & books;
	}

	template<class Archive>
	void load(Archive & archive, User & user, const unsigned int version) {
		IdentNum numUsers;
		IdentNum ID;
		string name;
		bool active;
		vector<IdentNum> books;

		archive & numUsers & ID & name & active & books;
	
		user.setNumUsers(numUsers);
		user.setID(ID);
		user.setName(name);
		user.setActive(active);
		user.setRequestedBooks(books);
	}




	template<class Archive>
	void save(Archive & archive, const Book & book, const unsigned int version) {
		IdentNum numBooks = (IdentNum)Book::getNumBooks();
		IdentNum ID = book.getID();
		string title = book.getTitle();
		string author = book.getAuthor();
		unsigned int numAvailable = book.getNumAvailable();

		archive & numBooks & ID & title & author & numAvailable;
	}

	template<class Archive>
	void load(Archive & archive, Book & book, const unsigned int version) {
		IdentNum numBooks;
		IdentNum ID;
		string title;
		string author;
		unsigned int numAvailable;

		archive & numBooks & ID & title & author & numAvailable;

		book.setNumBooks(numBooks);
		book.setID(ID);
		book.setTitle(title);
		book.setAuthor(author);
		book.setNumAvailable(numAvailable);
	}



	template<class Archive>
	void save(Archive & archive, const Library & library, const unsigned int version) {
		const vector<User>& users = library.getUsers();
		const vector<Book>& books = library.getBooks();
		string filenameUsers = library.getFilenameUsers();
		string filenameBooks = library.getFilenameBooks();

		archive & users & books & filenameUsers & filenameBooks;
	}

	template<class Archive>
	void load(Archive & archive, Library & library, const unsigned int version) {
		vector<User> users;
		vector<Book> books;
		string filenameUsers;
		string filenameBooks;

		archive & users & books & filenameUsers & filenameBooks;

		library.setUsers(users);
		library.setBooks(books);
		library.setFilenameUsers(filenameUsers);
		library.setFilenameBooks(filenameBooks);
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </with gets>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif




/**
 * Método que carrega o library usando a biblioteca de serialização das librarias do boost
 * P.S. Mais eficiente do que o loadUsers() e loadBooks()
 * @param filename Nome do ficheiro para onde será guardado a biblioteca
 * @param library biblioteca que vai ser carregada
 * @return Caso carregue com sucesso retorna true, senão false
 */
bool loadLibrary(string filename, Library& library) {

	std::ifstream inputFileStream(filename.c_str());

	if (inputFileStream.is_open()) {
		boost::archive::text_iarchive inputArchive(inputFileStream);
		inputArchive >> library;

		inputFileStream.close();

		//conseguiu ler o ficheiro
		return true;
	}

	//não conseguiu abrir o ficheiro
	return false;
}


/**
 * Método que guarda a library usando a biblioteca de serialização das librarias do boost
 * * P.S. Mais eficiente do que o saveUsers() e saveBooks()
 * @param filename Nome para onde será guardada a biblioteca
 * @param library biblioteca que vai ser guardada
 */
void saveLibrary(string filename, Library& library) {

	std::ofstream outputFileStream(filename.c_str());

	boost::archive::text_oarchive outputArchive(outputFileStream);

	outputArchive << library;

	outputFileStream.close();

}

}
}

#endif /* LIBRARYSERIALIZATION_H_ */
