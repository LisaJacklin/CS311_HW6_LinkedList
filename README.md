# CS311_HW6_LinkedList
[Assignment 6] (https://www.cs.uaf.edu/~chappell/class/2023_fall/cs311/docs/d-assn06d.html) in Data Structures and Algorithms: Linked List
Lisa Jacklin && Jewel Maldonado

## Notes:
- no source file will be required as we are working in a template header.
- requires the use of llnode2.hpp which cannot be modified
- we must also reference the linked list file via unique_ptr, creation of nodes via make_unique, or push_front which are all in llnode2.hpp.
- we cannot use new or delete
- any STL functionalities may be used as desired.
- 
## Requirements:  
*Shown below are some requirements and checklist items:*  
- [ ] Exercise A - Reversing a Linked List
    **Purpose**  
    - to be able to write an efficient reversing function for a linked list
    - use smart pointers
    **Instructions**  
    - All [coding standards](https://www.cs.uaf.edu/~chappell/class/2023_fall/cs311/docs/coding_std.html) now apply.
    - [ ] write a function template 'reverseList' prototype as follows:
          template<typename ValType>
          void reverseList(unique_ptr<LLNode2<ValType>> & head);
          - this function gives a unique_ptr to a linked list, an empty unique_prt if the list is empty!
          - this also alters the lits to allow values to appear in an unstable format (reverse order high to low)
  - [ ] reverseList required Functions:
        - performs no value type operations at all
        - runs in- place
        - runs in linear time.

  - [ ] Exercise B = Associative Dataset Class Template
    **Purpose**  
    - write a class template that uses a link list to hold an associative dataset, although this isn't a good way to implement this, we will cover better alternatives in the future.
    - an associative dataset is one which items are looked up by key and often there is a value associated with each key!
    - note no public member functions in SlowMap!
        - no copy ctor, move ctor, copy assignment, move assignment all must be deleted
 - All member functions should have the highest reasonable levels of exception safety.
 - All member functions must be exception-neutral; that is, exceptions thrown by value-type operations must propagate unchanged to the caller.
 - You may not forbid any member function of the key type or data type from throwing, except for the destructors.
    **Instructions**  
    - All [coding standards](https://www.cs.uaf.edu/~chappell/class/2023_fall/cs311/docs/coding_std.html) now apply.
    - [ ] implement a c++ class template that stores and manages an associative dataset consisting of key-value pairs.
    - note that duplicate keys should not be allowed, determining whether two keys are the same should be done (== operator)
    - [ ] call the class template 'SlowMap', where it can be declared as SlowMap(string, int).
    - [ ] The class must have one and only one data member of type 'unique_ptr<LLNode2<KVType>> note that KVTYppe is a type that can hold a single key-value pair. (std::pair or struct as appropriate)
    - a stored associative dataset must be held in a singly linked list of key-value pairs with the above data member as its head pointer.
    - [ ] Member functions!
       - default constructor to create an empty dataset
       - deconstructor (normal)
       - function size which takes no parameters, returns an int of an appropriate type given the number of key-value pairs in the dataset.
       - function empty which takes no parameters, returns bool: when true there is no key-value pairs in the stored dataset, otherwise false.
       - function present which takes a single key parameter. Returns a bool:The return value is true if a key equal to that given lies in the stored dataset, and false otherwise.
       - function get which takes a single key as a parameter. Returns a const Data_Type & for a const SlowMap and Data_Type & for a non-const slowMap. if an equal key lies in the stored dataset, then the associated value is returned as indicated, otherwise an exception std::out_of_range is thrown with the what member set to some human-readable string.
       - Function set. Two parameters: a key and an associated value. Returns nothing. If an equal key does not lie in the dataset, then the key-value pair is inserted. If an equal key does lie in the dataset, then the existing key-value pair is replaced with that given.
       - Function erase. One parameter: a key. Returns nothing. If an equal key lies in the dataset, then that key-value pair is removed. If an equal key does not lie in the dataset, then the function does nothing.
       - Function traverse. One parameter: a function or function object (its type can simply be a template parameter). Returns nothing. The passed function is expected to take two parameters, key type and data type, and return nothing. The passed function is called on each key-value pair in the dataset.
