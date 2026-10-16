#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
using namespace std;

struct StopNode {
    string    name;
    StopNode* next;
    StopNode* prev;
    StopNode(string n) : name(n), next(nullptr), prev(nullptr) {}
};

class Route {
private:
    string    destination;
    StopNode* head;
    StopNode* tail;

public:
    Route(string dest) : destination(dest), head(nullptr), tail(nullptr) {
        addStop("College");
        addStop("Halt 1");
        addStop("Halt 2");
        addStop(dest);
    }

    ~Route() {
        while (head != nullptr) {
            StopNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Route(const Route&) = delete;
    Route& operator=(const Route&) = delete;

    void addStop(string name) {
        StopNode* node = new StopNode(name);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    StopNode* getHead() const        { return head; }
    StopNode* getTail() const        { return tail; }
    string    getDestination() const { return destination; }

    int stopCount() const {
        int count = 0;
        for (StopNode* cur = head; cur != nullptr; cur = cur->next) count++;
        return count;
    }

    void display() const {
        for (StopNode* cur = head; cur != nullptr; cur = cur->next) {
            cout << cur->name;
            if (cur->next != nullptr) cout << " -> ";
        }
        cout << endl;
    }
};

#endif
