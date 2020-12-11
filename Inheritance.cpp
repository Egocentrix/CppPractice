// This is to toy around with multiple inheritance, 
// virtual functions and combining interfaces.

#include <memory>
#include <iostream>

// Two basic interface classes
class Foo
{
public:
    virtual void foo() = 0;
};

class Bar
{
public:
    virtual void bar() { std::cout << "Base-Bar" << std::endl; };
};

// Very cool combined object
class Both : public Foo, public Bar
{
public:
    virtual ~Both() = default;
    virtual void foo() override { std::cout << "Both-Foo" << std::endl; }
};

// This is what we are testing
class Derived : public Both
{

public:
    Derived(/* args */) {}
    ~Derived() { std::cout << "~Derived" << std::endl; }

    virtual void foo() override { std::cout << "Derived-Foo!" << std::endl; }
};

int main(int argc, char const *argv[])
{
    Both *D = new Derived;
    D->foo();

    delete D;

    // Yes, we can still call the base functions!
    std::unique_ptr<Both> D2 = std::make_unique<Derived>();
    D2->bar();
    D2->foo();

    return 0;
}
