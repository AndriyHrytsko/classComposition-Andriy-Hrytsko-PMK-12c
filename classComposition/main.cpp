#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Talon {
private:
    string name;
    int score;
    string teacher;

public:
    Talon(string name, int score, string teacher) {
        this->name = name;
        this->score = score;
        this->teacher = teacher;
    }

    string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }

    string getTeacher() const {
        return teacher;
    }
};

class Student {
private:
    string name;
    string group;
    vector<Talon> talons;

public:
    Student(string name, string group) {
        this->name = name;
        this->group = group;
    }

    string getName() const {
        return name;
    }

    string getGroup() const {
        return group;
    }

    void addTalon(Talon talon) {
        talons.push_back(talon);
    }

    int getTalonCount() const {
        return talons.size();
    }

    vector<Talon> getTalons() const {
        return talons;
    }
};

int main() {
    // ç÷èòóâàííÿ äàíèõ ç ôàéëó
    ifstream file("students.txt");
    string line;
    vector<Student> students;
    while (getline(file, line)) {
        string name = line;
        string group;
        getline(file, group);
        Student student(name, group);
        while (getline(file, line)) {
            if (line.empty()) {
                break;
            }
            string name = line;
            int score;
            string teacher;
            getline(file, teacher);
            file >> score;
            file.ignore();
            Talon talon(name, score, teacher);
            student.addTalon(talon);
        }
        students.push_back(student);
        return 0;
    }
}

    // âèâåäåííÿ ñòóäåíò³â ç á³ëüøå í³æ îäíèì òàëîíîì ó Ôàéë1
    ofstream file1("students_with_multiple_talons.txt");
    for (const auto& student : students) {
        if (student.getTalonCount() > 1) {
            file1 << student.getName() << " (" << student.getGroup() << ")" << endl;
            for (const auto& talon : student.getTalons()) {
                file1 << "- " << talon.getName() << " (" << talon.getTeacher() << "): " << talon.getScore() << endl;
            }
            file1 << endl;
        }
    }
    file1.close();

    // çíàõîäæåííÿ ïð³çâèùà âèêëàäà÷à, ÿêèé ô³ãóðóº â íàéá³ëüø³é ê³ëüêîñò³ òàëîí³â
    map<string, int> teacherCount;
    for (const auto& student : students) {
        for (const auto& talon : student.getTalons()) {
            teacherCount[talon.getTeacher()]++;
        }
    }
    string mostFrequentTeacher;
    int maxCount = 0;
    for (const auto& pair : teacherCount) {
        if (pair.second > maxCount) {
            mostFrequentTeacher = pair.first;
            maxCount = pair.second;
        }
    }

    // âèâåäåííÿ ïð³çâèùà âèêëàäà÷à ó Ôàéë2
    ofstream file2;
        
