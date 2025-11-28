#include "tasks_5.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <optional>
#include <map>
#include <memory>

using namespace std;

template <typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::map<Key1, std::shared_ptr<Value>> primary_map;
    std::map<Key2, std::shared_ptr<Value>> secondary_map;

public:
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value) {
        if (!key1.has_value() && !key2.has_value()) {
            throw std::invalid_argument("Both keys are empty");
        }

        if (key1.has_value() && primary_map.find(*key1) != primary_map.end()) {
            throw std::invalid_argument("Primary key already exists");
        }
        if (key2.has_value() && secondary_map.find(*key2) != secondary_map.end()) {
            throw std::invalid_argument("Secondary key already exists");
        }

        auto value_ptr = std::make_shared<Value>(value);

        if (key1.has_value()) {
            primary_map[*key1] = value_ptr;
        }
        if (key2.has_value()) {
            secondary_map[*key2] = value_ptr;
        }
    }

    Value& GetByPrimaryKey(const Key1& key) {
        auto it = primary_map.find(key);
        if (it == primary_map.end()) {
            throw std::out_of_range("Primary key not found");
        }
        return *(it->second);
    }

    const Value& GetByPrimaryKey(const Key1& key) const {
        auto it = primary_map.find(key);
        if (it == primary_map.end()) {
            throw std::out_of_range("Primary key not found");
        }
        return *(it->second);
    }

    Value& GetBySecondaryKey(const Key2& key) {
        auto it = secondary_map.find(key);
        if (it == secondary_map.end()) {
            throw std::out_of_range("Secondary key not found");
        }
        return *(it->second);
    }

    const Value& GetBySecondaryKey(const Key2& key) const {
        auto it = secondary_map.find(key);
        if (it == secondary_map.end()) {
            throw std::out_of_range("Secondary key not found");
        }
        return *(it->second);
    }
};

static struct Student {
    string Surname, Name;
};

static ostream& operator << (ostream& out, const Student& s) {
    return out << s.Surname << " " << s.Name;
}

void task_506() {
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, { "Ivanov", "Ivan" });
    bimap.Insert({}, "cshse-ami-512", { "Petrov", "Petr" });
    bimap.Insert(13, "cshse-ami-999", { "Fedorov", "Fedor" });

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    bimap.GetByPrimaryKey(13).Name = "Oleg";

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
}
