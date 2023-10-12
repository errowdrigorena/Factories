/*
 * TypeErasureVariant.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef TYPEERASUREVARIANT_HPP_
#define TYPEERASUREVARIANT_HPP_

#include <variant>

#include <AuxiliarClasses.hpp>

using namespace std;

// monostate is a type that can hold no value. It is the type of the default-constructed 
// std::variant and std::any. With this it can be guaranteed that the variant is default-constructive.
// in this case, it is used to indicate that the variant is not initialized, that the factory has not
// created any translator successfully.
using Translators = variant<monostate, Type1ToType2Translator, Type3ToType4Translator>;

// overload pattern is used to perform different actions depending on the type of the variant
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
			myTranslator = monostate{};
			// a better alternative could be an assert or throw an exception

		}
		return myTranslator;
	}

	void performTranslation(Translators translator)
	{
		visit(overloaded{[](auto val){val.translate();},
			  			 []([[maybe_unused]]monostate val){cout << "Invalid TRANSLATION" << endl;}},
						 translator);
	}
};



#endif /* TYPEERASUREVARIANT_HPP_ */
