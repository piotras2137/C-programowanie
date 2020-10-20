#include <stdio.h>
#include <stdlib.h>

struct binary_node
{
    char symbol;
    unsigned long weight;
    struct binary_node * left;
    struct binary_node * right;
};

void calculate_weight(struct binary_node * tab[256], char * data, unsigned long len)
{
    struct binary_node * temp;
    for(unsigned long i = 0; i<len; i++)
    {
        if(tab[data[i]] == 0)
        {
            temp = (struct binary_node*)malloc(sizeof(struct binary_node));
            temp->symbol = data[i];
            temp->weight = 1;
            temp->left = 0;
            temp->right = 0;
            tab[data[i]] = temp;
        }
        else
            tab[data[i]]->weight++;
    }
}

struct binary_node * create_binary_tree(struct binary_node * tab[256])
{
    struct binary_node ** op_table;
    unsigned long nodes = 0;

    for(unsigned long i = 0; i<256; i++)
        if(tab[i] != 0)
            nodes++;

    op_table = (struct binary_node**)malloc(sizeof(struct binary_node)*nodes);

    unsigned long node_iter = 0;
    for(unsigned long i = 0; i<256; i++)
    {
        if(tab[i] != 0)
        {
            op_table[node_iter] = tab[i];
            node_iter++;
        }
    }

    struct binary_node * min1;
    struct binary_node * temp;
    unsigned long pos;
    unsigned long i;
    while(node_iter > 1)
    {
        min1 = op_table[0];
        pos = 0;

        for(i = 1; i<nodes; i++)
        {
            if(op_table[i] != 0 && op_table[i]->weight < min1->weight)
            {
                min1 = op_table[i];
                pos = i;
            }
        }

        op_table[pos] = 0;
        temp = (struct binary_node*)malloc(sizeof(struct binary_node));
        temp->weight = min1->weight;
        temp->left = min1;

        i = 0;
        while(op_table[i] == 0)
            i++;

        min1 = op_table[i];

        for(i = 0; i<nodes; i++)
        {
            if(op_table[i] != 0 && op_table[i]->weight < min1->weight)
            {
                min1 = op_table[i];
                pos = i;
            }
        }
        temp->weight += min1->weight;
        temp->right = min1;
        op_table[pos] = 0;

        i = 0;
        while(op_table[i] != 0)
            i++;

        op_table[i] = temp;
        node_iter--;
    }

    temp = op_table[0];
    free(op_table);
    return temp;
}

void read_binary_tree(struct binary_node * tree, unsigned long code)
{
    if(tree->left != 0)
        read_binary_tree(tree->left, code<<1);
    if(tree->right != 0)
        read_binary_tree(tree->right, (code<<1)+1);
    if(tree->right == 0 && tree->left == 0)
        printf("%c:%u\n", tree->symbol, code);
}

int main()
{

    char data[13] = "aaaaabbbbcccd";
    struct binary_node * test[256] = {0};

    calculate_weight(test, data, 13);

    for(unsigned long i = 0; i<256; i++)
        if(test[i] != 0)
            printf("%c:%u\n", test[i]->symbol, test[i]->weight);

    struct binary_node * test2 = create_binary_tree(test);
    read_binary_tree(test2, 0);

    return 0;
}
