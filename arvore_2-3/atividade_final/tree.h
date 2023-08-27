#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef struct link Link;

TreeNode* balancear(TreeNode* aux);
TreeNode* insert_in_root(int key, TreeNode* arvore);
TreeNode* create(int key, TreeNode* dad);

struct TreeNode{
    int keys[3];
    int num_keys;
    TreeNode* children[3];   //children[menor que todas as chaves, entre as chaves, maior qur todas as chaves]
    TreeNode* father;
};

TreeNode* insert(int key, TreeNode* arvore)
{
    TreeNode* aux = arvore;
    int find_pos = 1;
    //Caso a inserção ocorre na nó raiz da arvore
    if(aux->father == NULL && aux->children[0] == NULL && aux->children[1] == NULL && aux->children[2] == NULL)
    {
        return insert_in_root(key, arvore);
    }
    
    //Caso não ,inicia um loop buscando uma posição na arvore
    while(find_pos)
    {
        //Se a chave a ser inseria é menor que a chave de menor valor do nó pai, então vai para o galho esquerdo se esse for não nulo
        if(key < aux->keys[0] && aux->children[0] != NULL)
        {
            aux = aux->children[0];
        }
        //Se a chave a ser inseria é maior que a chave de menor valor do nó pai e menor que a chave de maior valor do nó pai, então vai para o galho intermediário se esse for não nulo
        else if(key > aux->keys[0] && key < aux->keys[1] && aux->children[1] != NULL)
        {
            aux = aux->children[1];
        }
        //Se a chave a ser inseria é maior que a chave de maior valor do nó pai, então vai para o galho direito se esse for não nulo
        else if(key > aux->keys[2] && aux->children[2] != NULL)
        {
            aux = aux->children[2];
        }
        //Caso encontre um  nó não nulo, e com apenas uma chave, então adicione key a esse nó.
        else if(aux->num_keys == 1)
        {
            aux->keys[1] = key;
            aux->num_keys+=1;
            aux = balancear(aux);
            find_pos = 0;
        }
        //Caso encontre um nó não nulo, com duas chaves nele.
        else if(aux->num_keys == 2 && aux->father != NULL)
        {
            TreeNode* temp;
            aux = insert_in_root(key, aux);
            //Inseri um valor no nó da arvore, e se o nó atingir tamanho 3, então divide os em três nós
            /*
            Exemplo: no(2,3), insiro o 4, então fica no(2,3,4), isso não pode ocorrer, logo é transformado em:
            O novo nó pai:              ------3------
                                        |           |
            Os novos nós filhos:        2           4
            */
            temp = aux->father;

            //Caso esse nó tenha um nó pai simples(apenas uma chave)
            if(temp->num_keys == 1)
            {
                //Caso esse nó seja maior que a chave do nó pai
                if(aux->keys[0] > temp->keys[0])
                {
                    temp->keys[1] = aux->keys[0];
                    temp->children[1] = aux->children[0];
                    temp->children[1]->father = temp;
                    temp->children[2] = aux->children[2];
                    temp->children[2]->father = temp;
                    temp->num_keys+=1;
                    free(aux);
                    aux = NULL;
                }

                //Caso esse nó seja menor que a chave do nó pai
                else if(aux->keys[0] < temp->keys[0])
                {    
                    temp->keys[1] = temp->keys[0];
                    temp->keys[0] = aux->keys[0];

                    temp->children[0] = aux->children[0];
                    temp->children[0]->father = temp;
                    temp->children[1] = aux->children[2];
                    temp->children[1]->father = temp;
                    temp->num_keys+=1;
                    
                    free(aux);
                    aux = NULL; 
                }

            }

            //Caso o nó possui um nó pai duplo
            else if(temp->num_keys == 2)
            {   
                TreeNode* temp_2 ;

                //Caso a chave seja maior que o nó de maior valor do nó pai
                if(aux->keys[0] > temp->keys[1])
                {
                    
                    temp_2 = create(temp->keys[0], temp);
                    temp_2->keys[0] = temp->keys[0];

                    temp->keys[0] = temp->keys[1];
                    temp->keys[1] = 0;

                    temp_2->children[0] = temp->children[0];
                    temp_2->children[2] = temp->children[1];

                    temp_2->children[0]->father = temp_2;
                    temp_2->children[2]->father = temp_2;

                    temp->children[0] = temp_2;
                    temp->children[2] = aux;
                    temp->children[1] = NULL;

                    temp->num_keys = 1;

                    
                }
                //Caso a chave seja menor que o nó de menor valor do nó pai
                else if(aux->keys[0] < temp->keys[0])
                {
                    temp_2 = create(temp->keys[1], temp);
                    temp_2->keys[0] = temp->keys[1];

                    temp->keys[1] = 0;

                    temp_2->children[0] = temp->children[1];
                    temp_2->children[2] = temp->children[2];

                    temp_2->children[0]->father = temp_2;
                    temp_2->children[2]->father = temp_2;
                    
                    
                    temp->children[0] = aux;
                    temp->children[1] = NULL;

                    temp->children[2] = temp_2;
                    temp->num_keys = 1;
                }
                //Caso a chave seja intermediária
                else if(aux->keys[0] > temp->keys[0] && aux->keys[0] < temp->keys[1])
                {
                    temp = insert_in_root(aux->keys[0],temp);
                    temp->children[0]->children[2] = aux->children[0];
                    temp->children[2]->children[0] = aux->children[2];
                    temp->children[1] = NULL;
                    free(aux);

                }   
            }
            find_pos = 0 ;
        }
       
    }
    return arvore;
    

}

//Funções auxiliares

TreeNode* create(int key, TreeNode* dad)
{
    TreeNode* temp;
    temp = (TreeNode*) malloc(sizeof(TreeNode));
    for(int i= 0; i < 3; i++)
    {
        temp->keys[i] = 0;
        temp->children[i] = NULL;
    }
    temp->keys[0] = key;
    temp->father = dad;
    temp->num_keys = 1;
    return temp;
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
    else if(arvore->num_keys == 2)
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
    if (aux->num_keys == 2)
    {
        // Caso o nó tenha duas chaves, ordene-as
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
        return aux;
    }
    else if (aux->num_keys == 3)
    {
        // Caso o nó tenha três chaves, ordene-as
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
        if (aux->keys[1] > aux->keys[2])
        {
            int temp = aux->keys[1];
            aux->keys[1] = aux->keys[2];
            aux->keys[2] = temp;
        }
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
    }

    return aux;
}



