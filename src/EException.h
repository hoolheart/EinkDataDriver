/*
 * EException.h
 *
 *  Created on: 2013-1-17
 *      Author: Edward Chou
 */

#ifndef EEXCEPTION_H_
#define EEXCEPTION_H_
#include <string.h>

/*
 * Class Name: EException
 * Function: Represent Exception when Matrix Operates
 */
class EException {
private:
	char * error;
public:
	explicit EException(const char * err) {
		error = new char[strlen(err)+1];
		strcpy(error,err);
	}
	char * what() const {
		return error;
	}
    ~EException()
    {
        delete error;
    }
};

#ifndef _NO_EXCEPTION
	static inline void reportErr(char * _err) {throw EException(_err);}
    #define _NO_THROW throw()
    #define _THROW_ERROR throw(EException)
#else
	#include <iostream>
	#include <stdlib>
	using namespace std;
	static inline void reportErr(char * _err) {cout<<_err<<endl;exit(1);}
	#define _NO_THROW
	#define _THROW_ERROR
#endif

#endif /* EEXCEPTION_H_ */
