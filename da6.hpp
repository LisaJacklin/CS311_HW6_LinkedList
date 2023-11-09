//da6.hpp
//Lisa Jacklin && Jewel Maldonado
//2023-11-03

#ifndef DA6_HPP
#define DA6_HPP

// --------------------------------------------------------
// Libraries and Linkers
// --------------------------------------------------------
#include "llnode2.hpp"        //required header
#include <stdexcept>          //for std::out_of_range
#include <utility>            //for std::move
#include <memory>
using std::unique_ptr;        //simpifies writing it

// --------------------------------------------------------
//Exercise A
template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>> & head) {
    //Need give a nullptr if the unique_ptr is empty
    if (!head) {
        // The list is empty, so nothing to reverse.
        return;
    }

    //setup unique pointers:
    unique_ptr<LLNode2<ValType>> prev = nullptr;              //previous begins as a nullptr,
    unique_ptr<LLNode2<ValType>> current;                     //current moves the head through the linked list
    unique_ptr<LLNode2<ValType>> next =  std::move(prev->_next); //next is what comes next in the list.


  //Once the unique pointers are setup, std::move and be used to change the order
  //of all items in the Linked List
    while (next != nullptr) {                                 //so long as the next location isn't null
        current = std::move(next);                            //moving forward through the linked list

        //now we need to check that the next move isn't a null
        if (current ->_next != nullptr) {
          next = std::move(current -> _next);                //so long as next isn't null, we can iterate through
        } else {
          next = nullptr;                                    //and if it is null, we neet to set it as such.
        }

        //now to iterate through each piece, updating current and previous to new values.
        current->_next = std::move(prev);
        prev = std::move(current);
    }

    head = std::move(prev);                                 //set head back to the new beginning of the linked list
}

// --------------------------------------------------------
//Exercise B
// --------------------------------------------------------
//note that ktype is Key_Type and vtype is Data_Type
template <typename Key_Type, typename Data_Type>
class SlowMap {
private:
    struct KeyValue {
        Key_Type key;
        Data_Type data;

        KeyValue(const Key_Type& k, const Data_Type& d) : key(k), data(d) {}
    };

    //another way that may be easier to wrap our heads around: 
    /* 
    private:
        using key_type = Key_Type; //using the templates and an easier way to express
        using value_type = Data_Type;

        using pair_type = std::pair<key_type, value_type>;
        //using this we would have the associative pair easily using pair (STL utility...)

        std::unique_ptr<LLNode2<pair_type>> _data; 

        //granted, this is the same way to consider what we are to achieve, although one uses a struct with KeyValue as our pairing vs this example using std::pair to give us the pairing...
    */


    unique_ptr<LLNode2<KeyValue>> head;

public:
    //default constructor: generates an empty dataset
    SlowMap() : head(nullptr) {}

    // Destructor is automatically generated

    //function size:
    //takes no par. and returns an int of an appropriate type given the 
    //number of key-value pairs in the dataset
    int size() const {
        int count = 0;
        auto current = head.get();
        while (current) {
            count++;
            current = current->_next.get();
        }
        return count;
    }

    //empty function:
    //returns a bool: true if no keyvalue pairs in dataset, false otherwise
    bool empty() const {
        return (head == nullptr);
    }

    //present function:
    // takes a single parameter, Key_Type
    //returns a bool: true is key lies in the dataset, false otherwise
    bool present(const Key_Type& key) const {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                return true;
            }
            current = current->_next.get();
        }
        return false;
    }

    //function get:
    //returns a constant Data_type & for a const Slowmap.
    //if there is an equal key, the associated value will be returned,
    //otherwise an exceptionis thrown.
    const Data_Type& get(const Key_Type& key) const {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                return current->_data.data;
            }
            current = current->_next.get();
        }
        //no associated value, so an exception is thrown.
        throw std::out_of_range("Key not found in SlowMap");
    }

    //function get:
    //returns data_type & for a non-constnat slowmap.
    Data_Type& get(const Key_Type& key) {
        return const_cast<Data_Type&>(static_cast<const SlowMap*>(this)->get(key));
    }

    //function set:
    //takes two par: a key and an associated value 
    //returns nothing.
    //if an equal key isn't in the dataset, the key pair is inserted.
    //if an equal does lie in the dataset, the existing key pair is replaced.
    void set(const Key_Type& key, const Data_Type& data) {
        auto current = head.get();
        while (current) {
            if (current->_data.key == key) {
                current->_data.data = data;
                return;
            }
            current = current->_next.get();
        }

        auto newKeyValue = std::make_unique<KeyValue>(key, data);
        auto newNode = std::make_unique<LLNode2<KeyValue>>(std::move(*newKeyValue), std::move(head));
        head = std::move(newNode);
    }

    //function erase:
    //takes a single key parameter, returns nothing
    //if an equal key is in the dataset, then the key pair is removed
    //if equal key doesn't lie in the dataset, then the function does nothing.
    void erase(const Key_Type& key) {
        if (head && head->_data.key == key) {
            head = std::move(head->_next);
            return;
        }

        auto prev = head.get();
        auto current = head->_next.get();

        while (current) {
            if (current->_data.key == key) {
                prev->_next = std::move(current->_next);
                return;
            }
            prev = current;
            current = current->_next.get();
        }
    }

    //transverse function:
    //takes a function or function object (thus the template),
    //returns nothing, the passed function requires two pars,
    //key and data type and returns nothing as well.
    //This passed function is called for each key pair in the dataset.
    template <typename Func>
    void traverse(Func func) {
        auto current = head.get();
        while (current) {
            func(current->_data.key, current->_data.data);
            current = current->_next.get();
        }
    }
};

#endif  //end of DA6_HPP