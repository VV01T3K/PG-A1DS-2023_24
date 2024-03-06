#include <iostream>

#include "FiguryPlaskie/Kolo.h"
#include "FiguryPlaskie/Prostokat.h"
#include "FiguryPlaskie/Trojkat.h"

using namespace std;

int main() {
    Trojkat trojkatRownoboczny(3);

    cout << "Trojkat Rownoboczny: " << trojkatRownoboczny
         << ", Pole: " << trojkatRownoboczny.Pole()
         << ", Obwod: " << trojkatRownoboczny.Obwod() << endl;

    cout << endl;

    Kolo kolo(5);
    Prostokat prostokat(4, 6);
    Trojkat trojkat(3, 4, 5);

    cout << endl;

    cout << kolo << ", Pole: " << kolo.Pole() << ", Obwod : " << kolo.Obwod()
         << endl;
    cout << prostokat << ", Pole: " << prostokat.Pole()
         << ", Obwod: " << prostokat.Obwod() << endl;
    cout << trojkat << ", Pole: " << trojkat.Pole()
         << ", Obwod: " << trojkat.Obwod() << endl;

    FiguraPlaska* figury[3];

    cout << endl;

    figury[0] = new Kolo(7);
    figury[1] = new Prostokat(8, 9);
    figury[2] = new Trojkat(6, 8, 10);

    cout << endl;

    for (int i = 0; i < 3; i++) {
        cout << *figury[i] << endl;
    }

    cout << endl;

    for (int i = 0; i < 3; i++) {
        delete figury[i];
    }

    return 0;
}