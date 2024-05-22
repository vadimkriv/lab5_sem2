#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <functional>

class Student {
public:
    Student() = default;
    Student(const std::string& name, const std::string& group, const std::vector<int>& grades)
            : name(name), group(group), grades(grades) {}

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Group: " << student.group  << ", Marks: ";
        for (int grade : student.grades) {
            os << grade << " ";
        }
        return os;
    }

    bool operator<(const Student& other) const {
        return name < other.name;
    }

    bool operator==(const Student& other) const {
        return name == other.name && group == other.group && grades == other.grades;
    }

    float averageGrade() const {
        if (grades.empty()) return 0.0f;
        float sum = 0.0f;
        for (int grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }

    const std::string& getName() const { return name; }

private:
    std::string name;
    std::string group;
    std::vector<int> grades;
};

namespace std {
    template<>
    struct hash<Student> {
        std::size_t operator()(const Student& student) const {
            return std::hash<std::string>()(student.getName());
        }
    };
}

std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Student> students;
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return students;
    }
    std::string name, group;
    std::vector<int> grades(4);
    while (file >> name >> group >> grades[0] >> grades[1] >> grades[2] >> grades[3]) {
        students.emplace_back(name, group, grades);
    }
    file.close();
    return students;
}

void writeStudentsToFile(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    for (const auto& student : students) {
        file << student << std::endl;
    }
    file.close();
}

void writeSetToFile(const std::set<Student>& students, const std::string& filename) {
    std::ofstream file(filename, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    for (const auto& student : students) {
        file << student << std::endl;
    }
    file.close();
}

void writeUnorderedSetToFile(const std::unordered_set<Student>& students, const std::string& filename) {
    std::ofstream file(filename, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    for (const auto& student : students) {
        file << student << std::endl;
    }
    file.close();
}
void copyVectorToDeque(const std::vector<Student>& source, std::deque<Student>& destination) {
    destination.resize(source.size());
    std::copy(source.begin(), source.end(), destination.begin());
}
void sortStudentsByAverage(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.averageGrade() > b.averageGrade();
    });
}
int main() {
    std::vector<Student> students = readStudentsFromFile("input.txt");
    std::set<Student> studentSet(students.begin(), students.end());
    writeSetToFile(studentSet, "output.txt");
    std::unordered_set<Student> studentUnorderedSet(students.begin(), students.end());
    writeUnorderedSetToFile(studentUnorderedSet, "output.txt");
    sortStudentsByAverage(students);
    writeStudentsToFile(students, "output.txt");
    std::deque<Student> copiedStudents;
    copyVectorToDeque(students, copiedStudents);
    writeStudentsToFile(std::vector<Student>(copiedStudents.begin(), copiedStudents.end()), "output.txt");

    return 0;
}