/*
 * File: Gradebook.cpp
 * -------------------
 * CS106L - Assignment: Types and Structs
 * This program reads a file of student grades, calculates final scores,
 * and identifies the top-performing student.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// TODO 1: Define the Student struct.
// It should contain three fields:
// - A string for the first name
// - A string for the last name
// - A double for the final score
struct Student {
    // your code here
    string firstName;
    string lastName;
    double finalScore;
};

/*
 * Function: processGrades
 * Usage: vector<Student> students = processGrades(inFile);
 * --------------------------------------------------------
 * Reads student grade data from the provided input file stream.
 * For each student, it calculates a final weighted score and creates
 * a Student struct. It returns a vector of all Student structs.
 */
vector<Student> processGrades(ifstream& inFile) {
    vector<Student> students;
    string line;

    // TODO 2: Read the file line by line using getline.
    // For each line, you'll need to:
    // a. Create a stringstream from the line.
    // b. Declare variables for last name, first name, and the three scores.
    // c. Use getline with a comma delimiter to parse the stringstream.
    //    Hint: getline(ss, field, ',');
    // d. The scores will be read as strings, so you'll need to convert them to integers.
    //    Use the `stoi()` function (string to integer).
    // e. Calculate the final score (double).
    // f. Create a Student struct and add it to the `students` vector.
    //    Use modern uniform initialization, e.g., students.push_back({fname, lname, score});

    while (getline(inFile, line)) {
        stringstream ss(line);
        string firstName, lastName, score1, score2, score3;
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, score1, ',');
        getline(ss, score2, ',');
        getline(ss, score3, ',');

        double totalGrade = 0.2 * stoi(score1) + 0.3 * stoi(score2) + 0.5 * stoi(score3);

        Student curStudent{firstName, lastName, totalGrade};
        students.push_back(curStudent);
    }
    
    return students;
}


/*
 * Function: findTopStudent
 * Usage: Student top = findTopStudent(students);
 * ------------------------------------------------
 * Takes a vector of Student structs and returns the one with the highest score.
 * If the vector is empty, it should return a default-constructed Student.
 */
Student findTopStudent(const vector<Student>& students) {
    if (students.empty()) {
        return {}; // Return a default-initialized Student
    }

    // TODO 3: Find the student with the highest score.
    // a. Initialize a variable `topStudent` with the first student in the vector.
    // b. Loop through the rest of the students (starting from the second one).
    //    Use a modern range-based for loop. Remember the best practice: `const auto&`.
    // c. If you find a student with a higher score, update `topStudent`.
    
    Student topStudent = students[0]; // Placeholder
    double topScore = topStudent.finalScore;
    for (const auto& student : students) {
        if (student.finalScore > topScore) {
            topScore = student.finalScore;
            topStudent = student;
        }
    }
    return topStudent;
}


// --- Main Program ---
// You don't need to change this part.
int main() {
    // Create a dummy grades file
    ofstream outFile("grades.txt");
    outFile << "Smith,John,85,90,95\n";
    outFile << "Doe,Jane,92,88,94\n";
    outFile << "Garcia,Carlos,78,85,80\n";
    outFile.close();

    ifstream inFile("grades.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open grades.txt" << endl;
        return 1;
    }

    vector<Student> students = processGrades(inFile);
    inFile.close();

    if (students.empty()) {
        cout << "No student data processed." << endl;
    } else {
        Student top = findTopStudent(students);
        cout << "Top performing student: " << top.firstName << " " << top.lastName
             << " with a score of " << top.finalScore << endl;
    }

    return 0;
}