/*
 * AuxiliarClasses.hpp
 *
 *  Created on: Jul 22, 2023
 *      Author: iban
 */

#ifndef AUXILIARCLASSES_HPP_
#define AUXILIARCLASSES_HPP_

#include <iostream>
#include <string>

using namespace std;

class BaseTranslator
{
public:
	virtual void translate() = 0;
};

class Translator1 : public BaseTranslator
{
public:
	void translate() override
	{
		cout << "Translator1" << endl;
	}
};

class Translator2 : public BaseTranslator
{
public:
	void translate() override
	{
		cout << "Translator2" << endl;
	}
};

enum class TranslatorTypes
{
	Translator1,
	Translator2
};

class Type1ToType2Translator
{
public:
	void translate(){cout << "Type1ToType2Translator" << endl;}
};

class Type3ToType4Translator
{
public:
	void translate(){cout << "Type3ToType4Translator" << endl;}
};

enum class TranslatorTypesBT
{
	Type1ToType2Translator,
	Type3ToType4Translator
};

class Type5ToType6Translator
{
public:
	explicit Type5ToType6Translator(int storable) : mStored{storable}{}
	void translate(){cout << "Type5ToType6Translator with stored value: " << mStored << endl;}
private:
	int mStored;
};

class Type7ToType8Translator
{
public:
	explicit Type7ToType8Translator(string storable) : mStored{storable}{}
	void translate(){cout << "Type7ToType8Translator with stored value: " << mStored << endl;}
private:
	string mStored;
};

template<class>
inline constexpr bool always_false_v = false;

template<typename T>
struct AlwaysFalse : std::false_type
{ };

#endif /* AUXILIARCLASSES_HPP_ */
