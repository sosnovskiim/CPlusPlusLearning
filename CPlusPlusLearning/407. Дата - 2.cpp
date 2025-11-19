#include "tasks_4.h"
#include <windows.h>
#include <iostream>
#include <stdexcept>

static class Date {
private:
    int days;

    bool isValidDate(int d, int m, int y) const {
        if (y < 1970 || y > 2099) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1) return false;

        int daysInMonth = getDaysInMonth(m, y);
        return d <= daysInMonth;
    }

    static int getDaysInMonth(int m, int y) {
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

    static bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int dateToDays(int day, int month, int year) {
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

    static void daysToDate(int days, int& day, int& month, int& year) {
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

    int getDay() const {
        int d, m, y;
        daysToDate(days, d, m, y);
        return d;
    }

    int getMonth() const {
        int d, m, y;
        daysToDate(days, d, m, y);
        return m;
    }

    int getYear() const {
        int d, m, y;
        daysToDate(days, d, m, y);
        return y;
    }

public:
    Date(int d = 1, int m = 1, int y = 1970) {
        if (isValidDate(d, m, y)) {
            days = dateToDays(d, m, y);
        }
        else {
            days = 0;
        }
    }

    int GetDay() const { return getDay(); }
    int GetMonth() const { return getMonth(); }
    int GetYear() const { return getYear(); }

    Date operator+(int daysToAdd) const {
        if (daysToAdd < 0) {
            return *this - (-daysToAdd);
        }

        Date result;
        result.days = days + daysToAdd;

        int day, month, year;
        daysToDate(result.days, day, month, year);
        if (year > 2099) {
            return Date(31, 12, 2099);
        }

        return result;
    }

    Date operator-(int daysToSubtract) const {
        if (daysToSubtract < 0) {
            return *this + (-daysToSubtract);
        }

        Date result;
        result.days = days - daysToSubtract;
        if (result.days < 0) {
            result.days = 0;
        }
        return result;
    }

    int operator-(const Date& other) const {
        return this->days - other.days;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear();
        return os;
    }
};

void task_407() {
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
