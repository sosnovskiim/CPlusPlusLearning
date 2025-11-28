#include "tasks_4.h"
#include <iostream>
#include <memory>

static struct A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

static struct B : public A {
private:
    A a;

public:
    B() : A(42), a(17) {}
};

void task_425() {
    std::unique_ptr<A> ptr(new B);
    ptr->foo();
}
