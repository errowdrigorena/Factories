/*
 * SFINAEFactoy.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef SFINAEFACTORY_HPP_
#define SFINAEFACTORY_HPP_

#include <type_traits>
#include <AuxiliarClasses.hpp>

using namespace std;

class FactorySFINAE
{
public:
		template<typename T>
		typename enable_if<is_same_v<T, Type5ToType6Translator>, T>::type createTranslator()
		{
			return Type5ToType6Translator{5};
		}

		template<typename T>
		typename enable_if<is_same_v<T, Type7ToType8Translator>, T>::type createTranslator()
		{
			return Type7ToType8Translator{"five"};
		}
};


#endif /* SFINAEFACTORY_HPP_ */
