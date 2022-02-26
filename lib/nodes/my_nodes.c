#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../error_handler/error_handler.h"
#include "../strings/strings.h"
#include "my_nodes.h"

int count_nodes(node* _node_head){
    node* hold = _node_head;
    int count = 1;
    if(_node_head->nid == -1){
        return 0;
    } else {
        while(hold->next != NULL){
            hold = hold->next;
            count++;
        }
    }
    return count;
}

node* get_last_node(node* _node_head){
    node* hold = _node_head;
    int count = 1;
    if(_node_head->nid == -1){
        return _node_head;
    } else {
        while(hold->next != NULL){
            hold = hold->next;
            count++;
        }
    }
    return hold;
}

node* get_node(int _nid, node* _node_head){
    node* hold = _node_head;
    if(_node_head->nid == _nid){
        return _node_head;
    } else {
        while(hold->next != NULL){
            hold = hold->next;
            if(hold->nid == _nid){
                return hold;
            }
        }
    }
    return NULL;
}

node* get_node_before(int _nid, node* _node_head){
    node* hold = _node_head;
    node* old_hold;
    if(_node_head->nid == _nid){
        return NULL;
    } else {
        old_hold = hold;
        while(hold->next != NULL){
            old_hold = hold;
            hold = hold->next;
            if(hold->nid == _nid){
                return old_hold;
            }
        }
    }
    return NULL;
}

bool node_check_name(int _nid, node* _node_head){
    node* hold = _node_head;
    if(_node_head->nid == _nid){
        return false;
    }
    while(hold->next != NULL){
        hold = hold->next;
        if(hold->nid == _nid){
            return false;
        }
    }
    return true;
}

node* add_node(char* _name, node* _node_head){
    int nid = my_atoi(_name);
    if(nid < 1){
        err_handler(ERR_NODE_NAME);
        return NULL;
    }else if(!node_check_name(nid, _node_head)){
        err_handler(ERR_NODE_EXISTS);
        return NULL;
    }

    if(_node_head->nid == -1){
        _node_head->nid = nid;
        return _node_head; 
    } else {
        node* newnode = malloc(sizeof(node));
        node* last_node = get_last_node(_node_head);
        newnode->nid = nid;
        newnode->chain = NULL;
        newnode->next = NULL;
        last_node->next = newnode;
        return newnode;
    }
    
}

void free_node(node* _node){
    block* hold = _node->chain;
    while(hold != NULL){
        block* next = hold->previous;
        block* rm_block = hold;
        free_block(rm_block);
        hold = next;
    }
    free(_node);
}

void free_node_all(node* _node_head){
    node* hold = _node_head;
    node* del_node = _node_head;
    if(_node_head->nid == -1){
        free(_node_head);
    } else {
        while(hold != NULL){
            del_node = hold;
            hold = hold->next;
            free_node(del_node);
        }
    }
}

int rm_node(char* _name, node* _node_head){
    int nid = my_atoi(_name);
    node* rm_node = get_node(nid, _node_head);

    if(rm_node == NULL){
        err_handler(ERR_NODE_DOESNT_EXIST);
        return 1;
    }

    node* prev_node = get_node_before(nid, _node_head);

    if(prev_node == NULL){
        //fake delete head (modify head to be second node, delete second node), if head is only node set NID -1
        node* next_node = rm_node->next;
        if(next_node == NULL){
            node* del_node = malloc(sizeof(node));
            del_node->chain = rm_node->chain;
            rm_node->chain = NULL;
            rm_node->nid = -1;
            free_node(del_node);
        } else {
            block* hold = rm_node->chain;
            rm_node->nid = next_node->nid;
            rm_node->chain = next_node->chain;
            rm_node->next = next_node->next;
            next_node->chain = hold;
            free_node(next_node);
        }
    } else {
        //delete node
        prev_node->next = rm_node->next;
        free_node(rm_node);
    }
    return 0;
}

int add_block_to_node(char* _bid, char* _nid, node* _node_head){  
    node* node;
    block* block;  
    int nid = my_atoi(_nid);
    if(node_check_name(nid, _node_head)){
        err_handler(ERR_NODE_DOESNT_EXIST);
        return 1;
    } else {
        node = get_node(nid, _node_head);
    }

    block = create_block(_bid, node->chain);

    if(block == NULL){
        return 1;
    } else {
        node->chain = block;
    }

    return 0;
}

bool check_block_name_all(char* _bid, node* _node_head){
    node* node = _node_head;
    while(node != NULL){
        if(!block_check_name(_bid, node->chain)){
            return false;
        }
        node = node->next;
    }
    return true;
}

int add_block_to_all_nodes(char* _bid, node* _node_head){
    node* node = _node_head;
    block* block;  

    if(!check_block_name_all(_bid, _node_head)){
        err_handler(ERR_BLOCK_EXISTS);
        return 1;
    }

    if(!is_alphanum(_bid)){
        err_handler(ERR_BLOCK_NAME);
    }

    while(node != NULL){
        block = create_block(_bid, node->chain);
        if(block == NULL){
            return 1;
        } else {
            node->chain = block;
        }
        node = node->next;
    }
    return 0;
}

bool is_synced(node*_node_head){
    node* hold = _node_head->next;
    while(hold != NULL){
        block* chain_1 = _node_head->chain;
        block* chain_2 = hold->chain;
        while(chain_1 != NULL || chain_2 != NULL){
            if(chain_1 == NULL || chain_2 == NULL){
                return false;
            } else if(my_strcmp(chain_1->bid, chain_2->bid)){
                return false;
            }
            chain_1 = chain_1->previous;
            chain_2 = chain_2->previous;
        }
        hold = hold->next;
    }
    return true;
}

