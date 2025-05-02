#include <iostream>
#include <algorithm>
using namespace std;

class Box {
    unsigned int length;
    unsigned int width;
    unsigned int height;
public:
    Box() : length(0), width(0), height(0) {}
    Box(const Box& other) : length(other.length), width(other.width), height(other.height) {}
    Box(unsigned int l, unsigned int w, unsigned int h) : length(l), width(w), height(h) {}

    Box& operator=(const Box& other) {
        length = other.length;
        width  = other.width;
        height = other.height;
        return *this;
    }

    unsigned int getVolume() const {
        return length * width * height;
    }

    void scale(unsigned int s) {
        length *= s;
        width  *= s;
        height *= s;
    }

    bool isBigger(const Box& o) const {
        return getVolume() > o.getVolume();
    }

    bool isSmaller(const Box& o) const {
        return getVolume() < o.getVolume();
    }

    Box operator*(unsigned int s) const {
        return Box(length * s, width * s, height * s);
    }

    bool operator==(const Box& o) const {
        unsigned int a[3] = { length, width, height };
        unsigned int b[3] = { o.length, o.width, o.height };
        sort(a, a + 3);
        sort(b, b + 3);
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }
};

class Cube {
    unsigned int side;
public:
    Cube() : side(0) {}
    Cube(unsigned int s) : side(s) {}
    operator Box() const {
        return Box(side, side, side);
    }
};

int main() {
    Box b1;
    Box b2(2, 3, 4);
    Box b3 = b2;
    b1 = b3;

    cout << b2.getVolume() << endl;

    b2.scale(2);
    cout << b2.getVolume() << endl;

    cout << b2.isBigger(b3) << endl;
    cout << b3.isSmaller(b2) << endl;

    Box b4 = b3 * 3;
    cout << b4.getVolume() << endl;

    cout << (b3 == Box(2, 3, 4)) << endl;

    Cube c(5);
    Box b5 = c;
    cout << b5.getVolume() << endl;
}