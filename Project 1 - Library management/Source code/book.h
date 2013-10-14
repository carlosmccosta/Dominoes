#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "defs.h"


//boost
#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
#endif

#ifdef USE_BOOST_FRIEND
	//#include "librarySerialization.h"
	using boost::serialization::serialize;	
	class Book;
	template<class Archive> void serialize(Archive & archive, Book & book, const unsigned int version);
#endif


using namespace std;

class Book {

private:
	static IdentNum numBooks; //total number of books - used to obtain ID of each new book
	IdentNum ID; // unique book identifier (unsigned integer)
	string title; // book title
	string author; // book author OR authors 
	unsigned int numAvailable; // number of available items with this title


	//boost
#ifdef USE_BOOST
	friend class boost::serialization::access;
#endif

#ifdef USE_BOOST_FRIEND
	template<class Archive> friend void serialize(Archive & archive, Book & book, const unsigned int version);
#endif


#ifdef USE_BOOST_INSTRUSIVE
	template<class Archive>
	void serialize(Archive & archive, const unsigned int version) {
		archive & numBooks;
		archive & ID;
		archive & title;
		archive & author;
		archive & numAvailable;
	}
#endif


public:
	//constructors
	Book();
	Book(string bookTitle, string bookAuthor, unsigned int bookQuantity);

	//get methods
	static IdentNum getNumBooks();
	IdentNum getID() const;
	string getTitle() const;
	string getAuthor() const;
	unsigned int getNumAvailable() const;	

	//set methods
	void setID(IdentNum bookID);
	void setTitle(string bookTitle);
	void setAuthor(string bookAuthor);
	void setNumAvailable(unsigned int numBooks);
	static void setNumBooks(IdentNum num);

	void addBooks(int bookQuantity);
	void loanBook();
	void returnBook();
};




#endif

