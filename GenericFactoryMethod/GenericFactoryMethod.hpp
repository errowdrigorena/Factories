#include <memory>

// To understand this, please take a look at TraditionalFactoryMethod whole directory
template<class Base, typename... Args>
class GenericCreator 
{
 public:
  virtual unique_ptr<Base> Create() const = 0;

  void translate(Args&&... args) const 
  {
    auto translator{move(this->Create())};
    
    translator->translate(forward<Args>(args)...);
  }
};

template<class Base, class Derived, typename... Args>
class GenericConcreteCreator : public GenericCreator<Base, Args...> 
{
public:
  GenericConcreteCreator()
  {
      if constexpr (!is_base_of_v<Base, Derived>)
      {
        static_assert( AlwaysFalse<Derived>::value, "this Translator has wrong Base/Derived types");
      }    
  }

  unique_ptr<Base> Create() const override 
  {
    return make_unique<Derived>();
  }
};

