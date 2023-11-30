//
// Created by znwan on 2023/11/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;
struct Node{
    int value;
    node *link;
};

int main()
{
//head is a const, and it doesn't contain any value
//temp serves as a container to hold a new node
//cursor is the pointer to travel through the linked list
    node *head, *temp, *cursor;
    head = malloc(sizeof (node));
    head->link = NULL;

    int n;
    scanf("%d", &n);
    while(n--){
        int val;
        scanf("%d", &val);

        temp = malloc(sizeof (node));
        temp->link = NULL;
        temp->value = val;

        cursor = head;
        while(cursor->link != NULL && cursor->link->value < val){
            cursor = cursor->link;
        }
        temp->link = cursor->link;
        cursor->link = temp;

        cursor = head;
        while(cursor->link != NULL){
            printf("%d ", cursor->link->value);
            cursor = cursor->link;
        }
        printf("\n");
    }

    cursor = head;
    while(cursor->link != NULL){
        temp = cursor->link;
        free(cursor);
        cursor = temp;
    }
}










//#define TRUE (1 == 1)
//#define FALSE !TRUE
//
//typedef struct NODE{
//    struct NODE *link;
//    int value;
//}Node, *Linked_list;
//
//int insert(register Linked_list root, int new_value);
//Linked_list init_ll();
//void delete_ll(Linked_list root);
//void display_ll(Linked_list root);
//
//int main(void)
//{
////    n nodes
//    short n;
//    scanf("%hd", &n);
//
////    deal with data in file
////    FILE *file;
////    file = fopen("", "r");
////    if(file == NULL)
////        return -1;
//
////    init_ll();
//    Linked_list root;
//    root = init_ll();
////    Node **linkp = &root;//prepare for insertion
//    while(n--) {
//        int data;
////        fread(&data, sizeof (int), 1, file);
//        scanf("%d", &data);
//        if(insert(root, data) == TRUE)
//            display_ll(root);
//        else
//            break;
//    }
//    delete_ll(root);
////    fclose(file);
//
//    return 0;
//}
//
//Linked_list init_ll()
//{
//    Node *root = NULL;
////    root = (Node*)malloc(sizeof (Node));
////    if(root == NULL)
////        exit(-1);
////    root->link = NULL;
//    return root;
//}
//
//int insert(Node *root, int new_value)
//{
//    Node *current, *tmp;
//    Node *new_node;
//
//    new_node = (Node *) malloc(sizeof (Node));
//    if(new_node == NULL){
//        return FALSE;
//    }
//    new_node->value = new_value;
//    if(root == NULL){
//        root = new
//    }
//    while((current = root) != NULL && current->link->value < new_value){
//        current = current->link;
//    }
//    tmp = current;
//    new_node = tmp;
//    new_node->link = current->link;
//
//
//
//    return TRUE;
//}
//
////int insert(const Linked_list root, int new_value)
////{
////    if(root->link == NULL){
////        root->value = new_value;
////    }else{
////        while ()
////    }
////}
//
//void delete_ll(Linked_list root)
//{
//    Linked_list tmp1 = root, tmp2 = root;
//    while(tmp1->link != NULL){
//        tmp1 = tmp1->link;
//        free(tmp2);
//        tmp2 = tmp1;
//    }
//}
//
//void display_ll(Linked_list root)
//{
//    Linked_list tmp = root;
//    while (tmp != NULL){
//        printf("%d", tmp->value);
//        tmp = tmp->link;
//    }
//    printf("\n");
//}
