#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) //lisgto
{
  TreeMap *map = malloc(sizeof(TreeMap));
  if(map==NULL) return NULL;

  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) //listo
{
  TreeNode *tempNode = tree->root; // primer nodo, raiz
  TreeNode *nuevoNodo = createTreeNode(key,value);

  while(tempNode != NULL) 
  { 
    if(is_equal(tree, key, tempNode->pair->key) ) // la clave ya existe
    {
      return;
    }
    else if(tree->lower_than(key, tempNode->pair->key) ) 
    {
      if (tempNode->left == NULL) 
      {
        tempNode->left = nuevoNodo;
        nuevoNodo->parent = tempNode;
        tree->current = nuevoNodo;
        return;
      } 
      else 
      {
        tempNode = tempNode->left; 
      }
    }
    else 
    {
      if (tempNode->right == NULL) 
      {
        tempNode->right = nuevoNodo;
        nuevoNodo->parent = tempNode;
        tree->current = nuevoNodo;
        return;
      } 
      else 
      {
        tempNode = tempNode->right;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x) //listo?
{
  while( x->left != NULL)
  {
    x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) // listo
{
  TreeNode *tempNode = tree->root; // primer nodo, raiz

  while(tempNode != NULL) // recorremos el arbol
  { 
    if(is_equal(tree, key, tempNode->pair->key) ) // se compara y si es igual se reemplaza
    {
      tree->current = tempNode;
      return tree->current->pair;
    }
    else if(tree->lower_than(key, tempNode->pair->key) ) // si retorna verdadero esta a la izq
    {
      tempNode = tempNode->left; 
    }
    else // si no a la derehca
    {
      tempNode = tempNode->right;
    }

  }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode *min = minimum(tree->root);
  tree->current = min;
  return min->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
