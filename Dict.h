#ifndef DICT_H
#define DICT_H
#include <string>
template <typename V>
class Dict
{
public:
    virtual void insert(std::string key, V value);/*Inserta el par key->value en el diccionario. 
    Lanza una std::runtime_error si key ya existe en el diccionario.*/
    virtual V search(std::string key);/*Busca el valor correspondiente a key. Devuelve el value asociado si key está en diccionario. 
            Si no se encuentra, lanza una std::runtime_error.*/
    virtual V remove(std::string key);/*Elimina el par key->value si se encuentra en el diccionario. 
    Si no se encuentra, lanza una std::runtime_error*/
    virtual int entries();//Devuelve el número de elementos que tiene el Diccionario.
};
#endif


