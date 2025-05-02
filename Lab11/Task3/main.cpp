#include <iostream>
#include <string>

using namespace std;

class ITransport {
public:
    virtual void deliver() = 0;
    virtual ~ITransport() {}
};

class Truck : public ITransport {
    string address;
public:
    Truck(const string& addr) : address(addr) {}
    void deliver() override {
        cout << "Delivering by land to address: " << address << endl;
    }
};

class Ship : public ITransport {
    string country;
public:
    Ship(const string& c) : country(c) {}
    void deliver() override {
        cout << "Delivering by sea to country: " << country << endl;
    }
};

class Plane : public ITransport {
    string country;
public:
    Plane(const string& c) : country(c) {}
    void deliver() override {
        cout << "Delivering by air to country: " << country << endl;
    }
};

class TransportFactory {
public:
    static ITransport* getTransport(const string& mode, const string& destination) {
        if (mode == "truck") {
            return new Truck(destination);
        } else if (mode == "ship") {
            return new Ship(destination);
        } else if (mode == "plane") {
            return new Plane(destination);
        } else {
            return nullptr;
        }
    }
};

int main() {
    ITransport* t1 = TransportFactory::getTransport("truck", "221B Baker St");
    if (t1) { t1->deliver(); delete t1; }

    ITransport* t2 = TransportFactory::getTransport("ship", "Canada");
    if (t2) { t2->deliver(); delete t2; }

    ITransport* t3 = TransportFactory::getTransport("plane", "Japan");
    if (t3) { t3->deliver(); delete t3; }

    return 0;
}