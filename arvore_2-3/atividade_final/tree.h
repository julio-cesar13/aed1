#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef struct link Link;

TreeNode* balancear(TreeNode* aux);
TreeNode* insert_in_root(int key, TreeNode* arvore);

struct TreeNode{
    int keys[3];
    int num_keys;
    TreeNode* children[3];
    TreeNode* father;
};

TreeNode* create(int key, TreeNode* dad)
{
    TreeNode* temp;
    temp = (TreeNode*) malloc(sizeof(TreeNode));
    for(int i= 0; i < 3; i++)
    {
        temp->children[i] = NULL;
    }
    temp->keys[0] = key;
    temp->father = dad;
    temp->num_keys = 1;
    return temp;
}

TreeNode* insert(int key, TreeNode* arvore)
{
    TreeNode* aux = arvore;

    if(aux->father == NULL && aux->children[0] == NULL && aux->children[1] == NULL && aux->children[2] == NULL)
    {
        return insert_in_root(key, arvore);
    }

    while(1)
        {
        if(key < aux->keys[0] && aux->children[0] != NULL)
        {
            aux = aux->children[0];
        }
        else if(key > aux->keys[0] && aux->children[2] != NULL)
        {
            aux = aux->children[2];
        }
        else if(aux->num_keys == 1)
        {
            aux->keys[1] = key;
            aux = balancear(aux);
            aux->num_keys+=1;
            return arvore;
        }
        else if(aux->num_keys == 2 && aux->father != NULL)
        {
            TreeNode* temp;
            aux = insert_in_root(key, aux);
            temp = aux->father;
            if(temp->num_keys == 1 && aux->keys[0] > temp->keys[0])
            {
                temp->keys[1] = aux->keys[0];
                temp->children[1] = aux->children[0];
                temp->children[2] = aux->children[2];
                temp->num_keys+=1;
                return arvore;
            }
            else if(temp->num_keys == 1 && aux->keys[0] < temp->keys[0])
            {
                temp->keys[1] = temp->keys[0];
                temp->keys[0] = aux->keys[0];
                temp->children[0] = aux->children[0];
                temp->children[1] = aux->children[2];
                temp->num_keys+=1;
                aux = NULL;
                return arvore;
            }
            else if(temp->num_keys == 2 && aux->keys[0] > temp->keys[1])
            {   

                TreeNode* temp_2 ;
                temp_2 = create(temp->keys[0], temp);
                temp_2->keys[0] = temp->keys[0];
                temp->keys[0] = temp->keys[1];
                temp_2->children[0] = temp->children[0];
                temp_2->children[2] = temp->children[1];
                temp->children[0] = temp_2;
                temp->children[2] = aux;
                temp->num_keys = 1;

                return arvore;
                
            }
            else if(temp->num_keys == 2 && aux->keys[0] > temp->keys[2])
            {
                temp->keys[2] = aux->keys[0];
                temp->num_keys+=1;
                free(aux);
                aux = temp;
            }
        }
        else if(aux->num_keys == 2 && aux->father != NULL)
        {

        }
    }
    

}


TreeNode* insert_in_root(int key, TreeNode* arvore)
{
    if( arvore->num_keys == 1)
    {
        arvore->num_keys += 1;
        arvore->keys[1] = key;
        arvore = balancear(arvore);
        return arvore;
    }
    else if( arvore->num_keys == 2)
    {   
        arvore->num_keys += 1;
        arvore->keys[2] = key;
        arvore = balancear(arvore);

        TreeNode* menor = (TreeNode*) malloc(sizeof(TreeNode));
        TreeNode* maior = (TreeNode*) malloc(sizeof(TreeNode));

        menor = create(arvore->keys[0], arvore);
        maior = create(arvore->keys[2], arvore);

        arvore->keys[0] = arvore->keys[1];
        arvore->keys[1] = 0; 
        arvore->keys[2] = 0;
        arvore->children[0] = menor;
        arvore->children[2] = maior;
        arvore->num_keys = 1;

        return arvore;
    }
}

TreeNode* balancear(TreeNode* aux)
{
    if(aux->num_keys == 2)
    {
        if(aux->keys[0] > aux->keys[1])
        {
            int temp;
            temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
            return aux;
        }
        else
            return aux;

    }
    else
    {
         if(aux->keys[0] < aux->keys[1] && aux->keys[1] < aux->keys[2])
        {
             return aux;
        }
        else if(aux->keys[0] < aux->keys[1] && aux->keys[1] > aux->keys[2])
        {
             int temp;
             temp = aux->keys[1];
             aux->keys[1] = aux->keys[2];
             aux->keys[1] = temp;
             return aux;
        }
        else if(aux->keys[0] > aux->keys[1] && aux->keys[1] < aux->keys[2])
        {
             int temp;
             temp = aux->keys[0];
             aux->keys[0] = aux->keys[1];
             aux->keys[1] = temp;
             return aux;
        }
        else
        {
             int temp;
             temp = aux->keys[0];
             aux->keys[0] = aux->keys[2];
             aux->keys[2] = temp;

             temp = aux->keys[1];
             aux->keys[1] = aux->keys[2];
             aux->keys[2] = temp;
             
             return aux;
        }
    
    }
}


