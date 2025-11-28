#include "tasks_4.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

static struct ParticipantResults {
    std::string login;
    std::string team;
    std::map<std::string, int> scores;  // номер задачи -> баллы

    // ...

    ParticipantResults(const std::string& l, const std::string& te) : login(l), team(te) {
    }

    ParticipantResults(const ParticipantResults&) = delete;
    ParticipantResults& operator = (const ParticipantResults&) = delete;
};

static class Monitor {
private:
    using Ptr = ParticipantResults*;
    using ConstPtr = const ParticipantResults*;

    std::map<std::string, Ptr> byParticipant;
    std::map<std::string, std::vector<ConstPtr>> byTeam;
    std::vector<ConstPtr> allResults;

public:
    Monitor() = default;
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    ~Monitor() {
        for (auto& [login, ptr] : byParticipant) {
            delete ptr;
        }
    }

    Ptr RegisterParticipant(const std::string& login, const std::string& team) {
        if (byParticipant.contains(login)) {
            throw std::invalid_argument("Participant is already registered");
        }
        Ptr newParticipant = new ParticipantResults(login, team);
        byParticipant[login] = newParticipant;
        byTeam[team].push_back(newParticipant);
        allResults.push_back(newParticipant);
        return newParticipant;
    }

    Ptr GetParticipantResults(const std::string& login) {
        return byParticipant.at(login);
    }

    ConstPtr GetParticipantResults(const std::string& login) const {
        return byParticipant.at(login);
    }

    std::vector<ConstPtr> GetTeamResults(const std::string& team) const {
        return byTeam.at(team);
    }

    std::vector<ConstPtr> GetAllResults() const {
        return allResults;
    }
};

void task_415() {
    Monitor monitor;

    {
        auto ptr = monitor.RegisterParticipant("Ivanov Ivan", "201-1");
        ptr->scores["A"] = 10;
        ptr->scores["B"] = 8;
    }

    {
        auto ptr = monitor.RegisterParticipant("Petrov Petr", "201-2");
        ptr->scores["A"] = 5;
        ptr->scores["C"] = 10;
    }

    auto ptr = monitor.GetParticipantResults("Ivanov Ivan");
    ptr->scores["Q"] = 100;

    // тут может быть аналогичный вызов monitor.GetTeamResults(team)
    for (const auto& result : monitor.GetAllResults()) {
        std::cout << result->login << "\t" << result->team << "\t";
        for (const auto& [problemId, score] : result->scores) {
            std::cout << problemId << ": " << score << "\t";
        }
        std::cout << "\n";
    }
}