int rm_block_all(char* _bid, node* _node_head){
    node* hold = _node_head;
    bool exists = false;
    while(hold != NULL){
        int num_blocks = count_blocks(hold->chain);
        
        if(num_blocks){
            hold->chain = rm_block(_bid, hold->chain);
            
            if(count_blocks(hold->chain) != num_blocks){
                exists = true;
            }
        }

        hold = hold->next;
    }

    if(!exists){
        err_handler(ERR_BLOCK_DOESNT_EXIST);
        return 1;
    }

    return 0;
}

bool sync_all(node* _node_head){
    //create master chain on first node, delete all blocks on other chains, create *copies* of master chain for all other nodes
    if(is_synced(_node_head)){
        return false;
    }
    node* hold_node = _node_head->next;
    block* master = _node_head->chain;
    block* hold_chain;
    block* compare_chain;
    block* best_match;
    bool skip = false;

    while(hold_node != NULL){
        hold_chain = hold_node->chain;
        while(hold_chain != NULL){
            compare_chain = master;
            best_match = NULL;
            skip = false;
            while(compare_chain != NULL){
                if(!my_strcmp(hold_chain->bid, compare_chain->bid)){ //the blocks have the same BID
                    if(hold_chain->timestamp == compare_chain->timestamp){ //the blocks have the same timestamp
                        skip = true;
                        break; //skip, they are the same block
                    } else if(hold_chain->timestamp < compare_chain->timestamp) {
                        //swap timestamps (the bid is the same anyways) if hold is older
                        compare_chain->timestamp = hold_chain->timestamp;
                        skip = true;
                        break;
                    } else {
                        skip = true;
                        break; //the hold is newer, ignore it.
                    }
                } else {
                    if(hold_chain->timestamp < compare_chain->timestamp){
                        best_match = compare_chain; //find where the block should be inserted
                    }
                }
                compare_chain = compare_chain->previous;
            }
            if(!skip){
                block* copy = block_copy(hold_chain);
                if(best_match == NULL){ //insert before master
                    ///need to create copy, so the original chain can continue to be indexed
                    copy->previous = master;
                    master = copy;
                } else { //insert after best match
                    copy->previous = best_match->previous;
                    best_match->previous = copy;
                }
            }
            hold_chain = hold_chain->previous;
        }
        hold_node = hold_node->next;
    }

    //delete node chains and make master copies for every node
    hold_node = _node_head->next;
    while(hold_node != NULL){
        rm_chain(hold_node->chain);
        hold_node->chain = chain_copy(master);
        hold_node = hold_node->next;
    }

    //make sure the master tail is returned to our node head
    _node_head->chain = master;

    return true;
}

int list_nodes(bool with_blocks, node* _node_head){
    node* hold = _node_head;
    block* lastblock;
    if(hold->nid == -1){
        err_handler(ERR_NO_NODES);
        return 1;
    }

    while(hold != NULL){
        printf("Node %d", hold->nid);
        if(with_blocks){
            hold->chain = reverse_chain(hold->chain);
            lastblock = hold->chain;
            printf(":");
            
            if(lastblock == NULL){
                printf(" No blocks");
            }

            while(lastblock != NULL){
                printf(" %s,", lastblock->bid);
                lastblock = lastblock->previous;
            }

            hold->chain = reverse_chain(hold->chain);
        }
        printf("\n");
        hold = hold->next;
    }
    return 0;
}

bool nodes_unload(node* _node_head, char* _path){
    FILE * file;
    file = fopen(_path, "w");

    if(file != NULL){
        node* hold = _node_head;
        block* chain;
        while(hold != NULL){
            fprintf(file, "%d", hold->nid);
            fputs("[", file);
            hold->chain = reverse_chain(hold->chain);
            chain = hold->chain;
            while(chain != NULL){
                fprintf(file, "%s", chain->bid);
                fputs(":", file);
                fprintf(file, "%lld", (long long) chain->timestamp);
                fputs(",", file);
                chain = chain->previous;
            }
            fputs("]\n", file);
            hold = hold->next;
        }
        fclose(file);
    } else {
        printf("Save failure\n"); //move to errors
        return false; // continue input loop
    }

    return true; // end loop and end program
}

bool nodes_load(node* _node_head, char* _path){
    FILE* file;
    file = fopen(_path, "r");
    char* buffer = malloc(60);
    char c;
    int i = 0;
    node* hold = _node_head;
    block* bhold;
    bool fail = false;

    if(file != NULL){
        while(!feof(file)){
            c = fgetc(file);
            if(c == '['){ //add node
                buffer[i] = '\0';
                hold = add_node(buffer, _node_head);
                i = 0;
            }else if(c == ':'){ //add block
                buffer[i] = '\0';
                bhold = create_block(buffer, hold->chain);
                i = 0;
                while(c != ','){
                    c = fgetc(file);
                    buffer[i] = c;
                    i++;
                }
                buffer[i] = '\0';
                bhold->timestamp = (time_t) atoll(buffer);
                hold->chain = bhold;
                i = 0;
            }else{
                buffer[i] = c;
                i++;
            }
        }
        fclose(file);
        free(buffer);
    } else {
        err_handler(ERR_BACKUP_CORRUPTED);
        return false;
    }

    if(fail){
        err_handler(ERR_BACKUP_CORRUPTED);
        return false;
    }

    return true;
}
