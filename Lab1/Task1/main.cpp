#include <iostream>

using namespace std;

int main() {
    int totalSeconds;
    cin >> totalSeconds;

    int hours = totalSeconds / 3600;
    int rem = totalSeconds % 3600;
    int minutes = rem / 60;
    int seconds = rem % 60;
    cout << hours << ":" << minutes << ":" << seconds;
}