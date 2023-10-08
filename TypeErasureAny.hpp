/*
 * WhitTypeErasure.hpp
 *
 *  Created on: Jul 22, 2023
 *      Author: iban
 */

#ifndef TYPEERASUREANY_HPP_
#define TYPEERASUREANY_HPP_

#include <any>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <iomanip>

#include <AuxiliarClasses.hpp>

using namespace std;

template<class T, class F>
inline pair<const type_index, function<void(const any&)>>
    to_any_visitor(F const &f)
{
    return
    {
        type_index(typeid(T)),
        [g = f](std::any const &a)
        {
            if constexpr (std::is_void_v<T>)
			{
                g();
			}
            else
            {
                g(std::any_cast<T const&>(a));
            }
        }
    };
}

static unordered_map<type_index, function<void(const any&)>>
    any_visitor
{
    to_any_visitor<Type1ToType2Translator>([](Type1ToType2Translator translatable) { translatable.translate(); }),
    to_any_visitor<Type3ToType4Translator>([](Type3ToType4Translator translatable) { translatable.translate(); }),
    // ... add more handlers for your types ...
};

inline void process(const any& a)
{
    if (const auto it = any_visitor.find(std::type_index(a.type()));
        it != any_visitor.cend())
        it->second(a);
    else
        std::cout << "Unregistered type "<< std::quoted(a.type().name());
}

class FactoryTypeErasure
{
public:
	any create(TranslatorTypesBT type)
	{
		if(TranslatorTypesBT::Type1ToType2Translator == type)
		{
			return Type1ToType2Translator{};
		}
		else if(TranslatorTypesBT::Type3ToType4Translator == type)
		{
			return Type3ToType4Translator{};
		}
		else
		{
			cout << "Invalid" << endl;
			return 0;
		}
	}

	void useTranslator(TranslatorTypesBT type) //should go in another class
	{
		auto myTranslator = create(type);
		if(myTranslator.type() == typeid(Type1ToType2Translator))
		{
			any_cast<Type1ToType2Translator>(myTranslator).translate();
		}
		else if(myTranslator.type() == typeid(Type3ToType4Translator))
		{
			any_cast<Type3ToType4Translator>(myTranslator).translate();
		}
		else
		{
			cout << "Invalid" << endl;
		}
	}

	void useTranslatorCool(TranslatorTypesBT type) //should go in another class
	{
		auto myTranslator = create(type);
		process(myTranslator);
	}
};

#endif /* TYPEERASUREANY_HPP_ */
