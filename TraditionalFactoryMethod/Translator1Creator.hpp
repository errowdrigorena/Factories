#include <Creator.hpp>

class Translator1Creator : public Creator {
 public:
  unique_ptr<BaseTranslatorLiskov> FactoryMethod() const override {
    return make_unique<Translator1Liskov>();
  }
};