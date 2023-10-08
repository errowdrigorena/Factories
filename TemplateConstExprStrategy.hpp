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

class FactoryTempConstExpr
{
public:
		template<typename T>
		unique_ptr<T> createTranslator() // or maybe more apropiate just T instead of unique_ptr
		{
			if constexpr (is_same_v<Type1ToType2Translator, T>)
			{
				/*if(translatorA == nullptr)
				{
					translatorA = make_unique<Type1ToType2Translator>();
				}*/
				return make_unique<Type1ToType2Translator>();
			}
			else if(is_same_v<Type3ToType4Translator, T>)
			{
				/*if(translatorB == nullptr)
				{
					//translatorB = make_unique<Type3ToType4Translator>();
				}*/
				return make_unique<Type3ToType4Translator>();
			}
			else
			{
				cout << "Type3ToType4Translator" << endl;
				return unique_ptr<Type1ToType2Translator>{};
			}
	}
private:
	unique_ptr<Type1ToType2Translator> translatorA; //sensible only with shared_ptrs
	unique_ptr<Type3ToType4Translator> translatorB;
};


#endif /* TEMPLATECONSTEXPRSTRATEGY_HPP_ */
