#include <Creator.hpp>

class Translator2Creator : public Creator {
 public:
  unique_ptr<BaseTranslatorLiskov> FactoryMethod() const override {
    return make_unique<Translator2Liskov>();
  }
};