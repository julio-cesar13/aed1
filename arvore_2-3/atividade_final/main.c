#include "tree.h"

int main(int argc, char*argv)
{
    TreeNode* arvore;
    arvore = create(10, NULL);

    int inserir[] = {5,15,3,7,12,18,2,4,14};

    for(int i = 0; i < 9; i++)
    {
        arvore = insert(inserir[i], arvore);
    }
}