#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <atomic>
#include <conio.h> // For _kbhit() and _getch()

using namespace std;

atomic<bool> running(true);

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void checkInput() {
    while (running) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q' || key == 'Q') {
                running = false;
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void displayClock() {
    while (running) {
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        tm* local_time = localtime(&current_time);
        
        clearScreen();
        
        cout << "¨X¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨[" << endl;
        cout << "¨U       DIGITAL CLOCK      ¨U" << endl;
        cout << "¨d¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨g" << endl;
        cout << "¨U                          ¨U" << endl;
        cout << "¨U         " 
             << setw(2) << setfill('0') << local_time->tm_hour << ":"
             << setw(2) << setfill('0') << local_time->tm_min << ":"
             << setw(2) << setfill('0') << local_time->tm_sec 
             << "         ¨U" << endl;
        cout << "¨U                          ¨U" << endl;
        cout << "¨^¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨a" << endl;
        cout << "Press 'Q' to quit" << endl;
        
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    thread inputThread(checkInput);
    thread clockThread(displayClock);
    
    clockThread.join();
    inputThread.join();
    
    cout << "Clock stopped. Goodbye!" << endl;
    return 0;
}
