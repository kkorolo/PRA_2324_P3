#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //miembros privados
        int nelem;
        BSNode<T> *root;
        //Búsqueda de elementos

        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n==nullptr){
                throw std::runtime_error("Element not found");
            }
            else if(n->elem<e){
                return search(n->right,e);
            }
            else if(n->elem>e){
                return search(n->left,e);
            }
            else{
                return n;
            }
        };
        //Inserción de elementos
        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n==nullptr){
                return new BSNode<T>(e);
            }
            else if(e<n->elem){
                n->left=insert(n->left,e);
            }
            else if(e>n->elem){
                n->right=insert(n->right,e);
            }
            else{
                throw std::runtime_error("Element is a duplicate");
            }
            return n;
        }
        // Recorrido e impresión del árbol
        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if(n!=nullptr){
               print_inorder(out,n->left);
               out<<n->elem<<"\n";
               print_inorder(out,n->right);
            }
        }
        //Eliminación de elementos
        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n==nullptr){
                throw std::runtime_error("Element not found");
            }
             else if (n->elem < e){
                n->right=remove(n->right,e);
             }
             else if (n->elem > e){
                n->left=remove(n->left,e);
             }
             else{
                if (n->left != nullptr && n->right != nullptr){
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                    
                } // 2 desc.
                else{
                    n = (n->left != nullptr)? n->left : n->right;
                } // 1 ó 0 descendientes

             }
             return n;
        }
        T max(BSNode<T>* n) const{
            if (n==nullptr){
                throw std::runtime_error("Element not found");
            }
            else if(n->right!=nullptr){
                return max(n->right);
            }
            else {return n->elem;}
        }
        BSNode<T>* remove_max(BSNode<T>* n){
            if(n->right==nullptr){
                return n->left;
            }
            else{
                n->right=remove_max(n->right);
                return n;
            }
        }
        //destruccion
        void delete_cascade(BSNode<T>* n){
            if(n!=nullptr){
                delete_cascade(n->left);
                delete n;
                delete_cascade(n->right);
                delete n;
            }
        }
    public:
        // miembros públicos
        //Creación y tamaño
        BSTree(){
            this->nelem=0;
            this->root=nullptr;
        }
        int size() const{
            return nelem;
        }
        //Búsqueda de elementos
        T search(T e) const{
            return search(root, e)->elem;
        }
        T operator[](T e) const{
            return search(e);
        }
        //Inserción de elementos
        void insert(T e){
            root=insert(root,e);
            nelem++;
        }
        // Recorrido e impresión del árbol
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }
        //Eliminación de elementos
        void remove(T e){
            root=remove(this->root, e);
            nelem--;
        }
        // Destrucción
        ~BSTree(){
            delete_cascade(this->root);
        }


};


#endif