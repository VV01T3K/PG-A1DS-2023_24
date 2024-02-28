// #include <iostream>

// #include "ExampleClass.h"

// int main() {
//     ExampleClass example(5);  // Create an instance of ExampleClass with
//     value 5

//     std::cout << "Value: " << example.getValue() << std::endl;

//     example.setValue(10);
//     std::cout << "New Value: " << example.getValue() << std::endl;

//     return 0;
// }

#include "Prostokat.h"

int main() {
    Prostokat prostokat(5.0, 10.0);  // Create an instance of Prostokat with
                                     // width 5.0 and height 10.0

    std::cout << "Width: " << prostokat.GetA() << std::endl;
    std::cout << "Height: " << prostokat.GetB() << std::endl;
    std::cout << "Area: " << prostokat.Pole() << std::endl;

    return 0;
}