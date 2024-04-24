#include <iostream>
#include "src/MySharedPtr.h"

class Example {
public:
    int value;

    explicit Example(int value) : value(value) {
        std::cout << "Example created with value " << value << std::endl;
    }

    ~Example() {
        std::cout << "Example destroyed with value " << value << std::endl;
    }
};

void calculate(MySharedPtr<Example> copyPtr) {
    copyPtr->value = 50;
    std::cout << "Inside the method, the count is: " << copyPtr.getSize() << std::endl;
    std::cout << "Inside the method, the value is: " << copyPtr->value << std::endl;
}

int main() {
    MySharedPtr<Example> ptr1(new Example(42));

    std::cout << "Before the method, the count is: " << ptr1.getSize() << std::endl;
    std::cout << "Before the method, the value is: " << ptr1->value << std::endl;

    calculate(ptr1);
    MySharedPtr<Example> ptr2 = ptr1;
    calculate(ptr1);
    calculate(std::move(ptr1));

    ptr1 = std::move(ptr2);

    std::cout << "Outside the method, the count is: " << ptr1.getSize() << std::endl;
    std::cout << "Outside the method, the value is: " << ptr1->value << std::endl;

    (*ptr1).value = 100;

    std::cout << "Outside the method, the count is: " << ptr1.getSize() << std::endl;
    std::cout << "Outside the method, the value is: " << ptr1->value << std::endl;

    return 0;
}