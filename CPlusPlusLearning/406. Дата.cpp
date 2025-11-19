#include "tasks_4.h"
#include <windows.h>
#include <iostream>
#include <stdexcept>

static class Date {
private:
    int day, month, year;
    
    bool isValidDate(int d, int m, int y) const {
        if (y < 1970 || y > 2099) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1) return false;

        int daysInMonth = getDaysInMonth(m, y);
        return d <= daysInMonth;
    }

    int getDaysInMonth(int m, int y) const {
        switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(y) ? 29 : 28;
        default:
            return 0;
        }
    }

    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int toDays() const {
        int totalDays = 0;

        for (int y = 1970; y < year; y++) {
            totalDays += isLeapYear(y) ? 366 : 365;
        }

        for (int m = 1; m < month; m++) {
            totalDays += getDaysInMonth(m, year);
        }

        totalDays += day - 1;

        return totalDays;
    }

    void fromDays(int days) {
        int d = days;
        year = 1970;
        month = 1;
        day = 1;

        while (d >= (isLeapYear(year) ? 366 : 365)) {
            d -= isLeapYear(year) ? 366 : 365;
            year++;
        }

        while (d >= getDaysInMonth(month, year)) {
            d -= getDaysInMonth(month, year);
            month++;
        }

        day += d;
    }

public:
    Date(int d = 1, int m = 1, int y = 1970) {
        if (isValidDate(d, m, y)) {
            day = d;
            month = m;
            year = y;
        }
        else {
            day = 1;
            month = 1;
            year = 1970;
        }
    }

    int GetDay() const { return day; }
    int GetMonth() const { return month; }
    int GetYear() const { return year; }

    Date operator+(int days) const {
        if (days < 0) {
            return *this - (-days);
        }

        Date result = *this;
        int totalDays = toDays() + days;
        result.fromDays(totalDays);
        return result;
    }

    Date operator-(int days) const {
        if (days < 0) {
            return *this + (-days);
        }

        Date result = *this;
        int totalDays = toDays() - days;
        if (totalDays < 0) {
            return Date(1, 1, 1970);
        }
        result.fromDays(totalDays);
        return result;
    }

    int operator-(const Date& other) const {
        return this->toDays() - other.toDays();
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.day << "." << date.month << "." << date.year;
        return os;
    }
};

void task_406() {
    SetConsoleOutputCP(1251);

    std::cout << "Тест конструктора:" << std::endl;
    Date validDate(15, 5, 2023);
    Date invalidDate(32, 13, 2023);
    std::cout << "Корректная дата: " << validDate << std::endl;
    std::cout << "Некорректная дата: " << invalidDate << std::endl;

    std::cout << "\nТест геттеров:" << std::endl;
    std::cout << "День: " << validDate.GetDay() << std::endl;
    std::cout << "Месяц: " << validDate.GetMonth() << std::endl;
    std::cout << "Год: " << validDate.GetYear() << std::endl;

    std::cout << "\nТест оператора +:" << std::endl;
    Date date1(1, 1, 2023);
    Date date2 = date1 + 10;
    std::cout << date1 << " + 10 дней = " << date2 << std::endl;

    std::cout << "\nТест оператора - (с днями):" << std::endl;
    Date date3 = date2 - 5;
    std::cout << date2 << " - 5 дней = " << date3 << std::endl;

    std::cout << "\nТест оператора - (между датами):" << std::endl;
    Date date4(10, 1, 2023);
    Date date5(1, 1, 2023);
    int diff = date4 - date5;
    std::cout << date4 << " - " << date5 << " = " << diff << " дней" << std::endl;

    std::cout << "\nТест с високосным годом:" << std::endl;
    Date leapDate(28, 2, 2020);
    Date nextDay = leapDate + 1;
    std::cout << leapDate << " + 1 день = " << nextDay << std::endl;

    std::cout << "\nТест граничных значений:" << std::endl;
    Date minDate(1, 1, 1970);
    Date maxDate(31, 12, 2099);
    std::cout << "Минимальная дата: " << minDate << std::endl;
    std::cout << "Максимальная дата: " << maxDate << std::endl;

    std::cout << "\nТест большой разности:" << std::endl;
    Date start(1, 1, 1970);
    Date end(1, 1, 2000);
    int daysBetween = end - start;
    std::cout << "Дней между " << start << " и " << end << ": " << daysBetween << std::endl;
}
