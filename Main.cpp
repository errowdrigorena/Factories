#include <iostream>
#include <memory>
#include <type_traits>
#include <TemplateConstExprStrategy.hpp>
#include <NoFactory.hpp>
#include <UsualFactory.hpp>
#include <SFINAEFactory.hpp>
#include <TemplateSpecializationFactory.hpp>
#include <TypeErasureAny.hpp>
#include <TypeErasureVariant.hpp>
#include <Translator1Creator.hpp>
#include <Translator2Creator.hpp>
#include <GenericFactoryMethod.hpp>

#include <boost/functional/factory.hpp>
#include <boost/functional/value_factory.hpp>

using namespace std;

//The intend of this program is to show how different implementations about how a
//factory may work
int main(int argc, char **argv) {
	cout << "Factories" << endl<< endl << endl;

	cout << "** No Factory (it really is, maybe a better name could be functional old fashion factory) **" << endl;
	NoFactory myNoFactory;
	myNoFactory.getType1ToType2Translator().translate();
	myNoFactory.getType3ToType4Translator().translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Usual Factory **" << endl;
	factoryUsual myUsualFactory;
	auto trasnlatorUsual = myUsualFactory.createTranslator(TranslatorTypes::Translator1);
	trasnlatorUsual->translate();
	trasnlatorUsual = myUsualFactory.createTranslator(TranslatorTypes::Translator2);
	trasnlatorUsual->translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Constexpr (pointer) **" << endl;
	FactoryTempConstExprPointer myConstExprPtrFactory;
	auto translatorConstexprPtr = myConstExprPtrFactory.createTranslator<Type1ToType2Translator>();
	translatorConstexprPtr->translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Constexpr (value) **" << endl;
	FactoryTempConstExprValue myConstExprValFactory;
	auto translatorConstexprVal = myConstExprValFactory.createTranslator<Type3ToType4Translator>();
	translatorConstexprVal.translate();
	// NOTICE THIS. It will crash. Why? Because the compiler will try to instantiate the else branch
	// and the assert will always make it fail AT COMPILATION TIME
	// uncomment NEXT LINE to try it
	// auto translatorConstexprValCrash = myConstExprValFactory.createTranslator<Translator1>(); 
	cout << "****************" << endl << endl << endl;

	cout << "** Factory SFINAE **" << endl;
	FactorySFINAE myFactorySFINAE;
	auto translatorSfinae = myFactorySFINAE.createTranslator<Type5ToType6Translator>();
	translatorSfinae.translate();
	auto translatorSfinae2 = myFactorySFINAE.createTranslator<Type7ToType8Translator>();
	translatorSfinae2.translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Template Specialization Differente kind of initialitation**" << endl;
	FactoryTemplateSpecialization factoryTemplateSpecialization;
	// As above, this will crash. Why? Because the less specialized template member function will be called
	// this function is the one that has an allways failing static_assert (COMPILATION TIME assert)
	// uncomment NEXT LINE to try it
	// auto translatorTemplateSpecializationFails = factoryTemplateSpecialization.createTranslator<Type1ToType2Translator>();
	auto translatorTemplateSpecialization5To6= factoryTemplateSpecialization.createTranslator<Type5ToType6Translator>();
	translatorTemplateSpecialization5To6.translate();

	auto translatorTemplateSpecialization7To8= factoryTemplateSpecialization.createTranslator<Type7ToType8Translator>();
	translatorTemplateSpecialization7To8.translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Template Specialization LISKOV**" << endl;
	FactoryTemplateSpecializationRegularAndLiskov factoryTemplateSpecializationLiskov;
	
	// In the following lines it is shown how easy it can be to use an object based strategy
	// with pointers
	auto translatorLiskov{static_cast<unique_ptr<BaseTranslatorLiskov>>
		(make_unique<Translator1Liskov>
		(factoryTemplateSpecializationLiskov.createTranslator<Translator1Liskov>())) };
	translatorLiskov->translate();
	
	translatorLiskov = make_unique<Translator2Liskov>(
		factoryTemplateSpecializationLiskov.createTranslator<Translator2Liskov>());
	translatorLiskov->translate();

	// This will crash. Why? Because it doesn't exist a createTranslator function for non
	// BaseTranslatorLiskov bases
	// auto translatorTemplateSpecialization5To6Liskov= factoryTemplateSpecializationLiskov.createTranslator<Type5ToType6Translator>();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Template Specialization LISKOV with parameters**" << endl;
	FactoryTemplateSpecializationRegularAndLiskovWithParameters factoryTemplateSpecializationLiskovWithParameters;	
	factoryTemplateSpecializationLiskovWithParameters.translate<Translator1LiskovWithArgs>(1, 2.0);
	factoryTemplateSpecializationLiskovWithParameters.translate<Translator2LiskovWithArgs>(3, 4.5);
	factoryTemplateSpecializationLiskovWithParameters.translate<Translator1Liskov>();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Type Erasure Variant **" << endl;
	FactoryTypeErasureVariant factoryTypeErasureVariant;
	auto translatorVariant1To2 = factoryTypeErasureVariant.create(TranslatorTypesBT::Type1ToType2Translator);
	factoryTypeErasureVariant.performTranslation(translatorVariant1To2);
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Type Erasure Any **" << endl;
	FactoryTypeErasure myTypeErasureFactory;
	auto b = any_cast<Type1ToType2Translator>(myTypeErasureFactory.create(TranslatorTypesBT::Type1ToType2Translator));
	b.translate();
	myTypeErasureFactory.useTranslator(TranslatorTypesBT::Type1ToType2Translator);
	myTypeErasureFactory.useTranslator(TranslatorTypesBT::Type3ToType4Translator);
	myTypeErasureFactory.useTranslatorCool(TranslatorTypesBT::Type1ToType2Translator);
	cout << "****************" << endl << endl << endl;

	cout << "** Functional Factory Boost **" << endl;
	auto boostTranslatorUnique = boost::factory<unique_ptr<Type1ToType2Translator>>()();
	boostTranslatorUnique->translate();
	auto boostTranslatorValue = boost::value_factory<Type3ToType4Translator>()();
	boostTranslatorValue.translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Traditional Factory Method **" << endl;
	unique_ptr<Creator> translatorCreator = make_unique<Translator1Creator>();
	translatorCreator->translate();
	translatorCreator = make_unique<Translator2Creator>();
	translatorCreator->translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Generic Factory Method **" << endl;
	GenericConcreteCreator<BaseTranslatorLiskov, Translator1Liskov> Translator1LiskovGeneric;
	Translator1LiskovGeneric.translate();
	GenericConcreteCreator<BaseTranslatorLiskov, Translator2Liskov> Translator2LiskovGeneric;
	Translator2LiskovGeneric.translate();
	GenericConcreteCreator<BaseTranslatorLiskovWithArgs, Translator1LiskovWithArgs, int, double> Translator1LiskovGenericWithArgs;
	Translator1LiskovGenericWithArgs.translate(1, 2.0);
	GenericConcreteCreator<BaseTranslatorLiskovWithArgs, Translator2LiskovWithArgs, int, double> Translator2LiskovGenericWithArgs;
	Translator2LiskovGenericWithArgs.translate(3, 4.5);
	cout << "****************" << endl << endl << endl;

	return 0;
}