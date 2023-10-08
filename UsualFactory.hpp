#include <memory>
#include <iostream>
#include <unordered_map>

#include <AuxiliarClasses.hpp>


using namespace std;

class factoryUsual
{
public:
	shared_ptr<BaseTranslator> createTranslator(TranslatorTypes type) //even more Usual usign Strings instead of an enum class
	{
		return translatorMap.at(type); //not capture the exception just to simplify the code
	}
private:
	const unordered_map<TranslatorTypes, shared_ptr<BaseTranslator>> translatorMap{
		{TranslatorTypes::Translator1, make_shared<Translator1>()},
		{TranslatorTypes::Translator2, make_shared<Translator2>()}
	};
};
