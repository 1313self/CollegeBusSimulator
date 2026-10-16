#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>
#include "Route.h"
#include "Schedule.h"
#include "Simulator.h"
#include "History.h"
using namespace std;

class Menu {
private:
    static const int ROUTES = 4;
    Route*     routes[ROUTES];
    Schedule   schedule;
    Simulator  simulator;
    TripHistory history;

    int readInt(const string& prompt, int low, int high) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= low && value <= high) return value;
            cout << "  Invalid input. Enter " << low << " to " << high << ".\n";
            if (cin.eof()) exit(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void showRoutes() {
        cout << "\n--- ROUTES (stops stored as linked list) ---\n";
        for (int i = 0; i < ROUTES; i++) {
            cout << " " << i + 1 << ". ";
            routes[i]->display();
        }
        cout << " Bus capacity: " << Bus::capacity() << " | Buses per route: 3\n";
    }

    void simulateOneTrip() {
        cout << "\nChoose route:\n";
        for (int i = 0; i < ROUTES; i++)
            cout << " " << i + 1 << ". " << routes[i]->getDestination() << endl;
        int r   = readInt("Route (1-4): ", 1, ROUTES) - 1;
        int dir = readInt("1 = College -> Stop (departure), 2 = Stop -> College (arrival): ", 1, 2);

        if (dir == 1) {
            int bus = readInt("Bus number (1-3): ", 1, 3);
            history.push(simulator.runDeparture(*routes[r], bus, Schedule::departureHour(bus)));
        } else {
            int bus = readInt("Bus number (1-2): ", 1, 2);
            history.push(simulator.runArrival(*routes[r], bus, Schedule::arrivalHour(bus)));
        }
    }

    void simulateFullDay() {
        TripQueue queue;
        schedule.buildDay(queue, ROUTES);
        cout << "\n########## FULL DAY SIMULATION (" << queue.size() << " trips) ##########\n";

        int trips = 0, students = 0;
        while (!queue.isEmpty()) {
            TripEvent e = queue.dequeue();
            TripRecord rec = e.isDeparture
                ? simulator.runDeparture(*routes[e.routeIndex], e.busNo, e.hour)
                : simulator.runArrival(*routes[e.routeIndex], e.busNo, e.hour);
            history.push(rec);
            trips++;
            students += rec.studentsCarried;
        }
        cout << "\n########## DAY COMPLETE: " << trips << " trips, "
             << students << " students carried ##########\n";
    }

public:
    Menu() {
        const char* names[ROUTES] = {"Raipur", "Doiwala", "Kargi Chowk", "Rajpur Road"};
        for (int i = 0; i < ROUTES; i++) routes[i] = new Route(names[i]);
    }

    ~Menu() { for (int i = 0; i < ROUTES; i++) delete routes[i]; }

    void run() {
        int choice;
        do {
            cout << "\n=========================================\n"
                 << "        COLLEGE BUS SIMULATOR\n"
                 << "=========================================\n"
                 << " 1. Show routes\n"
                 << " 2. Show bus timetable\n"
                 << " 3. Simulate one trip\n"
                 << " 4. Simulate full day (all buses)\n"
                 << " 5. View trip history\n"
                 << " 0. Exit\n";
            choice = readInt("Enter choice: ", 0, 5);

            switch (choice) {
                case 1: showRoutes();          break;
                case 2: schedule.showTimetable(); break;
                case 3: simulateOneTrip();     break;
                case 4: simulateFullDay();     break;
                case 5: history.display();     break;
                case 0: cout << "\nThank you!\n"; break;
            }
        } while (choice != 0);
    }
};

#endif
