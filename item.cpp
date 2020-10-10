//
//  item.cpp
//  Lab4
//
//  Created by Nghi Vo on 5/24/19.
//  Copyright © 2019 Nghi Vo. All rights reserved.
//

#include "item.h"
#include <iomanip>

using namespace std;

Item::Item (int id, const string& name, double price, int quantity){
    _id = id;
    _name = name;
    _price = price;
    _quantity = quantity;
}
int Item::getID() const{
    return _id;
}
string Item::getName() const{
    return _name;
}
double Item::getPrice() const{
    return _price;
}
int Item::getQuantity() const{
    return _quantity;
}

void Item::setID (int newId){
    _id = newId;
}
void Item::setName (string newName){
    _name = newName;
}
void Item::setPrice (double newPrice){
    _price = newPrice;
}
void Item::setQuantity (int newQuantity){
    _quantity = newQuantity;
}
