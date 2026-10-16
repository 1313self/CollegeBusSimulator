#ifndef BUS_H
#define BUS_H

#include <string>
using namespace std;

class Bus {
private:
    int    busNo;
    string destination;
    int    passengers;

public:
    static int capacity() { return 50; }

    Bus(int no, string dest) : busNo(no), destination(dest), passengers(0) {}

    int    getBusNo() const      { return busNo; }
    int    getPassengers() const { return passengers; }
    int    seatsLeft() const     { return capacity() - passengers; }
    string getName() const       { return destination + " Bus " + to_string(busNo); }

    int board(int n) {
        if (n < 0) n = 0;
        if (n > seatsLeft()) n = seatsLeft();
        passengers += n;
        return n;
    }

    int alight(int n) {
        if (n < 0) n = 0;
        if (n > passengers) n = passengers;
        passengers -= n;
        return n;
    }

    int alightAll() {
        int n = passengers;
        passengers = 0;
        return n;
    }
};

#endif
