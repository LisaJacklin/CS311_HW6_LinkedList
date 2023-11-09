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

/*//da6.hpp
//Lisa Jacklin && Jewel Maldonado
//2023-11-03
// da6.hpp
#ifndef DA6_HPP
#define DA6_HPP

// Include necessary standard library headers
#include <memory>       // For std::unique_ptr
#include <utility>      // For std::pair
#include <stdexcept>    // For std::out_of_range exception
#include <functional>   // For std::function

// Include the linked list node definition.
#include "llnode2.hpp"  // Assumes LLNode2 is defined in this file and uses std::unique_ptr

//----------------------------------------------------
//Exercise A
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>>& head) {
    // Notes:
    // Implementation details to reverse the list
    // Be sure to only use smart pointers and do not use new or delete.
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;  // This will become the new head of the reversed list
    while (head) {
        std::unique_ptr<LLNode2<ValType>> _next = std::move(head->_next); // Temporarily take ownership of the _next node
        head->_next = std::move(newHead);  // Move the current newHead into the _next of the current node
        newHead = std::move(head);        // Move the current node to become the new head
        head = std::move(_next);           // Move to the _next node in the original list
    }
    head = std::move(newHead);  // Update the original head reference to the new head of the reversed list
}


// Exercise B

template<typename KeyType, typename DataType>
class SlowMap {
public:
    // Assuming KeyValuePair is defined somewhere in SlowMap
    using KeyValuePair = std::pair<KeyType, DataType>;

    // ... (other parts of the SlowMap class)

    void set(const KeyType& key, const DataType& data) {
        // ... (other parts of the set function)

        // Create a KeyValuePair object.
        KeyValuePair kvpair(key, data);

        // Instead of passing two arguments to make_unique, create the node separately
        // and then use make_unique with a single argument if that's what the constructor expects.
        auto new_node = new LLNode2<KeyValuePair>(kvpair); // Construct a node with data.
        // Now create a unique_ptr with the new node.
        std::unique_ptr<LLNode2<KeyValuePair>> new_head(new_node);
        // Set the next pointer of the new node to the current head.
        new_head->next = std::move(head);
        // Move the new head to become the actual head.
        head = std::move(new_head);
    }

public:
    // Default ctor
    SlowMap() : head(nullptr) {}

    // Dctor
    ~SlowMap() {
        // Automatically handled by unique_ptr
    }

    // Function size
    std::size_t size() const {
        std::size_t count = 0;
        auto current = head.get();
        while (current) {
            ++count;
            current = current->_next.get();
        }
        return count;
    }

    // Function empty
    bool empty() const {
        return head == nullptr;
    }

    // Function present
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

    // Function get
    DataType& get(const KeyType& key) {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                return current->_data.data;
            }
            current = current->_next.get();
        }
        throw std::out_of_range("Key not found");
    }

    const DataType& get(const KeyType& key) const {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                return current->_data.data;
            }
            current = current->_next.get();
        }
        throw std::out_of_range("Key not found");
    }

    // Function set
    void set(const KeyType& key, const DataType& data) {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                current->_data.data = data;
                return;
            }
            current = current->_next.get();
        }
        // Key not found, insert new node at the front
        head = std::make_unique<LLNode2<KeyValuePair>>(KeyValuePair(key, data), std::move(head));
    }

    // Function erase
    void erase(const KeyType& key) {
        auto current = head.get();
        LLNode2<KeyValuePair>* prev = nullptr;
        while (current) {
            if (current->_data.key == key) {
                std::unique_ptr<LLNode2<KeyValuePair>> temp = std::move(current->_next);
                if (prev) {
                    prev->_next = std::move(temp);
                } else {
                    head = std::move(temp);
                }
                return;
            }
            prev = current;
            current = current->_next.get();
        }
        // Key not found, nothing to erase
    }

    // Function traverse
    template<typename Func>
    void traverse(Func func) {
        auto current = head.get();
        while (current) {
            func(current->_data.key, current->_data.data);
            current = current->_next.get();
        }
    }

    // No copying or moving allowed
    SlowMap(const SlowMap&) = delete;
    SlowMap(SlowMap&&) = delete;
    SlowMap& operator=(const SlowMap&) = delete;
    SlowMap& operator=(SlowMap&&) = delete;

private:
    struct KeyValuePair {
        KeyType key;
        DataType data;

        KeyValuePair(const KeyType& k, const DataType& d) : key(k), data(d) {}

        // Implement other necessary constructors, assignment operators if needed
    };

    std::unique_ptr<LLNode2<KeyValuePair>> head;
};

#endif // DA6_HPP
*/