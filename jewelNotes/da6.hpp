// da6.hpp
// Lisa Jacklin && Jewel Maldonado
// 2023-11-03
// Interface for Assignment 6

#ifndef DA6_HPP_INCLUDED
#define DA6_HPP_INCLUDED

// Include the necessary headers for memory management and the linked list node
#include <memory> // For std::unique_ptr and std::make_unique
#include "llnode2.hpp" // Include the definition of the provided linked list node
#include <stdexcept> // Include standard exceptions
#include <utility> // Include utility library for std::move

// Define a template function to reverse a singly linked list.
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> &head) {
    // Initialize a new head pointer for the reversed list to nullptr
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;
    // Temporary pointer to hold the next node in the original list
    std::unique_ptr<LLNode2<ValType>> nextNode = nullptr;

    // Loop through the list until we reach the end which is (null)
    while (head) {
        nextNode = std::move(head->_next); // Save the next node
        head->_next = std::move(newHead); // Reverse the current node's link
        newHead = std::move(head); // Move the current node to the new head of the reversed list
        head = std::move(nextNode); // Go to the next node in the original list
    }

    // After all nodes reversed, update the original head to point to the new head
    head = std::move(newHead); // The original list is now reversed
}

// Exercise B - Banging my head against the wall

// This is the template for our map, which stores pairs of keys and values
template<typename KeyType, typename DataType>
class SlowMap {
public:
    // This is a shortcut we use to refer to our key-value pairs
    using KVType = std::pair<KeyType, DataType>;

    // This is our default setup when we create a new map
    SlowMap() = default;

    // This is what happens when our map is no longer needed
    ~SlowMap() = default;

    // Tells us how many pairs are in our map
    std::size_t size() const noexcept {
        return ::size(_head);
    }

    // Checks if our map is empty (has no pairs)
    bool empty() const noexcept {
        return !_head;
    }

    // Looks for a key in our map to see if it's there
    bool present(const KeyType &key) const {
        auto node = _head.get();  // We start looking from the first pair
        while (node) {  // We keep looking through all pairs
            if (node->_data.first == key) return true;  // Found it!
            node = node->_next.get();  // Move to the next pair
        }
        return false;  // Didn't find it
    }

    // Gets the value linked to a key
    DataType& get(const KeyType &key) {
        // This is a trick to reuse code for both const and non-const maps
        return const_cast<DataType&>(std::as_const(*this).get(key));
    }

    // The same as above, but this one is used when we can't change the map
    const DataType& get(const KeyType &key) const {
        auto node = _head.get();  // We start looking from the first pair
        while (node) {  // We keep looking through all pairs
            if (node->_data.first == key) return node->_data.second;  // Found it, here's your value!
            node = node->_next.get();  // Move to the next pair
        }
        throw std::out_of_range("Key not found");  // Oops, that key isn't in our map
    }

    // Puts a new pair in our map or changes the value if the key is already there
    void set(const KeyType &key, const DataType &value) {
        auto node = _head.get();  // We start looking from the first pair
        while (node) {  // We keep looking through all pairs
            if (node->_data.first == key) {  // If we find the key
                node->_data.second = value;  // We update the value
                return;
            }
            node = node->_next.get();  // Move to the next pair
        }
        // If we didn't find the key, we add a new pair at the start
        push_front(_head, KVType(key, value));
    }

    // Removes a pair from our map using a key
    void erase(const KeyType &key) {
        auto node = _head.get();  // We start looking from the first pair
        std::unique_ptr<LLNode2<KVType>> *prev = &_head;  // We remember the previous pair
        while (node) {  // We keep looking through all pairs
            if (node->_data.first == key) {  // If we find the key
                *prev = std::move(node->_next);  // We remove that pair from the map
                return;
            }
            prev = &node->_next;  // Remember this pair, before moving to the next
            node = node->_next.get();  // Move to the next pair
        }
    }

    // Applies a function to each pair in the map
    template<typename Func>
    void traverse(Func func) {
        for (auto node = _head.get(); node != nullptr; node = node->_next.get()) {
            // We apply the function to each pair
            func(node->_data.first, node->_data.second);
        }
    }

    // We don't allow copying or moving the whole map - it's a unique thing!
    SlowMap(const SlowMap&) = delete;
    SlowMap(SlowMap&&) = delete;
    SlowMap& operator=(const SlowMap&) = delete;
    SlowMap& operator=(SlowMap&&) = delete;

private:
    // This is where we start our list of pairs
    std::unique_ptr<LLNode2<KVType>> _head;
};

#endif // DA6_HPP_INCLUDED
