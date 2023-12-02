#include <memory>
#include <AuxiliarClassesLiskov.hpp>

#pragma once

using namespace std; 
/**
 * It is the base class for concrete creators. In this example it will
 * Note that it is an abstract class.
 * Note that its responsibility is just to translate.
 */
class Creator 
{
 public:
  virtual ~Creator() = default;
  virtual unique_ptr<BaseTranslatorLiskov> FactoryMethod() const = 0; // it is a creator
              // it may be better to use a name like createTranslator() instead of FactoryMethod()
              // but I have put this name to ilustrate that it is a factory method creator

  void translate() const {
    // Call the factory method to create a Tranlator object.
    // Which one? It will depend on the concrete creator.
    auto translator{move(this->FactoryMethod())};
    
    translator->translate();
  }
};