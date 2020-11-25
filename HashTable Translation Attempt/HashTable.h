//
// Created by Bogdan on 23.11.2020.
//

#ifndef C___HASH_TABLE_HASHTABLE_H
#define C___HASH_TABLE_HASHTABLE_H
#include <iostream>
#include <string>

class HashTable {

private:
    typedef std::string KeyT;
    const static int ENTSCHAIDUNG_FACTOR = 10;
    class Bucket{

    private:
        bool visited;
        void *headElement;
        KeyT key;

    public:
        Bucket(){
            this->visited = false;
            this->headElement = nullptr;
        }

        ~Bucket(){
            if(this->headElement != nullptr){
                this->headElement = nullptr;
                this->visited = false;
            }
        }

        bool getVisitedStatus() const {
            return this->visited;
        }

        void setVisitedStatus(bool logicValue){
            this->visited = logicValue;
        }

        const void* getHeadElement() const {
            return this->headElement;
        }

        bool isBucketAvailable() const {
            return (this->headElement == NULL);
        }

        void setHeadElement(const KeyT &key, void *newHeadElement){
            this->headElement = newHeadElement;
            this->key = key;
        }

        const KeyT &getKey() const {
            return this->key;
        }

    };

    Bucket *findFirstAvailableBucket(const KeyT &key) const;

    int numberOfBuckets;
    Bucket *bucketTable;

public:

    HashTable(int size);
    ~HashTable();
    int hashFunction(const KeyT &key) const;
    int getNumberOfBuckets() const;
    void insert(const KeyT &key, void *newElement);
    void printTable(std::ostream &output);

    class Iterator{

    private:
        int i;
        int visitCount;
        int hashValue;
        Bucket *currentBucket;
        const HashTable *hashTable;

        int computeIndex() const;

    //move all the function implementations to the .cpp file
    public:
        Iterator(const HashTable *table, const KeyT &key){
            this->i = 0;
            this->hashTable = table;
            this->hashValue = this->hashTable->hashFunction(key);
            const int bucketIndex = this->computeIndex();
            this->currentBucket = &(this->hashTable->bucketTable[bucketIndex]);
        }

        bool isLast() const {
            const int size = this->hashTable->getNumberOfBuckets();
            if(this->visitCount == size) return true;
            if(this->i > size) return true;
            return false;
        }

//* HashTable::ENTSCHAIDUNG_FACTOR

        void goToNext(){
            this->i++;
            const int bucketIndex = this->computeIndex();
            this->currentBucket = &(this->hashTable->bucketTable[bucketIndex]);
            if(!this->currentBucket->getVisitedStatus()) {
                this->currentBucket->setVisitedStatus(true);
                this->visitCount++;
            }
        }

        void print(std::ostream &output){
            output << std::endl;
            const std::string* value =
                    (const std::string*)this->currentBucket->getHeadElement();
            output << *value << " i = " << this->i << std::endl;
        }

        Bucket *getCurrentBucket(){
            return this->currentBucket;
        }
    };
};

#endif //C___HASH_TABLE_HASHTABLE_H
