#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Forward declaration
class SmartHouseMediator;

class Device {
public:
    virtual void sendMessage(const string& message) = 0;
    virtual void receiveMessage(const string& message) = 0;
    virtual void setMediator(SmartHouseMediator* mediator) = 0;
    virtual ~Device() = default;
};

class SmartHouseMediator {
private:
    vector<Device*> devices;
public:
    void addDevice(Device* device) {
        devices.push_back(device);
        device->setMediator(this);
    }

    void mediate(Device* sender, const string& message) {
        for (Device* dev : devices) {
            if (dev != sender) {
                dev->receiveMessage(message);
            }
        }
    }
};

class MotionSensor : public Device {
private:
    SmartHouseMediator* mediator = nullptr;

public:
    void sendMessage(const string& message) override {
        if (mediator) {
            cout << "[MotionSensor] sending message: " << message << "\n";
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "MotionSensor received a \"" << message
             << "\", the owner will be notified that they expect a visitor\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        mediator = med;
    }
};

class TemperatureSensor : public Device {
private:
    SmartHouseMediator* mediator = nullptr;
public:
    void sendMessage(const string& message) override {
        if (mediator) {
            cout << "[TemperatureSensor] sending message: " << message << "\n";
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "TemperatureSensor received a \"" << message
             << "\", the room temperature will be adjusted\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        mediator = med;
    }
};


int main() {
    SmartHouseMediator mediator;
    MotionSensor motion;
    TemperatureSensor temp;

    // Register devices with the mediator
    mediator.addDevice(&motion);
    mediator.addDevice(&temp);

    // Simulate events
    motion.sendMessage("Motion detected");
    cout << endl;
    temp.sendMessage("High temperature detected");

    return 0;
}