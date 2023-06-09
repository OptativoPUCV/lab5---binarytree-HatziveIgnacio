#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) // lisgto
{
  TreeMap *map = malloc(sizeof(TreeMap));
  if (map == NULL)
    return NULL;

  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;
  return map;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) // listo
{
  TreeNode *tempNode = tree->root; // primer nodo, raiz
  TreeNode *nuevoNodo = createTreeNode(key, value);

  while (tempNode != NULL) {
    if (is_equal(tree, key, tempNode->pair->key)) // la clave ya existe
    {
      return;
    } else if (tree->lower_than(key, tempNode->pair->key)) {
      if (tempNode->left == NULL) {
        tempNode->left = nuevoNodo;
        nuevoNodo->parent = tempNode;
        tree->current = nuevoNodo;
        return;
      } else {
        tempNode = tempNode->left;
      }
    } else {
      if (tempNode->right == NULL) {
        tempNode->right = nuevoNodo;
        nuevoNodo->parent = tempNode;
        tree->current = nuevoNodo;
        return;
      } else {
        tempNode = tempNode->right;
      }
    }
  }
}

TreeNode *minimum(TreeNode *x) // listo?
{
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

void removeNode(TreeMap *tree, TreeNode *node) // listo
{
  if (node->left == NULL && node->right == NULL) // caso 1, sin hijos // listo
  {
    if (node->parent->left == node) // en la izq
    {
      node->parent->left = NULL;
    } else if (node->parent->right == node) // o derecha
    {
      node->parent->right = NULL;
    }
    return;
  }
  /////////////////

  /////////////////
  if (node->left == NULL || node->right == NULL) // Caso 2, con un hijo // listo
  {
    //
    TreeNode *hijo;
    if (node->left == NULL) // Aux para ver cual debe ser, el izq o derecho
    {
      hijo = node->right; // si el izq es null, deberia ir en el derecho
    } else {
      hijo = node->left; // al contrario
    }
    //

    if (node == tree->root) // es la raiz
    {
      tree->root = hijo;
      hijo->parent = NULL; // no existe padre
      return;
    }
    // cambio de padre
    hijo->parent = node->parent;
    // se ve en que posicion del padre debe estar
    if (hijo == node->parent->left) {
      node->parent->left = hijo;
    } else {
      node->parent->right = hijo;
    }
    return;
  }
  /////////////////

  ///////////////// Caso 3, dos hijos, ver el minimo de la rama derecha y
  /// reemplazar
  TreeNode *minomoDerecho = minimum(node->right);
  node->pair->key = minomoDerecho->pair->key;
  node->pair->value = minomoDerecho->pair->value;
  removeNode(tree, minomoDerecho);

  /////////////////
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) // listo
{
  TreeNode *tempNode = tree->root; // primer nodo, raiz

  while (tempNode != NULL) // recorremos el arbol
  {
    if (is_equal(tree, key,
                 tempNode->pair->key)) // se compara y si es igual se reemplaza
    {
      tree->current = tempNode;
      return tree->current->pair;
    } else if (tree->lower_than(
                   key,
                   tempNode->pair->key)) // si retorna verdadero esta a la izq
    {
      tempNode = tempNode->left;
    } else // si no a la derehca
    {
      tempNode = tempNode->right;
    }
  }
  return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) 
{ 
  TreeNode* current = tree->root;
  TreeNode* ub_node = NULL;

  while (current != NULL) // busqueda
  {
    if (!tree->lower_than(current->pair->key, key)) // falso = izq
    {
      ub_node = current;
      current = current->left;
    } 
    else 
    {
    current = current->right;
    }
  }
  if (ub_node == NULL) return NULL;
  
  return ub_node->pair;
}

Pair *firstTreeMap(TreeMap *tree) // listo
{
  TreeNode *min = minimum(tree->root);
  tree->current = min;
  return min->pair;
}

Pair *nextTreeMap(TreeMap *tree) 
{
  TreeNode* current = tree->current;
  
  if (current == NULL) return NULL;
  
  if (current->right != NULL) // siguiente en la rama derecha
  {
    current = minimum(current->right);
  } 
  else // es el ultimo de la rama derecha, pasamos a la izquierda
  {
    TreeNode* parent = current->parent;
    while ( current->parent != NULL && current ==  current->parent->right)
    {
      current = parent;
      parent = parent->parent;
    }
    current =  current->parent;
  }
  tree->current = current;
  
  if (current != NULL) return current->pair;
  
  return NULL;
}
