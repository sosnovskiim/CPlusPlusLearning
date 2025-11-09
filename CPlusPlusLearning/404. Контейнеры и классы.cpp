#include "tasks_4.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

static class Ticket {

private:
    string number;

public:
    Ticket(const string& num = "") : number(num) {}

    const string& getNumber() const { return number; }

    bool startsWith(char digit) const {
        return !number.empty() && number[0] == digit;
    }

    void replaceFirstWithLast() {
        if (number.length() > 1) {
            char lastDigit = number.back();
            number[0] = lastDigit;
        }
    }

    friend ostream& operator<<(ostream& os, const Ticket& ticket) {
        os << ticket.number;
        return os;
    }
};

class TicketsList {

private:
    list<Ticket> tickets;

public:
    void addToFront(const Ticket& ticket) {
        tickets.push_front(ticket);
    }

    void removeTicketsStartingWith(char digit) {
        tickets.remove_if([digit](const Ticket& ticket) {
            return ticket.startsWith(digit);
        });
    }

    void printTickets() const {
        for (const auto& ticket : tickets) {
            cout << ticket << " ";
        }
        cout << endl;
    }
};

class TicketsVector {

private:
    vector<Ticket> tickets;

public:
    void addTicket(const Ticket& ticket) {
        tickets.push_back(ticket);
    }

    void replaceInEveryTicketN(int n) {
        if (n <= 0) return;
        for (size_t i = n - 1; i < tickets.size(); i += n) {
            tickets[i].replaceFirstWithLast();
        }
    }

    void removeLastTicket() {
        if (!tickets.empty()) {
            tickets.pop_back();
        }
    }

    void printTickets() const {
        for (const auto& ticket : tickets) {
            cout << ticket << " ";
        }
        cout << endl;
    }
};

void task_404() {
    SetConsoleOutputCP(1251);

    TicketsList ticketList;
    ticketList.addToFront(Ticket("123456"));
    ticketList.addToFront(Ticket("456789"));
    ticketList.addToFront(Ticket("112233"));
    ticketList.addToFront(Ticket("445566"));
    ticketList.addToFront(Ticket("789012"));

    cout << "Исходный список:" << endl;
    ticketList.printTickets();

    cout << "\nДобавляем билет '999999' в начало:" << endl;
    ticketList.addToFront(Ticket("999999"));
    ticketList.printTickets();

    cout << "\nУдаляем билеты, начинающиеся с '4':" << endl;
    ticketList.removeTicketsStartingWith('4');
    ticketList.printTickets();

    TicketsVector ticketVector;
    vector<string> tickets = { "123456", "234567", "345678", "456789", "567890", "678901" };
    for (const auto& number : tickets) {
        ticketVector.addTicket(Ticket(number));
    }

    cout << "\nИсходный вектор:" << endl;
    ticketVector.printTickets();

    cout << "\nЗаменяем первую цифру на последнюю в каждом 2-м билете:" << endl;
    ticketVector.replaceInEveryTicketN(2);
    ticketVector.printTickets();

    cout << "\nУдаляем последний билет:" << endl;
    ticketVector.removeLastTicket();
    ticketVector.printTickets();
}
