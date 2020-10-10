#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>

#include "inventory.h"

using namespace std;

int main() {
    cerr << "Lab 4 unit test..." << endl;
    cerr << "" << endl;

    cerr << "Item class test..." << endl;
    cerr << " Checking constructor and getters..." << endl;
    Item *item = new Item(10001, "CokeZero", 0.99, 20);
    assert(item->getID() == 10001);
    assert(item->getName() == "CokeZero");
    assert(item->getPrice() == 0.99);
    assert(item->getQuantity() == 20);

    cerr << " Checking setters..." << endl;
    item->setID(20010);
    item->setName("DietCoke");
    item->setPrice(0.95);
    item->setQuantity(10);

    assert(item->getID() == 20010);
    assert(item->getName() == "DietCoke");
    assert(item->getPrice() == 0.95);
    assert(item->getQuantity() == 10);

    cerr << "Item class test finished." << endl;
    cerr << "" << endl;

    cerr << "Node class test..." << endl;
    cerr << " Checking constructor and getters..." << endl;
    Node *node = new Node(item);
    assert(node->getItem() == item);
    assert(node->getNext() == nullptr);

    cerr << " Checking setItem..." << endl;
    Item *item2 = new Item(10002, "OreoMint", 2.99, 30);
    node->setItem(item2);
    assert(node->getItem() == item2);
    node->setItem(item);
    assert(node->getItem() == item);

    cerr << " Checking setNext..." << endl;
    Node *node2 = new Node(item2);
    node->setNext(node2);
    cerr << "  Now node's next should be node2..." << endl;
    assert(node->getNext() == node2);

    cerr << "Node class test finished." << endl;
    cerr << "" << endl;

    cerr << "Inventory class test..." << endl;
    cerr << " Constructor, isEmpty, pop_front check when empty" << endl;
    Inventory *inven = new Inventory();
    assert(inven->isEmpty());
    assert(inven->pop_front() == false);

    cerr << " Adding three items..." << endl;
    Item *item3 = new Item(30001, "Clorox", 3.99, 10);
    inven->push_front(item);
    inven->push_front(item2);
    inven->push_front(item3);

    cerr << " Popping those three items..." << endl;
    assert(inven->isEmpty() == false);
    assert(inven->front() == item3);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == false);
    assert(inven->front() == item2);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == false);
    assert(inven->front() == item);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == true);

    cerr << " Load function check... 4 items" << endl;
    stringstream inbuffer1;
    inbuffer1.str(
            "11000 Sprite 1.29 20\n"
            "11001 DietSprite 0.99 21\n"
            "11002 Crush 1.19 22\n"
            "11003 DietCrush 0.89 23\n"
            );
    assert(inven->load(inbuffer1) == 4);

    cerr << " Load function check... 4 duplicate items... shouldn't be loaded" << endl;
    assert(inven->load(inbuffer1) == 0);

    cerr << " Popping and checking 4 items..." << endl;
    assert(inven->isEmpty() == false);
    item = inven->front();
    assert(item->getID() == 11003);
    assert(item->getName() == "DietCrush");
    assert(item->getPrice() == 0.89);
    assert(item->getQuantity() == 23);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == false);
    item = inven->front();
    assert(item->getID() == 11002);
    assert(item->getName() == "Crush");
    assert(item->getPrice() == 1.19);
    assert(item->getQuantity() == 22);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == false);
    item = inven->front();
    assert(item->getID() == 11001);
    assert(item->getName() == "DietSprite");
    assert(item->getPrice() == 0.99);
    assert(item->getQuantity() == 21);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == false);
    item = inven->front();
    assert(item->getID() == 11000);
    assert(item->getName() == "Sprite");
    assert(item->getPrice() == 1.29);
    assert(item->getQuantity() == 20);
    assert(inven->pop_front() == true);

    assert(inven->isEmpty() == true);

    cerr << " Loading 4 items..." << endl;
    stringstream inbuffer2;
    inbuffer2.str(
            "11000 Sprite 1.29 20\n"
            "11001 DietSprite 0.99 21\n"
            "11002 Crush 1.19 22\n"
            "11003 DietCrush 0.89 23\n"
    );
    assert(inven->load(inbuffer2) == 4);

    cerr << " Loading 3 more items..." << endl;
    stringstream inbuffer3;
    inbuffer3.str(
            "12000 Spam 3.19 50\n"
            "12001 SpamLite 3.19 40\n"
            "12003 SpamBacon 3.49 20\n"
    );
    assert(inven->load(inbuffer3) == 3);

    cerr << " Checking findNodeBy functions..." << endl;
    cerr << "  Checking findNodeByID..." << endl;
    assert(inven->findNodeByID(11000) != nullptr);
    assert(inven->findNodeByID(11001) != nullptr);
    assert(inven->findNodeByID(11002) != nullptr);
    assert(inven->findNodeByID(11003) != nullptr);
    assert(inven->findNodeByID(12000) != nullptr);
    assert(inven->findNodeByID(12001) != nullptr);
    assert(inven->findNodeByID(12003) != nullptr);
    assert(inven->findNodeByID(11001)->getItem() != nullptr);
    assert(inven->findNodeByID(11001)->getItem()->getName() == "DietSprite");
    assert(inven->findNodeByID(11003)->getItem() != nullptr);
    assert(inven->findNodeByID(11003)->getItem()->getName() == "DietCrush");
    assert(inven->findNodeByID(12001)->getItem() != nullptr);
    assert(inven->findNodeByID(12001)->getItem()->getName() == "SpamLite");
    assert(inven->findNodeByID(20000) == nullptr);
    assert(inven->findNodeByID(0) == nullptr);

    cerr << "  Checking findNodeByName..." << endl;
    assert(inven->findNodeByName("Spam") != nullptr);
    assert(inven->findNodeByName("Spam")->getItem() != nullptr);
    assert(inven->findNodeByName("Spam")->getItem()->getID() == 12000);
    assert(inven->findNodeByName("SpamBacon") != nullptr);
    assert(inven->findNodeByName("SpamBacon")->getItem() != nullptr);
    assert(inven->findNodeByName("SpamBacon")->getItem()->getID() == 12003);
    assert(inven->findNodeByName("Crush") != nullptr);
    assert(inven->findNodeByName("Crush")->getItem() != nullptr);
    assert(inven->findNodeByName("Crush")->getItem()->getID() == 11002);
    assert(inven->findNodeByName("SPU") == nullptr);

    cerr << "  Checking findItemByID..." << endl;
    assert(inven->findItemByID(11000) != nullptr);
    assert(inven->findItemByID(11001) != nullptr);
    assert(inven->findItemByID(11002) != nullptr);
    assert(inven->findItemByID(11003) != nullptr);
    assert(inven->findItemByID(12000) != nullptr);
    assert(inven->findItemByID(12001) != nullptr);
    assert(inven->findItemByID(12003) != nullptr);
    assert(inven->findItemByID(11000)->getName() == "Sprite");
    assert(inven->findItemByID(11002)->getName() == "Crush");
    assert(inven->findItemByID(12003)->getName() == "SpamBacon");

    cerr << "  Checking findItemByName..." << endl;
    assert(inven->findItemByName("Sprite") != nullptr);
    assert(inven->findItemByName("DietSprite") != nullptr);
    assert(inven->findItemByName("Crush") != nullptr);
    assert(inven->findItemByName("DietCrush") != nullptr);
    assert(inven->findItemByName("Spam") != nullptr);
    assert(inven->findItemByName("SpamLite") != nullptr);
    assert(inven->findItemByName("SpamBacon") != nullptr);
    assert(inven->findItemByName("BottledWater") == nullptr);
    assert(inven->findItemByName("GranulatedSugar") == nullptr);
    assert(inven->findItemByName("BakingSoda") == nullptr);
    assert(inven->findItemByName("Pikachu") == nullptr);
    assert(inven->findItemByName("Crush")->getPrice() == 1.19);
    assert(inven->findItemByName("DietCrush")->getPrice() == 0.89);
    assert(inven->findItemByName("Spam")->getPrice() == 3.19);

    cerr << " Checking stockIn..." << endl;
    assert(inven->stockIn(11002, 50) == 72);
    assert(inven->findItemByID(11002)->getQuantity() == 72);
    assert(inven->stockIn(12000, 11) == 61);
    assert(inven->findItemByID(12000)->getQuantity() == 61);

    cerr << " Checking stockOut..." << endl;
    assert(inven->stockOut(11003, 3) == 3);
    assert(inven->findItemByID(11003)->getQuantity() == 20);
    assert(inven->stockOut(12001, 30) == 30);
    assert(inven->findItemByID(12001)->getQuantity() == 10);
    assert(inven->stockOut(12001, 30) == 10);
    assert(inven->findItemByID(12001)->getQuantity() == 0);

    cerr << " Checking addNewItem..." << endl;
    item = new Item(11002, "SomethingBad", 199.99, 30);
    assert(inven->addNewItem(item) == false);
    assert(inven->findItemByID(11002) != item);

    item2 = new Item(11004, "CanadaDry", 1.09, 30);
    assert(inven->addNewItem(item2) == true);
    assert(inven->findItemByID(11004) == item2);

    cerr << " Checking deleteItem..." << endl;
    assert(inven->deleteItem(11000) == true);
    assert(inven->findItemByName("Sprite") == nullptr);
    assert(inven->findItemByID(11000) == nullptr);
    assert(inven->findItemByID(11001) != nullptr);
    assert(inven->findItemByID(11002) != nullptr);
    assert(inven->findItemByID(11003) != nullptr);
    assert(inven->findItemByID(11004) != nullptr);
    assert(inven->findItemByID(12000) != nullptr);
    assert(inven->findItemByID(12001) != nullptr);
    assert(inven->findItemByID(12003) != nullptr);

    assert(inven->deleteItem(11000) == false);
    assert(inven->deleteItem(12001) == true);
    assert(inven->findItemByID(11000) == nullptr);
    assert(inven->findItemByID(11001) != nullptr);
    assert(inven->findItemByID(11002) != nullptr);
    assert(inven->findItemByID(11003) != nullptr);
    assert(inven->findItemByID(11004) != nullptr);
    assert(inven->findItemByID(12000) != nullptr);
    assert(inven->findItemByID(12001) == nullptr);
    assert(inven->findItemByID(12003) != nullptr);

    assert(inven->deleteItem(11001) == true);
    assert(inven->deleteItem(11003) == true);
    assert(inven->deleteItem(12000) == true);

    assert(inven->findItemByID(11000) == nullptr);
    assert(inven->findItemByID(11001) == nullptr);
    assert(inven->findItemByID(11002) != nullptr);
    assert(inven->findItemByID(11003) == nullptr);
    assert(inven->findItemByID(11004) != nullptr);
    assert(inven->findItemByID(12000) == nullptr);
    assert(inven->findItemByID(12001) == nullptr);
    assert(inven->findItemByID(12003) != nullptr);

    cerr << " Checking formattedPrint function..." << endl << endl;

    stringstream yourOutput;
    inven->formattedPrint(yourOutput);

    stringstream keyOutput;
    keyOutput << left << fixed << setprecision(2);
    keyOutput << setw(6) << "11002" << setw(12) << "Crush";
    keyOutput << setw(8) << "1.19" << setw(4) << "72" << endl;
    keyOutput << setw(6) << "12003" << setw(12) << "SpamBacon";
    keyOutput << setw(8) << "3.49" << setw(4) << "20" << endl;
    keyOutput << setw(6) << "11004" << setw(12) << "CanadaDry";
    keyOutput << setw(8) << "1.09" << setw(4) << "30" << endl;

    cerr << "expected:" << endl;
    cerr << keyOutput.str();
    cerr << endl;
    cerr << "yours:" << endl;
    cerr << yourOutput.str();
    cerr << endl;

    assert(keyOutput.str() == yourOutput.str());

    cerr << "Inventory class test finished." << endl;
    cerr << endl;
    cerr << "Unit Test passed. Congratulations!" << endl;

    return 0;
}
