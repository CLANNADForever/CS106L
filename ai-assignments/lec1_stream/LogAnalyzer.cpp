/*
 * File: LogAnalyzer.cpp
 * ---------------------
 * CS106L - Assignment 1: Streams
 * This program analyzes a web server log file and reports statistics.
 */

#include <iostream>
#include <fstream>   // For ifstream
#include <sstream>   // For stringstream
#include <string>
#include <vector>

// In CS106L, we often use `using namespace std;` for simplicity in lectures.
using namespace std;

/* This struct is used to store the statistics from the log file. */
struct LogStats {
    int totalRequests;
    int successfulRequests;
    long long totalBytes; // Use long long for total bytes to avoid overflow
};

/*
 * Function: analyzeLogFile
 * Usage: LogStats stats = analyzeLogFile(inFile);
 * -------------------------------------------------
 * This function takes an input file stream which is already opened,
 * reads it line by line, and computes statistics about the log entries.
 *
 * Your task is to implement this function using the "getline/stringstream"
 * pattern.
 */
LogStats analyzeLogFile(ifstream& inFile) {
    LogStats stats = {0, 0, 0}; // Initialize stats to zero
    // TODO: Implement the rest of this function.

    // 1. Create a string variable to hold each line of the file.
    string line;

    // 2. Use a `while` loop with `getline` to read the file line by line.
    while(getline(inFile, line)) {
        // 3. Inside the loop, create a `stringstream` from the line.
        stringstream ss(line);

        // 4. Declare variables to store the parsed data (ip, method, code, bytes).
        string ip;
        string method;
        string code;
        long long bytes;

        // 5. Use the extraction operator (>>) on the stringstream to parse the line.
        ss >> ip >> method >> code >> bytes;

        // 6. Update the `stats` struct based on the parsed data.
        stats.totalRequests++;
        stats.totalBytes += bytes;
        if (code == "200") {
            stats.successfulRequests++;
        }
    }
    
    return stats;
}


// --- Main Program ---
// You don't need to change this part. It sets up the file and calls your function.
int main() {
    // Create a dummy log file for testing
    ofstream logFile("log.txt");
    logFile << "192.168.1.1 GET 200 1450\n";
    logFile << "10.0.0.5 POST 200 512\n";
    logFile << "192.168.1.1 GET 404 120\n";
    logFile << "203.0.113.8 GET 200 8192\n";
    logFile << "10.0.0.5 PUT 500 88\n";
    logFile.close();

    // Open the log file for reading
    ifstream inFile("log.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open log.txt" << endl;
        return 1;
    }

    // Call your function to analyze the file
    LogStats result = analyzeLogFile(inFile);
    inFile.close();

    // Print the results
    cout << "--- Log Analysis Results ---" << endl;
    cout << "Total Requests: " << result.totalRequests << endl;
    cout << "Successful Requests (Code 200): " << result.successfulRequests << endl;
    cout << "Total Bytes Transferred: " << result.totalBytes << endl;

    return 0;
}