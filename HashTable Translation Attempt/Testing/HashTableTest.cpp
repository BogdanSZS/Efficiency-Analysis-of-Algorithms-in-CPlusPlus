//
// Created by Bogdan on 23.11.2020.
//

#include <iostream>
#include "../HashTable.h"

void constructionTest(){
    std::cout << "constructionTest";
    auto *table = new HashTable(10);
    delete(table);
    std::cout << " PASSED" << std::endl;
}

void iteratorConstructionTest(){
    std::cout << "iteratorConstructionTest";
    auto *table = new HashTable(10);

    std::string value1("Ice-cream");
    std::string value2("Cake");
    std::string value3("Tart");
    std::string value4("Collision1");
    std::string value5("Collision2");
    std::string value6("Collision3");

    table->insert("Chocolate", &value1);
    table->insert("Vanilla", &value2);
    table->insert("Strawberry", &value3);
    table->insert("allinaV", &value4);
    table->insert("niValla", &value5);
    table->insert("allainV", &value6);

    HashTable::Iterator it(table, "Vanilla");

    //while(!it.isLast()){
    //    it.print(std::cout);
    //    it.goToNext();
    //}

    table->printTable(std::cout);

    delete(table);
    std::cout << " PASSED" << std::endl;
}

int main(){
    std::cout << "Beginning of test" << std::endl;
    constructionTest();
    iteratorConstructionTest();
    std::cout << "End of test" << std::endl;

    return 0;
}