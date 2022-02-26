#ifndef BLOCKCHAIN_NODES_H
#define BLOCKCHAIN_NODES_H

#include "../blocks/my_blocks.h"

typedef struct node_s {
    int nid;
    block* chain;
    struct node_s* next;
} node;

int count_nodes(node* _node_head);
node* get_last_node(node* _node_head);
node* get_node(int _nid, node* _node_head);
node* get_node_before(int _nid, node* _node_head);
bool node_check_name(int _nid, node* _node_head);
node* add_node(char* _name, node* _node_head);
void free_node(node* _node);
void free_node_all(node* _node_head);
int rm_node(char* _name, node* _node_head);
int add_block_to_node(char* _bid, char* _nid, node* _node_head);
int add_block_to_all_nodes(char* _bid, node* _node_head);
bool is_synced(node*_node_head);
int rm_block_all(char* _bid, node* _node_head);
bool sync_all(node* _node_head);
int list_nodes(bool with_blocks, node* _node_head);
bool nodes_unload(node* _node_head, char* _path);
bool nodes_load(node* _node_head, char* _path);

#endif