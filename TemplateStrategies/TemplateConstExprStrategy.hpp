/*
 * TemplateConstExprStrategy.hpp
 *
 *  Created on: Jul 22, 2023
 *      Author: iban
 */

#ifndef TEMPLATECONSTEXPRSTRATEGY_HPP_
#define TEMPLATECONSTEXPRSTRATEGY_HPP_

#include <memory>
#include <type_traits>
#include <AuxiliarClasses.hpp>

using namespace std;

// notice that the constexpr if could be avoided as the constructor always does
// make_unique<T>(). But this is just to show how to use it.
// If those conditions 
class FactoryTempConstExprPointer
{
public:
		template<typename T>
		unique_ptr<T> createTranslator() // or maybe more apropiate just T instead of unique_ptr
		{
			if constexpr (is_same_v<Type1ToType2Translator, T>)
			{
				return make_unique<Type1ToType2Translator>();
			}
			else if constexpr (is_same_v<Type3ToType4Translator, T>)
			{
				return make_unique<Type3ToType4Translator>();
			}
			else
			{
				cerr << "is nullptr" << endl; // this can be improved
				return nullptr;
			}
	}
};

class FactoryTempConstExprValue
{
public:
		template<typename T>
		T createTranslator()
		{
			if constexpr (is_same_v<Type1ToType2Translator, T>)
			{
				return Type1ToType2Translator{};
			}
			else if constexpr (is_same_v<Type3ToType4Translator, T>)
			{
				return Type3ToType4Translator{};
			}
			else
			{
				static_assert( AlwaysFalse<T>::value, "this function has to be implemented for desired type");
				return T{}; //IT WILL NEVER BE EXECUTED
			}
	}
};



#endif /* TEMPLATECONSTEXPRSTRATEGY_HPP_ */
