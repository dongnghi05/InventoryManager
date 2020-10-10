//
//  item.hpp
//  Lab4
//
//  Created by Nghi Vo on 5/24/19.
//  Copyright © 2019 Nghi Vo. All rights reserved.
//

#ifndef item_h
#define item_h

#include <string>
#include <stdio.h>
using namespace std;

class Item {
private:
    int _id;
    string _name;
    double _price;
    int _quantity;
    
public:
    Item (int, const string&, double, int);
    int getID() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
    
    void setID (int);
    void setName (string);
    void setPrice (double);
    void setQuantity (int);
};
#endif /* item_h */

