#include "tree.h"

int main(int argc, char*argv)
{
    TreeNode* arvore;
    arvore = create(5, NULL);

    int inserir[] = {3,7,8,9,10,11};

    for(int i = 0; i < 6; i++)
    {
        arvore = insert(inserir[i], arvore);
    }
}