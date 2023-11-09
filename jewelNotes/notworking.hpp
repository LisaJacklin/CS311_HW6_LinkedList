// da6.hpp
// Lisa Jacklin && Jewel Maldonado
// 2023-11-03
// Interface for Assignment 6
#ifndef DA6_HPP
#define DA6_HPP

// Include necessary standard library headers
#include <memory>       // For std::unique_ptr, used for smart pointer management
#include <utility>      // For std::pair, used to create key-value pairs
#include <stdexcept>    // For std::out_of_range exception, used in error handling
#include <functional>   // For std::function, to allow function passing as an argument

// Include the linked list node definition
#include "llnode2.hpp"  // For LLNode2, the definition of the linked list node

//----------------------------------------------------
// Exercise A
// Reverse the given linked list
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>>& head) {
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;
    while (head) {
        auto next = std::move(head->_next);
        head->_next = std::move(newHead);
        newHead = std::move(head);
        head = std::move(next);
    }
    head = std::move(newHead);
}

//----------------------------------------------------
// Exercise B
// A slow map implemented as a singly linked list
template<typename KeyType, typename DataType>
class SlowMap {
public:
    // Internal data structure for key-value pairs
    struct KeyValuePair {
        KeyType key;
        DataType data;

        // Constructor for the KeyValuePair struct
        KeyValuePair(const KeyType& k, const DataType& d)
            : key(k), data(d) {}
    };

private:
    std::unique_ptr<LLNode2<KeyValuePair>> head;  // Head of the linked list

public:
    // Default constructor
    SlowMap() : head(nullptr) {}

    // Destructor is automatically managed by unique_ptr for head

    // Returns the number of elements in the map
    std::size_t size() const {
        auto current = head.get();
        std::size_t count = 0;
        while (current) {
            ++count;
            current = current->_next.get();
        }
        return count;
    }

    // Checks if the map is empty
    bool empty() const {
        return !head;
    }

    // Checks if a key is present in the map
    bool present(const KeyType& key) const {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                return true;
            }
            current = current->_next.get();
        }
        return false;
    }

    // Gets the data associated with the key
    DataType& get(const KeyType& key) {
        for (auto current = head.get(); current; current = current->_next.get()) {
            if (current->_data.key == key) {
                return current->_data.data;
            }
        }
        throw std::out_of_range("Key not found");
    }

    // Gets the data associated with the key (const version)
    const DataType& get(const KeyType& key) const {
        for (auto current = head.get(); current; current = current->_next.get()) {
            if (current->_data.key == key) {
                return current->_data.data;
            }
        }
        throw std::out_of_range("Key not found");
    }

    // Sets the value for a key, or creates a new node if key doesn't exist
    void set(const KeyType& key, const DataType& data) {
        for (auto current = head.get(); current; current = current->_next.get()) {
            if (current->_data.key == key) {
                current->_data.data = data;
                return;
            }
        }
        auto newNode = std::make_unique<LLNode2<KeyValuePair>>(KeyValuePair(key, data));
        newNode->_next = std::move(head);
        head = std::move(newNode);
    }


    // Erases the node with the given key
    void erase(const KeyType& key) {
        LLNode2<KeyValuePair>* prev = nullptr;
        for (auto current = head.get(); current; current = current->_next.get()) {
            if (current->_data.key == key) {
                auto temp = std::move((prev ? prev->_next : head)->_next);
                (prev ? prev->_next : head) = std::move(temp);
                return;
            }
            prev = current;
        }
    }

    // Traverses the map and applies a function to each key-value pair
    void traverse(std::function<void(const KeyType&, DataType&)> visit) {
        for (auto current = head.get(); current; current = current->_next.get()) {
            visit(current->_data.key, current->_data.data);
        }
    }
};

#endif // DA6_HPP
