/*
 * File: FileSystem.cpp
 * --------------------
 * Implements the Node, File, Directory, and FileSystem classes.
 */

#include "FileSystem.h"
#include <sstream>  // Required for stringstream
#include <algorithm> // Required for std::find_if if you choose to use it

// using namespace std;

// --- Node Class Implementation ---

// Implement the Node constructor.
Node::Node(const std::string& name) : m_name{name} {};

// Implement the Node's getName function.
std::string Node::getName() const {
    return m_name;
}


// --- File Class Implementation ---

// Implement the File constructor.
File::File(std::string name, size_t size) : Node(name), m_size{size} {}; //TODO

// Implement the File's print function.
// Remember to handle the indentation. A simple loop printing spaces works well.
void File::print(int indent /*=0*/) const {
    printSpace(indent);
    std::cout << "-- " << m_name << " (" << m_size << " bytes)" << std::endl;
}


// --- Directory Class Implementation ---

// Implement the Directory constructor.
Directory::Directory(std::string name) : Node(name) {};

// Implement the Directory destructor.
// Loop through m_children and delete each pointer.
Directory::~Directory() {
    for (const auto& p : m_children) {
        delete p;
    }
}

// Implement the Directory's print function.
// It should first print its own name with indentation,
// then recursively call print() on all its children with increased indentation.
void Directory::print(int indent /*=0*/) const {
    printSpace(indent);
    std::cout << "+ " << m_name << std::endl;
    for (const auto& p : m_children) {
        p->print(indent + 2);
    }
} 

// Implement other Directory methods like addChild and findChild.
void Directory::addChild(Node* child) {
    m_children.push_back(child);
}

Node* Directory::findChild(const std::string& name) const {
    for (const auto& p : m_children) {
        if (p->getName() == name) {
            return p;
        }
    }
    return nullptr;
}

// --- FileSystem Class Implementation ---

// Implement the FileSystem constructor.
// It should initialize m_root with a new Directory.
FileSystem::FileSystem() {
    m_root = new Directory("/"); //TODO
}

// Implement the FileSystem destructor.
// It should delete m_root.
FileSystem::~FileSystem() {
    delete m_root;
}

// Implement FileSystem's listAll and getRoot methods.
void FileSystem::listAll() const {
    m_root->print();
}

Directory* FileSystem::getRoot() const {
    return m_root;
}

// Implement addFile and addDirectory. This is the most complex part.
// You'll need to parse the path string.
// A helper function that takes a path and returns the parent directory node might be very useful!

bool FileSystem::addFile(const std::string& path, size_t size) {
    auto allPathString = splitPath(path);
    Directory* parentDir = getNode(m_root, allPathString);
    if (parentDir == nullptr) {
        return false;
    }

    std::string name = allPathString.at(allPathString.size() - 1);
    // 已经存在则不能创建
    if (parentDir->findChild(name)) {
        return false;
    }
    File* f = new File(name, size);
    parentDir->addChild(f);
    return true;
}

bool FileSystem::addDirectory(const std::string& path) {
    auto allPathString = splitPath(path);
    Directory* parentDir = getNode(m_root, allPathString);
    if (parentDir == nullptr) {
        return false;
    }
    std::string name = allPathString.at(allPathString.size() - 1);
    // 已经存在则不能创建
    if (parentDir->findChild(name)) {
        return false;
    }
    Directory* d = new Directory(name);
    parentDir->addChild(d);
    return true;
}

std::vector<std::string> FileSystem::splitPath(const std::string& path) const {
    std::stringstream ss(path);
    std::string pathString;
    std::vector<std::string> allPathString;
    while (std::getline(ss, pathString, '/')) {
        allPathString.push_back(pathString);
    }

    return allPathString;
}

Directory* FileSystem::getNode(Directory* root, const std::vector<std::string>& path) const {
    int n = path.size();
    Directory* curDir = root;
    for (int i = 1; i < n - 1; i++) {
        std::string dirName = path.at(i);
        Node* next = curDir->findChild(dirName);
        
        Directory* dNode = dynamic_cast<Directory*>(next);
        if (dNode == nullptr) {
            return nullptr;
        } else {
            curDir = dNode;
        }
    }
    return curDir;
}