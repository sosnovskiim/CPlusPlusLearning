#include "tasks_4.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <windows.h>

using namespace std;

static class Sound {

private:
    int height;
    int duration;

public:
    Sound(int p = 0, int d = 0) : height(p), duration(d) {}

    int getHeight() const { return height; }
    int getDuration() const { return duration; }

    bool operator<(const Sound& other) const {
        if (height == other.height) {
            return duration < other.duration;
        }
        return height < other.height;
    }

    bool operator==(const Sound& other) const {
        return height == other.height && duration == other.duration;
    }

    friend ostream& operator<<(ostream& os, const Sound& sound) {
        os << "(h = " << sound.height << ", d = " << sound.duration << ")";
        return os;
    }
};

static class Melody {

private:
    vector<Sound> sounds;

public:
    void addSound(const Sound& sound) {
        sounds.push_back(sound);
    }

    void printMelody() const {
        for (size_t i = 0; i < sounds.size(); i++) {
            cout << i + 1 << ". " << sounds[i] << endl;
        }
    }

    void startWithHeight(int height) {
        auto it = find_if(sounds.begin(), sounds.end(),
            [height](const Sound& s) {
                return s.getHeight() == height;
            });
        if (it != sounds.end()) {
            rotate(sounds.begin(), it, sounds.end());
            cout << "Мелодия сдвинута к первой ноте с высотой " << height << endl;
        }
        else {
            cout << "Звук с высотой " << height << " не найден" << endl;
        }
    }

    bool containsSoundBinary(const Sound& sound) {
        vector<Sound> sorted = sounds;
        sort(sorted.begin(), sorted.end());
        return binary_search(sorted.begin(), sorted.end(), sound);
    }

    void removeDuplicateDurations() {
        vector<int> durations;
        vector<Sound> result;
        for (const auto& sound : sounds) {
            if (find(durations.begin(), durations.end(), sound.getDuration()) == durations.end()) {
                durations.push_back(sound.getDuration());
                result.push_back(sound);
            }
        }
        sounds = move(result);
    }

    const vector<Sound>& getSounds() const { return sounds; }
};

void task_405() {
    SetConsoleOutputCP(1251);

    Melody melody;
    melody.addSound(Sound(1, 5));
    melody.addSound(Sound(2, 5));
    melody.addSound(Sound(3, 5));
    melody.addSound(Sound(4, 2));
    melody.addSound(Sound(5, 5));
    melody.addSound(Sound(6, 2));
    melody.addSound(Sound(7, 5));
    melody.addSound(Sound(1, 3));
    melody.addSound(Sound(2, 5));

    cout << "Исходная мелодия:" << endl;
    melody.printMelody();

    cout << "\nПервый звук заданной высоты:" << endl;
    melody.startWithHeight(2);
    melody.printMelody();

    cout << "\nБинарный поиск:" << endl;
    Sound searchSound(7, 5);
    if (melody.containsSoundBinary(searchSound)) {
        cout << "Звук " << searchSound << " найден в мелодии" << endl;
    }
    else {
        cout << "Звук " << searchSound << " не найден в мелодии" << endl;
    }

    cout << "\nМелодия с дубликатами длительностей:" << endl;
    melody.printMelody();
    melody.removeDuplicateDurations();
    cout << "\nМелодия без дупликатов длительностей:" << endl;
    melody.printMelody();
}
