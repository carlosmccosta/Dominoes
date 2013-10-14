#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sstream>

#include "defs.h"
#include "LibraryExceptions.h"

//boost
#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
#endif

#ifdef USE_BOOST_FRIEND
	//#include "librarySerialization.h"
	using boost::serialization::serialize;
	class User;
	template<class Archive> void serialize(Archive & archive, User & user, const unsigned int version);
#endif


using namespace std;

class User {

private:
	static IdentNum numUsers; //total number of users - used to obtain ID of each new user
	IdentNum ID; // unique user identifier (unsigned integer)
	string name; // user name
	bool active; // only active users can request books
	vector<IdentNum> requestedBooks; // books presently loaned to the user


	//boost
#ifdef USE_BOOST
	friend class boost::serialization::access;
#endif

#ifdef USE_BOOST_FRIEND
	template<class Archive> friend void serialize(Archive & archive, User & user, const unsigned int version);
#endif

#ifdef USE_BOOST_INSTRUSIVE
	template<class Archive>
	void serialize(Archive & archive, const unsigned int version) {
		archive & numUsers;
		archive & ID;
		archive & name;
		archive & active;
		archive & requestedBooks;
	}
#endif


public:
	//constructors 
	User();
	User(string name);

	//get methods
	static IdentNum getNumUsers();
	IdentNum getID() const;
	string getName() const;
	bool isActive() const;
	vector<IdentNum> getRequestedBooks() const;

	bool hasBooksRequested() const;	

	//set methods
	void setID(IdentNum userID);
	void setName (string userName);
	void setActive(bool status);
	void setRequestedBooks(const vector<IdentNum> &booksRequestedByUser);
	static void setNumUsers(IdentNum num);
	
	void borrowBook(IdentNum bookID);
	void returnBook(IdentNum bookID) throw(ElementDoesntExistsException<IdentNum>);
};


#endif

