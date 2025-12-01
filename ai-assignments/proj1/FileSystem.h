/*
 * File: FileSystem.h
 * ------------------
 * Defines the interfaces for the Node, File, Directory, and FileSystem classes.
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <deque>

// Forward declaration to let Node know about Directory
class Directory;

/*
 * Base class for all objects in our file system.
 * This is an abstract base class.
 */
class Node {
public:
    // Declare the virtual destructor. Use the default implementation.
    virtual ~Node() = default;

    // Declare the pure virtual print function. It should take an optional int for indent level.
    virtual void print(int indent = 0) const = 0; // 纯虚函数

    // Declare the virtual getName getter.
    virtual std::string getName() const;

protected:
    // Declare the constructor. It should be protected so only derived classes can call it.
    Node(const std::string& name);

    // Declare the name member variable.
    std::string m_name;

    // 辅助函数，所有子类可以用，而且不能重写
    void printSpace(int n) const { //TODO
        for (size_t i = 0; i < n; i++) {
            std::cout << " ";
        }
    }
};

/*
 * Class representing a File in our file system.
 */
class File : public Node {
public:
    // Declare the constructor for File. It should take a name and a size.
    File(std::string name, size_t size);

    // Override the print function from the Node class.
    void print(int indent = 0) const override;

private:
    // Declare the size member variable.
    size_t m_size;
};

/*
 * Class representing a Directory in our file system.
 */
class Directory : public Node {
public:
    // Declare the constructor for Directory. It should take just a name.
    Directory(std::string name);

    // Declare the destructor. It must clean up the children nodes.
    ~Directory();

    // Override the print function from the Node class.
    void print(int indent = 0) const override;

    // Declare functions to add a child node. You might want separate functions for File and Directory.
    void addChild(Node* child);

    // Declare a function to find a child node by name. This will be helpful for path parsing.
    Node* findChild(const std::string& name) const;

    std::vector<Node*> getChild() {
        return m_children;
    }

private:
    // Declare the vector to hold pointers to child nodes.
    std::vector<Node*> m_children;
};


/*
 * The main class to manage the entire file system simulation.
 */
class FileSystem {
public:
    // Declare the constructor and destructor.
    FileSystem();
    ~FileSystem();

    // Declare the main public interface functions.
    void listAll() const;
    bool addFile(const std::string& path, size_t size);
    bool addDirectory(const std::string& path);
    
    // Declare a getter for the root node, which will be useful for the `find` template function.
    Directory* getRoot() const;

private:
    // Declare the root directory pointer.
    Directory* m_root;

    std::vector<std::string> splitPath(const std::string& path) const;
    Directory* getNode(Directory* root, const std::vector<std::string>& path) const;
};


/*
 * A generic template function to find a node of a specific type.
 * Note: Since this is a template function, its implementation MUST be in the header file.
 */
// Implement the `find` template function here.
template <typename T>
T* find(Node* root, const std::string& name) {
    // 递归基本情况：找到了类型和名字都正确的节点
    if (root->getName() == name) {
        T* tNode = dynamic_cast<T*>(root);
        if (tNode != nullptr) {
            return tNode;
        }
    }

    // 1. Check if the root itself matches the type and name.
    //    Use dynamic_cast to check the type.
    Directory* directoryNode = dynamic_cast<Directory*>(root);
    if (directoryNode == nullptr) { // root不是目录，而且不是所要的节点，则这一分支没有找到
        // std::cout << "Root must be a directory!" << std::endl;
        return nullptr;
    }

    // 2. If the root is a Directory, recursively search its children.
    T* result;
    for (const auto& childNode : directoryNode->getChild()) {
        result = find<T>(childNode, name);
        if (result != nullptr) {
            return result;
        }
    }

    // 3. If not found after checking everything, return nullptr.
    return nullptr;
}


#endif // FILESYSTEM_H