#include <memory>
#include <AuxiliarClassesLiskov.hpp>

#pragma once

using namespace std; 
/**
 * It is the base class for concrete creators. In this example it will
 * Note that it is an abstract class.
 * Note that its responsibility is just to translate.
 */
class Creator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:
  virtual ~Creator(){};
  virtual unique_ptr<BaseTranslatorLiskov> FactoryMethod() const = 0;


  void translate() const {
    // Call the factory method to create a Tranlator object.
    // Which one? It will depend on the concrete creator.
    auto translator{move(this->FactoryMethod())};
    // Use it to translate
    translator->translate();
  }
};