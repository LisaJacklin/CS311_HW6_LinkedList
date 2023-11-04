//da6.hpp
//Lisa Jacklin && Jewel Maldonado
//2023-11-03

#include "llnode2.hpp"
#include <stdexcept>
#include <utility>

// --------------------------------------------------------
//Exercise A
template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>> & head) {
    unique_ptr<LLNode2<ValType>> prev = nullptr;
    unique_ptr<LLNode2<ValType>> current = std::move(head);
    unique_ptr<LLNode2<ValType>> next;

    while (current) {
        next = std::move(current->next);
        current->next = std::move(prev);
        prev = std::move(current);
        current = std::move(next);
    }

    head = std::move(prev);
}

// --------------------------------------------------------
//Exercise B

template <typename KeyType, typename DataType>
class SlowMap {
private:
    struct KeyValue {
        KeyType key;
        DataType data;

        KeyValue(const KeyType& k, const DataType& d) : key(k), data(d) {}
    };

    unique_ptr<LLNode2<KeyValue>> head;

public:
    SlowMap() : head(nullptr) {}

    // Destructor is automatically generated

    int size() const {
        int count = 0;
        auto current = head.get();
        while (current) {
            count++;
            current = current->next.get();
        }
        return count;
    }

    bool empty() const {
        return (head == nullptr);
    }

    bool present(const KeyType& key) const {
        auto current = head.get();
        while (current) {
            if (current->data.key == key) {
                return true;
            }
            current = current->next.get();
        }
        return false;
    }

    const DataType& get(const KeyType& key) const {
        auto current = head.get();
        while (current) {
            if (current->data.key == key) {
                return current->data.data;
            }
            current = current->next.get();
        }
        throw std::out_of_range("Key not found in SlowMap");
    }

    DataType& get(const KeyType& key) {
        return const_cast<DataType&>(static_cast<const SlowMap*>(this)->get(key));
    }

    void set(const KeyType& key, const DataType& data) {
        auto current = head.get();
        while (current) {
            if (current->data.key == key) {
                current->data.data = data;
                return;
            }
            current = current->next.get();
        }

        auto newKeyValue = std::make_unique<KeyValue>(key, data);
        auto newNode = std::make_unique<LLNode2<KeyValue>>(std::move(newKeyValue), std::move(head));
        head = std::move(newNode);
    }

    void erase(const KeyType& key) {
        if (head && head->data.key == key) {
            head = std::move(head->next);
            return;
        }

        auto prev = head.get();
        auto current = head->next.get();

        while (current) {
            if (current->data.key == key) {
                prev->next = std::move(current->next);
                return;
            }
            prev = current;
            current = current->next.get();
        }
    }

    template <typename Func>
    void traverse(Func func) {
        auto current = head.get();
        while (current) {
            func(current->data.key, current->data.data);
            current = current->next.get();
        }
    }
};
