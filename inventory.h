//
//  inventory.h
//  Lab4
//
//  Created by Nghi Vo on 5/24/19.
//  Copyright © 2019 Nghi Vo. All rights reserved.
//

#ifndef inventory_h
#define inventory_h
#include "item.h"
using namespace std;

class Node {
private:
    Item* _item;
    Node* _next;
    
public:
    Node (Item* item);
    ~Node();
    Item* getItem() const;
    Node* getNext() const;
    void setItem(Item*);
    void setNext(Node*);
};

class Inventory {
private:
    Node* _head;
public:
    Inventory();
    ~Inventory();
    void push_front(Item*);
    Item* front() const;
    bool pop_front();
    Node* findNodeByName(const string &) const;
    Node* findNodeByID(const int) const;
    Item* findItemByName(const string &)const;
    Item* findItemByID(const int)const;
    int stockIn(const int,const int);
    int stockOut(const int,const int);
    bool addNewItem(Item*);
    bool deleteItem(const int);
    bool isEmpty() const;
    int load(istream&);
    void formattedPrint(ostream&out);
};

#endif /* inventory_h */
