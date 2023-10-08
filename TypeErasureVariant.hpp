/*
 * TypeErasureVariant.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef TYPEERASUREVARIANT_HPP_
#define TYPEERASUREVARIANT_HPP_

#include <variant>

#include <AuxiliaryClasses/AuxiliarClasses.hpp>

using namespace std;

using Translators = variant<Type1ToType2Translator, Type3ToType4Translator, int>;

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class FactoryTypeErasureVariant
{
public:
	Translators create(TranslatorTypesBT type)
	{
		Translators myTranslator;
		if(TranslatorTypesBT::Type1ToType2Translator == type)
		{
			myTranslator = Type1ToType2Translator{};
		}
		else if(TranslatorTypesBT::Type3ToType4Translator == type)
		{
			myTranslator = Type3ToType4Translator{};
		}
		else
		{
			myTranslator = 0;
			cout << "Invalid CREATION" << endl; //put an assert here instead
		}
		return myTranslator;
	}

	void performTranslation(Translators translator)
	{
		visit(overloaded{[](auto val){val.translate();},
			  [](int val){cout << "Invalid TRANSLATION" << val << endl;}},
				translator);
	}
};



#endif /* TYPEERASUREVARIANT_HPP_ */
