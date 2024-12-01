#include <iostream>

class Base1 {
public:
    virtual void func() { std::cout << "Base1 func\n"; }
    virtual ~Base1() = default;
};

class Base2 {
public:
    virtual void func() { std::cout << "Base2 func\n"; }
    virtual ~Base2() = default;
};

class Derived : public Base1, public Base2 {
public:
    // 使用作用域限定符重写 Base1 和 Base2 的 func
    void func() override { std::cout << "Derived override func\n"; }
    ~Derived() override = default;
};

int main () {
    Base1 *b1 = new Derived();
    b1->func();
    Base2 *b2 = new Derived();
    b2->func();
    delete b1;
    delete b2;
    Derived d;
    d.func();
}
