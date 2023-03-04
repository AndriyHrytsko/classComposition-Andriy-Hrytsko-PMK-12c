#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Talon {
public:
    Talon(const string& subj, int score, const string& teacher)
        : subj_(subj), score_(score), teacher_(teacher) {}

    const string& GetSubj() const { return subj_; }
    int GetScore() const { return score_; }
    const string& GetTeacher() const { return teacher_; }

private:
    string subj_;
    int score_;
    string teacher_;
};

class Student {
public:
    Student(const string& name, const string& group)
        : name_(name), group_(group) {}

    void AddTalon(const Talon& talon) {
        talons_.push_back(talon);
    }

    int GetTalonCount() const {
        return talons_.size();
    }

    const Talon& GetTalon(int index) const {
        return talons_[index];
    }

    const string& GetName() const { return name_; }
    const string& GetGroup() const { return group_; }

private:
    string name_;
    string group_;
    vector<Talon> talons_;
};

int main() {
    // Відкриття файлу для зчитування даних про студентів
    ifstream in("students.txt");
    if (!in) {
        cout << "Can't open students.txt" << endl;
        return 1;
    }
    return 0;
}
    vector<Student> students;

    // Зчитування даних про студентів
    while (in) {
        string name, group;
        cin >> name >> group;

        Student student(name, group);

        // Зчитування даних про талони студента
        int talonCount;
        cin >> talonCount;

        for (int i = 0; i < talonCount; ++i) {
            string subj, teacher;
            int score;
            cin >> subj >> score >> teacher;

            student.AddTalon(Talon(subj, score, teacher));
        }

        students.push_back(student);
    }

    // Відкриття файлу для запису списку студентів з більше ніж одним талоном
    ofstream out1("students_with_multiple_talons.txt");
    if (!out1) {
        cout << "Can't open students_with_multiple_talons.txt" << endl;
        return 1;
    }

    // Виведення списку студентів з більше ніж одним талоном
    for (const auto& student : students) {
        if (student.GetTalonCount() > 1) {
            out1 << student.GetName() << " " << student.GetGroup() << " ";

            for (int i = 0; i < student.GetTalonCount(); ++i) {
                const Talon& talon = student.GetTalon(i);
                out1 << talon.GetSubj() << " " << talon.GetScore() << " " << talon.GetTeacher() << " ";
            }

            out1 << endl;
        }
    }
