/**	@file: ut_avltree_erase.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T>::erase() unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avltree.hpp"
#include "KaylaTestObject.hpp"



/**	iterator erase( iterator ) */
BOOST_AUTO_TEST_CASE( ut_erase_iterator ) {
	/*std::cout << "NOT IMPLEMENTED: avltree<T>::erase(iterator)\n";*/
/****************Int, Int*********************/
	avltree<int,int> avltree_int_int;

	for(int i = 0; i < 10; i++)
	{
		std::pair<int,int>testpair(i,100);		
		avltree_int_int.insert(testpair);
	}
	BOOST_CHECK(avltree_int_int.size() == 10);
	avltree<int,int>::iterator int_int_it = avltree_int_int.begin();
	avltree_int_int.erase(int_int_it);
	BOOST_CHECK(avltree_int_int.size() == 9);


///****************Char, Int*********************/
	avltree<char,int> avltree_char_int;

	for(int i = 0; i < 10; i++)
	{
		std::pair<char,int>testpair('a'+i,100);
		avltree_char_int.insert(testpair);
	}
	BOOST_CHECK(avltree_char_int.size() == 10);
	avltree<char,int>::iterator char_int_it = avltree_char_int.begin();
	avltree_char_int.erase(char_int_it);
	BOOST_CHECK(avltree_char_int.size() == 9);

///****************Int, KaylaTestObject*********************/
	avltree<int,KaylaTestObject> avltree_int_object;
	KaylaTestObject testObject;
	for(int i = 0; i < 10; i++)
	{
		std::pair<int,KaylaTestObject>testpair(i,testObject);
		avltree_int_object.insert(testpair);
	}
	BOOST_CHECK(avltree_int_object.size() == 10);
	avltree<int,KaylaTestObject>::iterator int_object_it = avltree_int_object.begin();
	avltree_int_object.erase(int_object_it);
	BOOST_CHECK(avltree_int_object.size() == 9);

///****************Double, String*********************/
	avltree<double, std::string> avltree_double_string;

	for(double i = 0.1; i < 10; i++)
	{
		std::pair<double,std::string>testpair(i,"Kayla");
		avltree_double_string.insert(testpair);
	}
	BOOST_CHECK(avltree_double_string.size() == 10);
	avltree<double,std::string>::iterator double_string_it = avltree_double_string.begin();
	avltree_double_string.erase(double_string_it);
	BOOST_CHECK(avltree_double_string.size() == 9);

}

