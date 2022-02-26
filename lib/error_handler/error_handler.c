#include <stdio.h>
#include <stdlib.h>

#include "error_handler.h"

// #define ERR_BACKUP_CORRUPTED 101
// #define ERR_NODE_EXISTS 102
// #define ERR_NODE_DOESNT_EXIST 103
// #define ERR_BLOCK_EXISTS 104
// #define ERR_BLOCK_DOESNT_EXIST 105
// #define ERR_COMMAND_NOT_FOUND 106
// #define ERR_NO_NODES 107
// #define ERR_NODE_NAME 108
// #define ERR_BLOCK_NAME 109

void err_handler(int _input){
    switch(_input){
        case ERR_COMMAND_NOT_FOUND:
            printf("Error: Command not found\n");
        break;
        case ERR_NODE_EXISTS:
            printf("Error: Node with this NID already exists\n");
        break;
        case ERR_NODE_NAME:
            printf("Error: NID must be number greater than zero\n");
        break;
        case ERR_NODE_DOESNT_EXIST:
            printf("Error: Node with this NID does not exist\n");
        break;
        case ERR_BLOCK_EXISTS:
            printf("Error: Block with this BID already exists\n");
        break;
        case ERR_BLOCK_NAME:
            printf("Error: BID must contain alphanumeric characters only\n");
        break;
        case ERR_BLOCK_DOESNT_EXIST:
            printf("Error: Block with this BID does not exist\n");
        break;
        case ERR_NO_NODES:
            printf("No nodes exist yet\n");
        break; 

        default:
            printf("Error: Undefined\n");
        break;
    }
}