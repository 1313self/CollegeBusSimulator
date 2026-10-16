#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "Simulator.h"
using namespace std;

class TripHistory {
private:
    struct SNode {
        TripRecord data;
        SNode*     next;
    };
    SNode* top;
    int    count;

public:
    TripHistory() : top(nullptr), count(0) {}
    ~TripHistory() { while (!isEmpty()) pop(); }
    TripHistory(const TripHistory&) = delete;
    TripHistory& operator=(const TripHistory&) = delete;

    bool isEmpty() const { return top == nullptr; }
    int  size() const    { return count; }

    void push(const TripRecord& r) {
        top = new SNode{r, top};
        count++;
    }

    void pop() {
        if (isEmpty()) return;
        SNode* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    void display() const {
        if (isEmpty()) { cout << "\nNo trips simulated yet.\n"; return; }
        cout << "\n--- TRIP HISTORY (latest first) ---\n";
        int n = count;
        for (SNode* cur = top; cur != nullptr; cur = cur->next, n--) {
            cout << " #" << n << "  " << cur->data.timeText << " | "
                 << cur->data.busName << " | " << cur->data.path
                 << " | students: " << cur->data.studentsCarried << endl;
        }
    }
};

#endif
