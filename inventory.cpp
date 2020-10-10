//
//  inventory.cpp
//  Lab4
//
//  Created by Nghi Vo on 5/24/19.
//  Copyright © 2019 Nghi Vo. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include "item.h"
#include "inventory.h"
using namespace std;

// Node class

// Constructor with an item instance’s pointer.
// It assigns the parameter item to _item, then set _next as nullptr.
Node::Node (Item* item){
    _item = item;
    _next = nullptr;
}

// Destructor. It should delete _item.
Node::~Node(){
    delete _item;
}

// Accessor
// Returns the item pointer.
Item* Node::getItem() const{
    //if (_item != nullptr){
    return _item;
    //}
    //else {
    //    return nullptr;
    //}
}

// Accessor
// Returns the next node pointer.
Node* Node::getNext() const{
    return _next;
}

// Mutator, simply sets a new item instance pointer.
void Node::setItem(Item* item){
    _item = item;
}

// Mutator, simply sets a new next node pointer.
void Node::setNext(Node* next){
    _next = next;
}

//.......................................//

// Constructor
// Initializes _headto nullptr.
Inventory::Inventory(): _head (nullptr) {
    //_head = nullptr;
}

// Free up (i.e., delete) all nodes in the list.
Inventory::~Inventory(){
    while (isEmpty() == false){
        pop_front();
    }
}

// Allocate a new Node with the parameter item, then insert it at the front of the list.
// Update _head to the new Node pointer.
void Inventory::push_front(Item* item){
    Node* newNode = new Node(item);
    if (_head == nullptr){
        _head = newNode;
        _head->setNext(nullptr);
    }
    else {
        newNode->setNext(_head);
        _head = newNode;
        
    }
}

// Returns the first item of the list (i.e., _head’s item).
// If there is no Node, return nullptr.
Item* Inventory::front() const{
    if(_head == nullptr){
        return nullptr;
    }
    else {
        return _head->getItem();
    }
}

// Deletes the first node.
// Return true if the delete was successful, false otherwise (i.e., no node).
bool Inventory::pop_front(){
    if (_head == nullptr){
        return false;
    }
    else {
        Node* temp = _head;
        _head = _head->getNext();
        delete temp;
        return true;
    }
}

// Traverse  the  nodes  in  the  list and return  if  there  is  a  node containing  an  item  having  the  same  name  to  the  string parameter.
// Return a node pointer if found, nullptr otherwise.
Node* Inventory::findNodeByName(const string & name) const{
    Node* n = _head;
    while (n != nullptr){
        if (n->getItem()->getName() == name){
            return n;
            
        }
        n = n->getNext();
    }
    return nullptr;
}

// Traverse  the  nodes  in  the  list  and  return  if  there  is  a  node containing  an  item  having  the  same  ID  to  the  integer parameter.
// Return a node pointer if found, nullptr otherwise.
Node* Inventory::findNodeByID(const int id) const{
    Node* i = _head;
    while (i != nullptr){
        if (i->getItem()->getID() == id){
            return i;
        }
        i = i -> getNext();
    }
    return nullptr;
    
}

// Traverse the nodes in the list and return if there is a node containing an item having the same name to the string parameter.
// Return an item pointer if found, nullptr otherwise.
Item* Inventory::findItemByName(const string & name)const{
    Node* found = findNodeByName(name);
    if (found == nullptr)
        return nullptr;
    return found->getItem();
}

// Traverse  the  nodes  in  the  list  and  return  if  there  is  a  node containing  an  item  having  the  same  ID  to  the  integer parameter.
// Return an item pointer if found, nullptr otherwise.
Item* Inventory::findItemByID(const int id)const{
    Node* found = findNodeByID(id);
    if (found == nullptr)
        return nullptr;
    return found->getItem();
    
}

// Find an item with the given id(first parameter), then increase its quantity by the  given value (second  parameter).
// Return the updated quantity. If there is no item  with the given id, return -1.
int Inventory::stockIn(const int id, const int quantity){
    Item* found = findItemByID(id);
    if (found == nullptr)
        return -1;
    
    int q = found->getQuantity();
    q += quantity;
    found->setQuantity(q);
    return q;
    
}

// Find  an  item  with  the  given  id  (first  parameter), then decrease its quantity by the given value (second parameter).
// If the given value is greater than the current quantity in stock, update  the  quantity  as  zero.
// Return  how  many  items  are withdrawn.
int Inventory::stockOut(const int id, const int quantity){
    Item* found = findItemByID(id);
    if (found == nullptr)
        return -1;
    
    int q = found->getQuantity();
    if (quantity > q){
        found->setQuantity(0);
        return q;
    }
    else{
        q -= quantity;
        found->setQuantity(q);
    }
    return quantity;
}

// Add a new item to the inventory, if there is no item with the same ID.
// Return true if the addition was successful.
// Return false otherwise, that is, there is already an item with the same ID.
bool Inventory::addNewItem(Item* item){
    if (findItemByID(item->getID()) != nullptr){
        return false;
    }
    else {
        push_front(item);
        return true;
    }
}
// Find an item with the given ID, then delete it.
bool Inventory::deleteItem(const int item){
    if (_head != nullptr){
        Node* a = findNodeByID(item);
        if ( a != nullptr){
        Item *temp;
        temp  = _head->getItem();
        _head->setItem(a->getItem());
        a->setItem(temp);
        pop_front();
        return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Inventory::isEmpty() const{
    if (_head == nullptr){
        return true;
    }
    else{
        return false;
    }
}

// Reads records from an istream, and insert them  to  the inventory.
// Each line has the four fields for one item record. Per record, an Item object is allocated and added to the inventory.
// Returns the number of recordsread.
int Inventory::load(istream& fin){
    int count = 0;
    int id;
    string name;
    double price;
    int quantity;
    while (!fin.eof()){
        // Using fin to read in file
        // Fin read each part in the line
        fin >> id >> name >> price >> quantity;
        
        // Read until out of word in the line
        if (fin.fail()){
            break;
        }
        else {
            Item* newItem = new Item(id, name, price, quantity);
            addNewItem(newItem);
            count++;
        }
    }
    return count;
}

void Inventory::formattedPrint(ostream& out){
    Node* n = _head;
    while (n != nullptr){
        out << left << fixed << setprecision(2);
        out << setw(6) << n->getItem()->getID();
        out << setw(12) << n->getItem()->getName();
        out << setw(8) << n->getItem()->getPrice();
        out << setw(4) << n->getItem()->getQuantity() << endl;
        n = n->getNext();
    }
    
}


