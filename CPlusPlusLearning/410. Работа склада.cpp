#include "tasks_4.h"
#include <iostream>
#include <list>
#include <set>
#include <cstdint>
#include <unordered_map>

static class Stock {
private:
    struct WeightNumber {
        int w;
        size_t i;

        bool operator < (const WeightNumber& other) const {
            if (w == other.w) {
                return i > other.i;
            }
            return w < other.w;
        }
    };

    struct VolumeNumber {
        int v;
        size_t i;

        bool operator < (const VolumeNumber& other) const {
            if (v == other.v) {
                return i > other.i;
            }
            return v < other.v;
        }
    };

    struct Iterators {
        std::set<WeightNumber>::iterator byW;
        std::set<VolumeNumber>::iterator byV;
    };

    std::list<Iterators> boxes;
    std::set<WeightNumber> sortedByW;
    std::set<VolumeNumber> sortedByV;
    std::unordered_map<size_t, std::list<Iterators>::iterator> indexes;
    size_t current_index{ 0 };

public:
    void Add(int w, int v) {
        boxes.push_front({ sortedByW.insert({w, current_index}).first,
                            sortedByV.insert({v, current_index}).first });
        indexes.insert({ current_index, boxes.begin() });
        ++current_index;
    }

    int GetByW(int min_w) {
        const auto it = sortedByW.lower_bound({ min_w, current_index });
        if (it == sortedByW.end()) {
            return -1;
        }

        size_t res = it->i;
        sortedByW.erase(it);
        sortedByV.erase(indexes[res]->byV);
        boxes.erase(indexes[res]);
        indexes.erase(res);
        return res;
    }

    int GetByV(int min_v) {
        const auto it = sortedByV.lower_bound({ min_v, current_index });
        if (it == sortedByV.end()) {
            return -1;
        }

        size_t res = it->i;
        sortedByV.erase(it);
        sortedByW.erase(indexes[res]->byW);
        boxes.erase(indexes[res]);
        indexes.erase(res);
        return res;
    }
};


void task_410() {
    Stock stock;
    stock.Add(50, 30);
    stock.Add(30, 40);
    stock.Add(70, 20);
    stock.Add(50, 50);
    stock.Add(30, 25);

    int box1 = stock.GetByW(40);
    std::cout << box1 << std::endl;  // 3

    int box2 = stock.GetByV(35);
    std::cout << box2 << std::endl;  // 1

    int box3 = stock.GetByW(60);
    std::cout << box3 << std::endl;  // 2

    int box4 = stock.GetByW(100);
    std::cout << box4 << std::endl;  // -1

    int box5 = stock.GetByV(20);
    std::cout << box5 << std::endl;  // 4
}
