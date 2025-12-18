#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;
template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
            tree=new BSTree<TableEntry<V>>();
        }
        ~BSTreeDict(){
            delete tree;
        }
        int entries()override{
            return tree->size();
        }
        void insert(string key, V value) override{
            tree->insert(TableEntry<V>(key,value));
        }
        V search(string key) override{
            return tree->search(TableEntry<V>(key)).value;
        }
        V remove(string key) override{
            V value=tree->search(TableEntry<V>(key)).value;
            tree->remove(TableEntry<V>(key));
            return value;
        }
        V operator[](std::string key){
            return tree->search(TableEntry<V>(key)).value;
        }
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out<<*(bs.tree);
            return out;
        }





        
};

#endif