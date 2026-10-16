#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Bus.h"
#include "Route.h"
#include "Schedule.h"
using namespace std;

struct TripRecord {
    string busName;
    string path;
    string timeText;
    bool   isDeparture;
    int    studentsCarried;
};

class Simulator {
private:
    int randomBetween(int low, int high) {
        if (high < low) return low;
        return low + rand() % (high - low + 1);
    }

public:
    Simulator() { srand((unsigned)time(nullptr)); }

    TripRecord runDeparture(Route& route, int busNo, int hour) {
        Bus bus(busNo, route.getDestination());
        cout << "\n=== " << bus.getName() << " | DEPARTS College at "
             << Schedule::timeText(hour) << " ===\n";

        StopNode* stop = route.getHead();
        int start = bus.board(randomBetween(30, 50));
        cout << "  " << stop->name << ": " << start << " students boarded"
             << " | on bus: " << bus.getPassengers() << endl;

        stop = stop->next;
        while (stop != nullptr) {
            if (stop->next == nullptr) {
                int off = bus.alightAll();
                cout << "  " << stop->name << ": " << off
                     << " students got off (ALL) | on bus: 0" << endl;
            } else {
                int off = bus.alight(randomBetween(1, bus.getPassengers() / 2));
                cout << "  " << stop->name << ": " << off
                     << " students got off | on bus: " << bus.getPassengers() << endl;
            }
            stop = stop->next;
        }
        cout << "  Trip completed. Bus is empty.\n";

        return {bus.getName(), "College -> " + route.getDestination(),
                Schedule::timeText(hour), true, start};
    }

    TripRecord runArrival(Route& route, int busNo, int hour) {
        Bus bus(busNo, route.getDestination());
        cout << "\n=== " << bus.getName() << " | ARRIVES College at "
             << Schedule::timeText(hour) << " ===\n";

        StopNode* stop = route.getTail();
        int total = 0;
        while (stop->prev != nullptr) {
            int got = bus.board(randomBetween(5, 20));
            total += got;
            cout << "  " << stop->name << ": " << got << " students boarded"
                 << " | on bus: " << bus.getPassengers()
                 << " | seats left: " << bus.seatsLeft() << endl;
            stop = stop->prev;
        }
        int off = bus.alightAll();
        cout << "  " << stop->name << ": " << off
             << " students got off (ALL) | on bus: 0\n";
        cout << "  Trip completed. Bus reached college.\n";

        return {bus.getName(), route.getDestination() + " -> College",
                Schedule::timeText(hour), false, total};
    }
};

#endif
