#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../error_handler/error_handler.h"
#include "../strings/strings.h"
#include "my_blocks.h"

int count_blocks(block* _block_tail){
    block* hold = _block_tail;
    int count = 1;
    if(_block_tail == NULL){
        return 0;
    } else {
        while(hold != NULL){
            count++;
            hold = hold->previous;
        }
    }
    return count;
}

bool block_check_name(char* _bid, block* _last_block){
    block* hold = _last_block;

    while(hold != NULL){
        if(!my_strcmp(hold->bid, _bid)){
            return false;
        }
        hold = hold->previous;
    }
    
    return true;
}

block* create_block(char * _bid, block* _last_block){
    if(*_bid == '\0'){
        err_handler(ERR_BLOCK_NAME);
        return NULL;
    }else if(!block_check_name(_bid, _last_block)){
        err_handler(ERR_BLOCK_EXISTS);
        return NULL;
    }

    block* newblock = malloc(sizeof(block));
    char* bid = malloc(my_strlen(_bid)+1);
    my_strcpy(bid, _bid);
    newblock->bid = bid;
    newblock->timestamp = time(NULL);
    newblock->previous = _last_block;

    return newblock;
}

void free_block(block* _block){
    free(_block->bid);
    free(_block);
}

//removes block from blockchain, see nodes for remove blocks from all nodes. Returns last block on success, NULL if nothing found
block* rm_block(char* _bid, block* _block_tail){ 
    block* hold = _block_tail;
    block* last = NULL;

    while(hold != NULL){
        if(!my_strcmp(hold->bid, _bid)){
            break;
        }
        last = hold;
        hold = hold->previous;
    }

    if(hold == NULL){
        return _block_tail;
    }

    if(last == NULL){
        last = hold->previous;
        free_block(hold);
        return last;
    } else {
        last->previous = hold->previous;
        free_block(hold);
    }

    return _block_tail;
}

block* rm_chain(block* _block_tail){
    block* rm_block;
    while(_block_tail != NULL){
        rm_block = _block_tail;
        _block_tail = _block_tail->previous;
        free_block(rm_block);
    }

    return NULL;
}

block* block_copy(block* _block){
    block* newblock = malloc(sizeof(block));
    char* bid = malloc(my_strlen(_block->bid)+1);
    my_strcpy(bid, _block->bid);
    newblock->bid = bid;
    newblock->timestamp = _block->timestamp;
    newblock->previous = _block->previous;

    return newblock;
}

block* chain_copy(block* _block_tail){
    block* newchain = block_copy(_block_tail);
    block* new_tail = newchain;
    block* hold = _block_tail->previous;
    block* copy;
    while(hold != NULL){
        copy = block_copy(hold);
        newchain->previous = copy;
        newchain = newchain->previous;
        hold = hold->previous;
    }

    return new_tail;
}

block* reverse_chain(block* _block_tail){
    block* prev = NULL;
    block* current = _block_tail;
    block* next = NULL;
    while (current != NULL) {
        next = current->previous;
        current->previous = prev;
        prev = current;
        current = next;
    }
    return prev;
}

