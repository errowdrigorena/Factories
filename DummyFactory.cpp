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

#include <boost/functional/factory.hpp>
#include <boost/functional/value_factory.hpp>

using namespace std;

//The intent of this program is to show how different implementations about how a
//factory may work
int main(int argc, char **argv) {
	cout << "Factories" << endl<< endl << endl;

	cout << "** No Factory **" << endl;
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

	cout << "** Factory Constexpr **" << endl;
	FactoryTempConstExpr myFactory;
	auto a = myFactory.createTranslator<Type1ToType2Translator>();
	a->translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory SFINAE **" << endl;
	FactorySFINAE myFactorySFINAE;
	auto translatorSfinae = myFactorySFINAE.createTranslator<Type5ToType6Translator>();
	translatorSfinae.translate();
	auto translatorSfinae2 = myFactorySFINAE.createTranslator<Type7ToType8Translator>();
	translatorSfinae2.translate();
	cout << "****************" << endl << endl << endl;

	cout << "** Factory Template Specialization **" << endl;
	FactoryTemplateSpecialization factoryTemplateSpecialization;
	auto translatorTemplateSpecializationFails = factoryTemplateSpecialization.createTranslator<Type1ToType2Translator>();
	auto translatorTemplateSpecialization5To6= factoryTemplateSpecialization.createTranslator<Type5ToType6Translator>();
	translatorTemplateSpecialization5To6->translate();
	auto translatorTemplateSpecialization7To8= factoryTemplateSpecialization.createTranslator<Type7ToType8Translator>();
	translatorTemplateSpecialization7To8->translate();
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

	return 0;
}
