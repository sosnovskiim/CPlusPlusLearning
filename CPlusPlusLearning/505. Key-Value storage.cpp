#include "tasks_5.h"
#include <iostream>
#include <string>
#include <unordered_map>

template <typename Key, typename Value>
class KeyValueStorage {
private:
    std::unordered_map<Key, Value> data;

public:
    void Insert(const Key& key, const Value& value) {
        data[key] = value;
    }

    void Remove(const Key& key) {
        data.erase(key);
    }

    bool Find(const Key& key, Value* const value = nullptr) const;
};

template <typename Key, typename Value>
bool KeyValueStorage<Key, Value>::Find(const Key& key, Value* const value) const {
    auto it = data.find(key);
    if (it != data.end()) {
        if (value != nullptr) {
            *value = it->second;
        }
        return true;
    }
    return false;
}

void task_505() {
    KeyValueStorage<std::string, int> kv;
    kv.Insert("hello", 42);
    kv.Insert("bye", -13);
    int value = 123;
    std::cout << kv.Find("wrong", &value) << std::endl;  // должно вернуться false
    std::cout << value << std::endl;  // а value не должен меняться
    std::cout << kv.Find("bye", &value) << std::endl;  // должно вернуться true
    std::cout << value << std::endl;  // в value должно быть -13
    std::cout << kv.Find("hello", nullptr) << std::endl;  // должно вернуться true
}
