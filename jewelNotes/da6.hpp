// da6.hpp
// Lisa Jacklin && Jewel Maldonado
// 2023-11-03
// Interface for Assignment 6
#ifndef DA6_HPP_INCLUDED
#define DA6_HPP_INCLUDED
//Exercise A- Reverse Linked List
//-----------------------------------------------------------------------------------
#include <memory> // For std::unique_ptr and std::make_unique
#include "llnode2.hpp" // the provided linked list node definition
#include <stdexcept>
#include <utility>


template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> &head) {
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;
    std::unique_ptr<LLNode2<ValType>> nextNode = nullptr;

    while (head) {
        nextNode = std::move(head->_next); // Save the next node
        head->_next = std::move(newHead); // Reverse the link
        newHead = std::move(head); // Update the new head to the current node
        head = std::move(nextNode); // Move to the next node
    }

    head = std::move(newHead); // Update the original head to the new head of the reversed list
}
//Exercise B - 
//----------------------------------------------------

template<typename KeyType, typename DataType>
class SlowMap {
public:
    using KVType = std::pair<KeyType, DataType>;

    // Default constructor
    SlowMap() = default;

    // Destructor
    ~SlowMap() = default;

    // Return the number of key-value pairs in the dataset
    std::size_t size() const noexcept {
        return ::size(_head);
    }

    // Check if the dataset is empty
    bool empty() const noexcept {
        return !_head;
    }

    // Check if a key is present in the dataset
    bool present(const KeyType &key) const {
        auto node = _head.get();
        while (node) {
            if (node->_data.first == key) return true;
            node = node->_next.get();
        }
        return false;
    }

    // Get the value associated with a key
    DataType& get(const KeyType &key) {
        return const_cast<DataType&>(std::as_const(*this).get(key));
    }

    const DataType& get(const KeyType &key) const {
        auto node = _head.get();
        while (node) {
            if (node->_data.first == key) return node->_data.second;
            node = node->_next.get();
        }
        throw std::out_of_range("Key not found");
    }

    // Set the value for a key
    void set(const KeyType &key, const DataType &value) {
        auto node = _head.get();
        while (node) {
            if (node->_data.first == key) {
                node->_data.second = value;
                return;
            }
            node = node->_next.get();
        }
        push_front(_head, KVType(key, value));
    }

    // Erase the key-value pair for a key
    void erase(const KeyType &key) {
        auto node = _head.get();
        std::unique_ptr<LLNode2<KVType>> *prev = &_head;
        while (node) {
            if (node->_data.first == key) {
                *prev = std::move(node->_next);
                return;
            }
            prev = &node->_next;
            node = node->_next.get();
        }
    }

    // Traverse the dataset and apply a function to each key-value pair
    template<typename Func>
    void traverse(Func func) {
        for (auto node = _head.get(); node != nullptr; node = node->_next.get()) {
            func(node->_data.first, node->_data.second);
        }
    }

    // Deleted functions
    SlowMap(const SlowMap&) = delete;
    SlowMap(SlowMap&&) = delete;
    SlowMap& operator=(const SlowMap&) = delete;
    SlowMap& operator=(SlowMap&&) = delete;

private:
    std::unique_ptr<LLNode2<KVType>> _head;
};

#endif // DA6_HPP_INCLUDED
