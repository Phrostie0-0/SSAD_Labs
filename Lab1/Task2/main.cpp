#include <iostream>

using namespace std;

void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y;
    cin >> x >> y;

    cout << "Before swap by pointer: x = " << x << ", y = " << y << endl;
    swapByPointer(&x, &y);
    cout << "After swap by pointer: x = " << x << ", y = " << y << endl;

    swapByReference(x, y);
    cout << "After swap by reference: x = " << x << ", y = " << y << endl;
}