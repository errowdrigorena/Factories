/*
 * NoFactory.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef NOFACTORY_HPP_
#define NOFACTORY_HPP_

#include <iostream>

#include <AuxiliarClasses.hpp>

using namespace std;

class NoFactory
{
public:
	Type1ToType2Translator getType1ToType2Translator()
	{
		return Type1ToType2Translator{};
	}

	Type3ToType4Translator getType3ToType4Translator()
	{
		return Type3ToType4Translator{};
	}
};


#endif /* NOFACTORY_HPP_ */
