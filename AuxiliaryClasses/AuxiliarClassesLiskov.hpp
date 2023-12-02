/*
 * AuxiliarClassesLiskov.hpp
 *
 *  Created on: Oct 08, 2023
 *      Author: iban
 */

#ifndef AUXILIARCLASSESLISKOV_HPP_
#define AUXILIARCLASSESLISKOV_HPP_

#include <iostream>
#include <string>

using namespace std;

// Here are the same classes as in AuxiliaryClasses/AuxiliarClassesNotLiskov.hpp
// but now they inherit from the same base class and the translate member function has the same signature.
// This is Liskov.
// It can be seen that the only point in which the NOT LISKOV is superior is legibility.
// But calling to translate1() and translate2() when calling to translate() that legibility does not differ
// much from calling to translate1() and translate2() directly.
// It would be even better that translate1() and translate2() were normal functions and not member functions,
// in the .cpp file, and that translate() called to them. That would be the best approach.
// But it is not possible to do so because the examples are in the header file for simplicity.
// It is recommended to use this approach.
class BaseTranslatorLiskov
{
public:
	virtual void translate() = 0;
};

class Translator1Liskov : public BaseTranslatorLiskov
{
public:
	void translate() override
	{
		translate1();
	}
private:
	void translate1()
	{
		cout << "Translator1" << endl;
	}
};

class Translator2Liskov : public BaseTranslatorLiskov
{
public:
	void translate() override
	{
		translate2();
	}
private:
	void translate2()
	{
		cout << "Translator2" << endl;
	}
};

enum class TranslatorTypesLiskov
{
	Translator1Liskov,
	Translator2Liskov
};

// Now we will try the same but with arguments in the calle method.
class BaseTranslatorLiskovWithArgs
{
public:
	virtual void translate(int arg1, double arg2) = 0;
};

class Translator1LiskovWithArgs : public BaseTranslatorLiskovWithArgs
{
public:
	void translate(int arg1, double arg2) override
	{
		cout << "Translator1LiskovWithArgs arg1 = " << arg1 << " arg2 = " << arg2 << endl;
	}
};

class Translator2LiskovWithArgs : public BaseTranslatorLiskovWithArgs
{
public:
	void translate(int arg1, double arg2) override
	{
		cout << "Translator2LiskovWithArgs arg1 = " << arg1 << " arg2 = " << arg2 << endl;
	}
};
#endif /* AUXILIARCLASSESLISKOV_HPP_ */
