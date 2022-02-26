#ifndef BLOCKCHAIN_BLOCKS_H
#define BLOCKCHAIN_BLOCKS_H

typedef struct block_s {
    char* bid;
    struct block_s* previous;
    time_t timestamp;
} block;

int count_blocks(block* _block_tail);
block* create_block(char * _bid, block* _last_block);
bool block_check_name(char* _bid, block* _last_block);
void free_block(block* _block);
block* rm_block(char* _bid, block* _block_tail);
block* rm_chain(block* _block_tail);
block* block_copy(block* _block);
block* chain_copy(block* _block_tail);
block* reverse_chain(block* _block_tail);

#endif