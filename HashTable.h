// #ifndef HASHTABLE_H
// #define HASHTABLE_H

// #include <ostream>
// #include <stdexcept>
// #include "Dict.h"
// #include "TableEntry.h"

// #include "/Users/kyrylo_korolov/Documents/education/UPV/2ndo-IndustryRobot/PRA/practica1Linked/PRA_2324_P1/ListLinked.h"
// template <typename V>
// class HashTable: public Dict<V> {

//     private:
//         int n;
//         int max;
//         ListLinked<TableEntry<V>>* table;
//         int h(std::string key){
//             int suma=0;
//             for(int i=0; i<key.length();i++){
//                 suma+=int(key.at(i));
//             }
//             return suma%max;
//         }


//     public:
//         HashTable(int size){
//             this->table = new ListLinked<TableEntry<V>>[size];
//             this->n = 0;
//             this->max = size;

//         }
//         ~HashTable(){
//             delete[] table;
//         }
//         int capacity(){
//             return max;
//         }
//         //metodos dict
//         void insert(std::string key, V value) override{
//             if(table->search(h(key))==-1){
//                 throw std::runtime_error("Posicion no valida");
//             }
//             else{
//                 TableEntry<V> te1(key,value);
//                 table->insert(h(key),te1);
//             }
//         }
//         V search(std::string key) override{
//             return table->get(h(key));
//         }
//         V remove(std::string key) override{
//             return table->remove(h(key));
//         }
//         int entries() override{
//             return table->size();
//         }
//         //fin metodos dict

//         friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
//             out<<"Hash Map --> \n";
//             for(auto entry : th){
//                 out<<entry<<endl;
//             }
//             out<<"\n";
//             return out;
//         }
//         V operator[](std::string key){
//             return search(key);
//         }




        
        
// };

// #endif
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "/Users/kyrylo_korolov/Documents/education/UPV/2ndo-IndustryRobot/PRA/practica1Linked/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {
private:
    int n = 0;
    int max = 0;
    ListLinked<TableEntry<V>>* table = nullptr;

    int h(const std::string& key) const {
        int suma = 0;
        for (unsigned char c : key) suma += c;
        return (max == 0) ? 0 : (suma % max);
    }

public:
    explicit HashTable(int size) : n(0), max(size), table(new ListLinked<TableEntry<V>>[size]) {}

    ~HashTable() {
        delete[] table;
        table = nullptr;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    int capacity() const { return max; }

    // Dict API
    void insert(const std::string& key, const V& value) override {
        int idx = h(key);
        int pos = table[idx].search(TableEntry<V>(key, V{})); // requires operator== by key
        if (pos == -1) {
            table[idx].append(TableEntry<V>(key, value));
            ++n;
        } else {
            table[idx].remove(pos);
            table[idx].append(TableEntry<V>(key, value));
        }
    }

    V search(const std::string& key) const override {
        int idx = h(key);
        int pos = table[idx].search(TableEntry<V>(key, V{}));
        if (pos == -1) throw std::out_of_range("key not found");
        return table[idx].get(pos).value;
    }

    V remove(const std::string& key) override {
        int idx = h(key);
        int pos = table[idx].search(TableEntry<V>(key, V{}));
        if (pos == -1) throw std::out_of_range("key not found");
        TableEntry<V> e = table[idx].remove(pos);
        --n;
        return e.value;
    }

    int entries() const override { return n; }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "Hash Map -->\n";
        for (int i = 0; i < th.max; ++i) {
            out << i << ": " << th.table[i] << '\n';
        }
        return out;
    }

    V operator[](std::string key) { return search(key); }
};

#endif