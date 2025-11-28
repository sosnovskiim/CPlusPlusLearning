#include "tasks_4.h"
#include <iostream>
#include <string>

static class Serializer {
public:
    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const std::string&) = 0;
    virtual void EndArray() = 0;
    virtual ~Serializer() = default;
};

static class JsonSerializer : public Serializer {
private:
    bool firstItem = true;

public:
    void BeginArray() override {
        if (!firstItem) {
            std::cout << ",";
        }
        std::cout << "[";
        firstItem = true;
    }

    void AddArrayItem(const std::string& item) override {
        if (!firstItem) {
            std::cout << ",";
        }
        std::cout << "\"" << item << "\"";
        firstItem = false;
    }

    void EndArray() override {
        std::cout << "]";
        firstItem = false;
    }

    ~JsonSerializer() override = default;
};

void task_414() {
    Serializer* serializer1 = new JsonSerializer();
    serializer1->BeginArray();
    serializer1->EndArray();
    std::cout << std::endl;

    Serializer* serializer2 = new JsonSerializer();
    serializer2->BeginArray();
    serializer2->AddArrayItem("string");
    serializer2->EndArray();
    std::cout << std::endl;

    Serializer* serializer3 = new JsonSerializer();
    serializer3->BeginArray();
    serializer3->AddArrayItem("first");
    serializer3->AddArrayItem("second");
    serializer3->EndArray();
    std::cout << std::endl;

    Serializer* serializer4 = new JsonSerializer();
    serializer4->BeginArray();
    serializer4->BeginArray();
    serializer4->EndArray();
    serializer4->EndArray();
    std::cout << std::endl;
}
