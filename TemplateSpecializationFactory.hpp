/*
 * TemplateFactory.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: iban
 */

#ifndef TEMPLATESPECIALIZATIONFACTORY_HPP_
#define TEMPLATESPECIALIZATIONFACTORY_HPP_

#include <AuxiliarClasses.hpp>
#include <memory>

class FactoryTemplateSpecialization //would not work inside a class
{
public:
		template<typename T>
		shared_ptr<T> createTranslator();
};

template<typename T>
shared_ptr<T> FactoryTemplateSpecialization::createTranslator()
{
	cout << "This is not correct" << endl;
	return{nullptr};
}

template<>
shared_ptr<Type5ToType6Translator> FactoryTemplateSpecialization::createTranslator()
{
	return make_shared<Type5ToType6Translator>(5);
}

template<>
shared_ptr<Type7ToType8Translator> FactoryTemplateSpecialization::createTranslator()
{
	return make_shared<Type7ToType8Translator>("five");
}

#endif /* TEMPLATESPECIALIZATIONFACTORY_HPP_ */
