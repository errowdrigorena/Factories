/*
 * AuxiliarClassesNotLiskov.hpp
 *
 *  Created on: Oct 08, 2023
 *      Author: iban
 */

#ifndef AUXILIARCLASSESNOTLISKOV_HPP_
#define AUXILIARCLASSESNOTLISKOV_HPP_

#include <iostream>
#include <string>

using namespace std;

// This is not Liskov because the classes do not inherit from the same base class
// and the methods are not the same.
// It is not recommended to use this approach.
class Translator1NotLiskov
{
public:
	void translate1()
	{
		cout << "Translator1" << endl;
	}
};

class Translator2NotLiskov
{
public:
	void translate2()
	{
		cout << "Translator2" << endl;
	}
};

enum class TranslatorTypes
{
	Translator1NotLiskov,
	Translator2NotLiskov
};

#endif /* AUXILIARCLASSESNOTLISKOV_HPP_ */