/**	iterator erase( iterator, iterator ) */
BOOST_AUTO_TEST_CASE( ut_erase_iterator_iterator ) {
	/*std::cout << "NOT IMPLEMENTED: avltree<T>::erase(iterator,iterator)\n";*/
/****************Int, Int*********************/
	avltree<int,int> avltree_int_int;

	for(int i = 0; i < 10; i++)
	{
		std::pair<int,int>testpair(i,100);
		avltree_int_int.insert(testpair);
	}
	BOOST_CHECK(avltree_int_int.size() == 10);
	avltree<int,int>::iterator it_first = avltree_int_int.begin();
	avltree<int,int>::iterator it_last = avltree_int_int.end();
	it_first++;
	it_last--;
	avltree_int_int.erase(it_first,it_last);
	
	BOOST_CHECK(avltree_int_int.size() == 2);
	it_first = avltree_int_int.begin();
	it_last = avltree_int_int.end();
	avltree_int_int.erase(it_first,it_last);
	BOOST_CHECK(avltree_int_int.size() == 0);

///****************Char, Int*********************/
	avltree<char,int> avltree_char_int;

	for(int i = 0; i < 10; i++)
	{
		std::pair<char,int>testpair('a'+i,100);
		avltree_char_int.insert(testpair);
	}
	
	BOOST_CHECK(avltree_char_int.size() == 10);
	avltree<char,int>::iterator char_int_it_first = avltree_char_int.begin();
	avltree<char,int>::iterator char_int_it_last = avltree_char_int.end();
	char_int_it_first++;
	char_int_it_last--;
	avltree_char_int.erase(char_int_it_first,char_int_it_last);
	BOOST_CHECK(avltree_char_int.size() == 2);
	char_int_it_first = avltree_char_int.begin();
	char_int_it_last = avltree_char_int.end();
	avltree_char_int.erase(char_int_it_first,char_int_it_last);
	BOOST_CHECK(avltree_char_int.size() == 0);

///****************Int, KaylaTestObject*********************/
	avltree<int,KaylaTestObject> avltree_int_object;
	KaylaTestObject testObject;
	for(int i = 0; i < 10; i++)
	{
		std::pair<int,KaylaTestObject>testpair(i, testObject);
		avltree_int_object.insert(testpair);
	}
	BOOST_CHECK(avltree_int_object.size() == 10);
	avltree<int,KaylaTestObject>::iterator int_object_it_first = avltree_int_object.begin();
	avltree<int,KaylaTestObject>::iterator int_object_it_last = avltree_int_object.end();
	int_object_it_first++;
	int_object_it_last--;
	avltree_int_object.erase(int_object_it_first,int_object_it_last);
	BOOST_CHECK(avltree_int_object.size() == 2);
	int_object_it_first = avltree_int_object.begin();
	int_object_it_last = avltree_int_object.end();
	avltree_int_object.erase(int_object_it_first,int_object_it_last);
	BOOST_CHECK(avltree_int_object.size() == 0);

///****************Double, String*********************/
	avltree<double, std::string> avltree_double_string;

	for(double i = 0.1; i < 10; i++)
	{
		std::pair<double,std::string>testpair(i, "Kayla");
		avltree_double_string.insert(testpair);
	}
	BOOST_CHECK(avltree_double_string.size() == 10);
	avltree<double,std::string>::iterator double_string_it_first = avltree_double_string.begin();
	avltree<double,std::string>::iterator double_string_it_last = avltree_double_string.end();
	double_string_it_first++;
	double_string_it_last--;
	avltree_double_string.erase(double_string_it_first,double_string_it_last);
	BOOST_CHECK(avltree_double_string.size() == 2);
	double_string_it_first = avltree_double_string.begin();
	double_string_it_last = avltree_double_string.end();
	avltree_double_string.erase(double_string_it_first,double_string_it_last);
	BOOST_CHECK(avltree_double_string.size() == 0);


}

/**	size_type erase( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_erase_key ) {
	/*std::cout << "NOT IMPLEMENTED: avltree<T>::erase(key)\n";*/
/****************Int, Int*********************/
	avltree< int,int> avltree_int_int;

	for(int i = 0; i < 10; i++)
		avltree_int_int.insert(std::pair< int,int>(i, 100));
	
	BOOST_CHECK(avltree_int_int.size() == 10);
	avltree< int,int>::iterator int_int_it = avltree_int_int.begin();
	avltree_int_int.erase(int_int_it->first);
	BOOST_CHECK(avltree_int_int.size() == 9);
	avltree_int_int.erase(4);
	BOOST_CHECK(avltree_int_int.size() == 8);

//****************Char, Int*********************/
	avltree< char,int> avltree_char_int;

	for(int i = 0; i < 10; i++)
		avltree_char_int.insert(std::pair<char,int>('a' + i, 100));
	
	BOOST_CHECK(avltree_char_int.size() == 10);
	avltree< char,int>::iterator char_int_it = avltree_char_int.begin();
	avltree_char_int.erase(char_int_it->first);
	BOOST_CHECK(avltree_char_int.size() == 9);
	avltree_char_int.erase('d');
	BOOST_CHECK(avltree_char_int.size() == 8);

//****************Int, KaylaTestObject*********************/
	avltree< int,KaylaTestObject> avltree_int_object;
	KaylaTestObject testObject;
	for(int i = 0; i < 10; i++)
		avltree_int_object.insert(std::pair< int,KaylaTestObject>(i, testObject));
	
	BOOST_CHECK(avltree_int_object.size() == 10);
	avltree< int,KaylaTestObject>::iterator int_object_it = avltree_int_object.begin();
	avltree_int_object.erase(int_object_it->first);
	BOOST_CHECK(avltree_int_object.size() == 9);
	avltree_int_object.erase(4);
	BOOST_CHECK(avltree_int_object.size() == 8);

}


/*=============================================================

Revision History

Version 0.0.0: 2013-01-16
Alpha release.

=============================================================

Copyright Garth Santor

The copyright to the computer program(s) herein
is the property of Garth Santor of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/