#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <fstream>

#include "defs.h"
#include "book.h"
#include "user.h"

#include "utils.h"

#include "LibraryExceptions.h"


//boost
#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
#endif

#ifdef USE_BOOST_FRIEND
	//#include "librarySerialization.h"
	using boost::serialization::serialize;
	class Library;
	template<class Archive> void serialize(Archive & archive, Library & library, const unsigned int version);
#endif


#define USER_ID_SIZE 5
#define USER_NAME_SIZE 30
#define USER_ACTIVE_STATE_SIZE 15

#define BOOK_ID_SIZE 5
#define BOOK_TITLE_SIZE 25
#define BOOK_AUTHOR_SIZE 20
#define BOOK_QTD_DISP_SIZE 10

#define LIBRARY_FILE_NAME "library.txt"

using namespace std;

class Library {

private:
	vector<User> users; // all users that are registered or were registered in the library
	vector<Book> books; // all books that are registered or were registered in the library
	string filenameUsers; // name of the file where users are saved at the end of each program run
	string filenameBooks; // name of the file where books are saved at the end of each program run

	//boost
#ifdef USE_BOOST
	friend class boost::serialization::access;
#endif

#ifdef USE_BOOST_FRIEND
	template<class Archive> friend void serialize(Archive & archive, Library & library, const unsigned int version);
#endif


#ifdef USE_BOOST_INSTRUSIVE
	template<class Archive>
	void serialize(Archive & archive, const unsigned int version) {
		archive & users;
		archive & books;
		archive & filenameUsers;
		archive & filenameBooks;
	}
#endif



public:
	// constructors
	Library();
	Library(string fileUsers, string fileBooks);

	// get functions
	size_t getUserIndexByID(IdentNum userID) const throw(ElementDoesntExistsException<IdentNum>);
	User getUserByID(IdentNum userID) const;
	User& getRefToUserByID(IdentNum userID);

	size_t getBookIndexByID(IdentNum bookID) const throw(ElementDoesntExistsException<IdentNum>);
	Book getBookByID(IdentNum bookID) const;
	Book& getRefToBookByID(IdentNum bookID);

	const vector<User> &getUsers() const;
	const vector<Book> &getBooks() const;
	string getFilenameUsers() const;
	string getFilenameBooks() const;


	//set functions
	void setUsers(vector<User> &users);
	void setBooks(vector<Book> &books);
	void setFilenameUsers(string filename);
	void setFilenameBooks(string filename);

	// user management
	void addUser(User);

	// book management
	void addBook(Book);

	// loaning management
	void loanBook(IdentNum, IdentNum);
	void returnBook(IdentNum, IdentNum);

	// file management methods
	void loadUsers();
	void loadBooks();
	void saveUsers();
	void saveBooks();

	bool loadLibrary(string filename);
	void saveLibrary(string filename);


	// information display
	void showUsersParameterized(string stringToSearch) const;
	void showUsers() const;
	void showUsers(string str) const;

	void showBooksParameterized(bool showUnavailableBooks, string stringToSearch) const;
	void showBooks() const;
	void showBooks(string str) const;
	void showAvailableBooks() const;
	void showUserBooks(vector<IdentNum> IDsOfBooksRequestedByTheUser);


	// CLI interface
	void registerUserCLI();		//1
	void addBookCLI();			//2
	void listAllUsersCLI();		//3
	void listAllBooksCLI();		//4
	void searchUserCLI();		//5
	void searchBookCLI();		//6
	void changeUserStateCLI();	//7
	void requestBookCLI();		//8
	void returnBookCLI();		//9


	// contagens
	size_t countAvailableBooks();
	size_t countUsersWithRequestedBooks();
	size_t countActiveUsers();
};


#endif
