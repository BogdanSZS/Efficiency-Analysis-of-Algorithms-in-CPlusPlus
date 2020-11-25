//
// Created by Bogdan on 23.11.2020.
//

#include "HashTable.h"
#include <exception>
#include <new>

HashTable::HashTable(int size){
    this->bucketTable = new Bucket[size];
    this->numberOfBuckets = size;
}

HashTable::~HashTable(){
    if(this->bucketTable != nullptr) {
        delete (this->bucketTable);
        this->bucketTable = nullptr;
        this->numberOfBuckets = 0;
    }
}

int HashTable::hashFunction(const KeyT &key) const {
    int hashSum = 0;
    std::string::const_iterator itr = key.begin();
    while(itr != key.end()){
        hashSum += *itr;
        itr++;
    }
    return (hashSum % this->numberOfBuckets);
}

int HashTable::getNumberOfBuckets() const {
    return this->numberOfBuckets;
}

void HashTable::printTable(std::ostream &output) { //TODO: delete this function after testing
    output << std::endl;
    for(int i = 0; i < this->getNumberOfBuckets(); i++){
        Bucket &currentBucket = this->bucketTable[i];
        auto value = (const std::string*)currentBucket.getHeadElement();
        const std::string &key = currentBucket.getKey();
        if(key.empty()){
            output << "Empty bucket" << std::endl;
        }
        else {
            output << key << " : " << *value << std::endl;
        }
    }
}

int HashTable::Iterator::computeIndex() const {
    const int size = this->hashTable->getNumberOfBuckets();
    const int quadraticProbing = this->i * this->i;
    return (this->hashValue + quadraticProbing) % size;
}

HashTable::Bucket* HashTable::findFirstAvailableBucket(const KeyT &key) const {             //Transversal iterator
    Iterator iterator(this, key);
    while(!iterator.isLast()){
        if(iterator.getCurrentBucket()->isBucketAvailable()){
            return iterator.getCurrentBucket();
        }
        iterator.goToNext();
    }
    return nullptr;
}

void HashTable::insert(const KeyT &key, void *newElement){
    if(newElement){
        Bucket *destinationBucket = findFirstAvailableBucket(key);
        if(destinationBucket == nullptr) {
            throw std::bad_alloc(); //TODO: find a more specific exception
            //fprintf(stderr, "ERROR, HASH TABLE CAPACITY REACHED\n");
            //throw and exception
        }
        destinationBucket->setHeadElement(key, newElement);
    }
    else{
        throw std::bad_alloc();   //TODO: find a more specific exception
        //fprintf(stderr, "NO MEMORY AVAILABLE FOR CREATING THIS NEW STUDENT\n");
        //throw an exception
    }
}

