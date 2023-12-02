/*
 * TemplateFactory.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef TEMPLATESPECIALIZATIONFACTORY_HPP_
#define TEMPLATESPECIALIZATIONFACTORY_HPP_

#include <AuxiliarClasses.hpp>
#include <AuxiliarClassesLiskov.hpp>
#include <type_traits>
#include <memory>

using namespace std;

class FactoryTemplateSpecialization 
{
public:
		template<typename T>
		T createTranslator();
};

//would not work inside class
template<typename T>
T FactoryTemplateSpecialization::createTranslator()
{
	static_assert( AlwaysFalse<T>::value, "this function has to be implemented for desired type");
	return T{}; //IT WILL NEVER BE EXECUTED
}

template<>
Type5ToType6Translator FactoryTemplateSpecialization::createTranslator()
{
	return Type5ToType6Translator{5};
}

template<>
Type7ToType8Translator FactoryTemplateSpecialization::createTranslator()
{
	return Type7ToType8Translator("five");
}
//***********************************************************************************

class FactoryTemplateSpecializationRegularAndLiskov 
{
public:
		template<typename T>
		typename enable_if<is_base_of_v<BaseTranslatorLiskov, T>, T>::type createTranslator();
};

// let us assume that almost all translators are initialized with no parameters
// if not, we would have to specialize for each translator
template<typename T>
typename enable_if<is_base_of_v<BaseTranslatorLiskov, T>, T>::type 
	FactoryTemplateSpecializationRegularAndLiskov::createTranslator()
{
	return T{};
}

// even when it is not needed at all, if we use the netion of enable_if,
// we can make a clearer failure message in compilation time
/*template<typename T>
typename enable_if<!is_base_of_v<T, T>, T>::type createTranslator()
{
	static_assert( AlwaysFalse<T>::value, "this function has to be implemented for desired type");
	return T{}; //IT WILL NEVER BE EXECUTED
}*/

//***********************************************************************************
//now we will use the same approach but with input parameters in the function
class FactoryTemplateSpecializationRegularAndLiskovWithParameters 
{
public:
	template<typename T, typename... Args>
	void translate(Args&&... args);
private:
	template<typename T>
	T createTranslator();
};

template <typename T>
T FactoryTemplateSpecializationRegularAndLiskovWithParameters::createTranslator()
{
	return T{};
}

template<typename T, typename... Args>
void FactoryTemplateSpecializationRegularAndLiskovWithParameters::translate(Args&&... args)
{
	auto translator{createTranslator<T>()};
	translator.translate(forward<Args>(args)...);
}

#endif /* TEMPLATESPECIALIZATIONFACTORY_HPP_ */
