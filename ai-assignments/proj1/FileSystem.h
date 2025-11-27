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

// Forward declaration to let Node know about Directory
class Directory;

/*
 * Base class for all objects in our file system.
 * This is an abstract base class.
 */
class Node {
public:
    // TODO: Declare the virtual destructor. Use the default implementation.
    // virtual ~Node() = default;

    // TODO: Declare the pure virtual print function. It should take an optional int for indent level.
    // virtual void print(...) const = 0;

    // TODO: Declare the virtual getName getter.
    // virtual std::string getName() const;

protected:
    // TODO: Declare the constructor. It should be protected so only derived classes can call it.
    // Node(const std::string& name);

    // TODO: Declare the name member variable.
    // std::string m_name;
};

/*
 * Class representing a File in our file system.
 */
class File : public Node {
public:
    // TODO: Declare the constructor for File. It should take a name and a size.
    // File(...);

    // TODO: Override the print function from the Node class.
    // void print(...) const override;

private:
    // TODO: Declare the size member variable.
    // size_t m_size;
};

/*
 * Class representing a Directory in our file system.
 */
class Directory : public Node {
public:
    // TODO: Declare the constructor for Directory. It should take just a name.
    // Directory(...);

    // TODO: Declare the destructor. It must clean up the children nodes.
    // ~Directory();

    // TODO: Override the print function from the Node class.
    // void print(...) const override;

    // TODO: Declare functions to add a child node. You might want separate functions for File and Directory.
    // void addChild(Node* child);

    // TODO: Declare a function to find a child node by name. This will be helpful for path parsing.
    // Node* findChild(const std::string& name);

private:
    // TODO: Declare the vector to hold pointers to child nodes.
    // std::vector<Node*> m_children;
};


/*
 * The main class to manage the entire file system simulation.
 */
class FileSystem {
public:
    // TODO: Declare the constructor and destructor.
    // FileSystem();
    // ~FileSystem();

    // TODO: Declare the main public interface functions.
    // void listAll() const;
    // bool addFile(const std::string& path, size_t size);
    // bool addDirectory(const std::string& path);
    
    // TODO: Declare a getter for the root node, which will be useful for the `find` template function.
    // Directory* getRoot() const;

private:
    // TODO: Declare the root directory pointer.
    // Directory* m_root;
};


/*
 * A generic template function to find a node of a specific type.
 * Note: Since this is a template function, its implementation MUST be in the header file.
 */
// TODO: Implement the `find` template function here.
// template <typename T>
// T* find(Node* root, const std::string& name) {
//     // 1. Check if the root itself matches the type and name.
//     //    Use dynamic_cast to check the type.
//     // 2. If the root is a Directory, recursively search its children.
//     // 3. If not found after checking everything, return nullptr.
// }


#endif // FILESYSTEM_H