/*
 * File: main.cpp
 * --------------
 * A simple test program for the FileSystem classes.
 */

#include "FileSystem.h"

using namespace std;

// A wrapper function to make calling the generic find more convenient from main.
template <typename T>
T* find(FileSystem* fs, const std::string& name) {
    return find<T>(fs->getRoot(), name);
}

int main() {
    FileSystem fs;

    cout << "--- Initializing File System ---" << endl;
    fs.addDirectory("/home");
    fs.addDirectory("/home/user");
    fs.addFile("/home/user/todo.txt", 150);
    fs.addDirectory("/etc");
    fs.addFile("/etc/config.json", 2048);
    fs.addFile("/readme.md", 512);

    // Test some error cases
    cout << "\n--- Testing Error Cases ---" << endl;
    cout << "Trying to add file to non-existent path: " << (fs.addFile("/var/log/sys.log", 100) ? "Success" : "Failed (Correct)") << endl;
    cout << "Trying to add duplicate directory: " << (fs.addDirectory("/home/user") ? "Success" : "Failed (Correct)") << endl;


    cout << "\n--- File System Listing ---" << endl;
    fs.listAll();


    cout << "\n--- Searching for nodes ---" << endl;
    // Note: We're calling the wrapper function here for convenience
    File* f = find<File>(&fs, "todo.txt");
    if (f) {
        cout << "Found file: " << f->getName() << " in the file system." << endl;
    } else {
        cout << "File 'todo.txt' not found." << endl;
    }

    Directory* d = find<Directory>(&fs, "home");
    if (d) {
        cout << "Found directory: " << d->getName() << " in the file system." << endl;
    } else {
        cout << "Directory 'home' not found." << endl;
    }

    Node* n = find<Node>(&fs, "non-existent");
    if (!n) {
        cout << "Node 'non-existent' not found (Correct)." << endl;
    }

    cout << "\n--- FileSystem is going out of scope, destructor will be called ---" << endl;
    return 0;
}