#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "error_handler/error_handler.h"
#include "strings/strings.h"
#include "nodes/my_nodes.h"
#include "blocks/my_blocks.h"

#define MAX_INPUT_SIZE 30
#define MAX_INPUT_ARGS 4

node* load_backup(char* _path);
node* cmd_loop(node* _node_head);
bool save_backup(node* _node_head, char* _fpath, char* _dpath);
void print_welcome_msg();

int my_blockchain(){

    char* backup_folder = "./backups";
    char* backup_path = "./backups/bloch_backup";

    print_welcome_msg();

    node* node_head = load_backup(backup_path);
    if(node_head != NULL){
        cmd_loop(node_head); 
    }

    save_backup(node_head, backup_path, backup_folder);

    return 0;
}

node* load_backup(char* _path){
    struct stat st;
    node* node_head = malloc(sizeof(node));

    node_head->nid = -1;
    node_head->next = NULL;
    node_head->chain = NULL;

    if (stat(_path, &st) == -1) {
        //no backup
        printf("No backup found, starting new blockchain\n");
        
    } else {
        if(nodes_load(node_head, _path)){
            printf("Backup loaded\n");
        } else {
            return NULL;
        }
    }

    return node_head;
}

void print_prompt(node* _node_head){
    int n = count_nodes(_node_head);
    char ns[11];
    printf_nr("[");
    if(is_synced(_node_head)){
        printf_nr("S");
    } else {
        printf_nr("-");
    }
    sprintf(ns, "%d", n);
    printf_nr(ns);
    printf_nr("]> ");
    fflush(stdout);
}

bool input_handler(char* _input, node* _node_head){
    char* cmds[MAX_INPUT_ARGS];
    bool quit = false;
    bool cmd_err = true;

    for(int i = 0; i < MAX_INPUT_ARGS; i++){
        cmds[i] = malloc(sizeof(char) * MAX_INPUT_SIZE);
        if(!get_word(_input, cmds[i], i)){ 
            cmds[i][0] = '\0';
        }
    }

    if(!my_strcmp(cmds[0], "add")){                 /////add commands

        if(!my_strcmp(cmds[1], "node")){            //add node
            add_node(cmds[2], _node_head);
            cmd_err = false;

        } else if(!my_strcmp(cmds[1], "block")){    //add block
            if(*cmds[3] == '*'){
                if(count_nodes(_node_head)){ //check if any nodes exist
                    add_block_to_all_nodes(cmds[2], _node_head);
                } else {
                    err_handler(ERR_NO_NODES);
                }
            } else {
                add_block_to_node(cmds[2], cmds[3], _node_head);
            }
            cmd_err = false;
        }

    } else if(!my_strcmp(cmds[0], "rm")){           /////remove commands

        if(!my_strcmp(cmds[1], "node")){            //remove node
            rm_node(cmds[2], _node_head);
            cmd_err = false;

        } else if(!my_strcmp(cmds[1], "block")){    //remove block
            rm_block_all(cmds[2], _node_head);
            cmd_err = false;
        }

    } else if(!my_strcmp(cmds[0], "ls")){           /////ls commands

        if(!my_strcmp(cmds[1], "-l")){              //list nodes with bids
            list_nodes(true, _node_head);
            cmd_err = false;

        } else{                                     //list nodes
            list_nodes(false, _node_head);
            cmd_err = false;
        }

    } else if(!my_strcmp(cmds[0], "sync")){ /////sync commands
        sync_all(_node_head);
        cmd_err = false;

    } else if(!my_strcmp(cmds[0], "quit")){ /////quit commands
        printf("Goodbye!\n");
        cmd_err = false;
        quit = true;
    }
    
    if(cmd_err){
        err_handler(ERR_COMMAND_NOT_FOUND);
    }

    for(int i = 0; i < MAX_INPUT_ARGS; i++){
        free(cmds[i]);
    }

    return quit;
}

node* cmd_loop(node* _node_head){
    bool exit = false;

    //count nodes
    //check sync

    while(!exit){
        char input[MAX_INPUT_SIZE];

        print_prompt(_node_head);

        fgets(input, MAX_INPUT_SIZE, stdin);
        
        input[MAX_INPUT_SIZE-1] = '\n';
        
        exit = input_handler(input, _node_head);
    }

    return _node_head;
}

bool save_backup(node* _node_head, char* _fpath, char* _dpath){
    //make directory if it doesnt exist;
    struct stat sb;
    if (stat(_dpath, &sb) == -1) {
        mkdir(_dpath, 0700);
    }

    nodes_unload(_node_head, _fpath);
    
    free_node_all(_node_head);
    return true;
}

void print_welcome_msg(){
    printf(" .----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n");
    printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
    printf("| |   ______     | || |   _____      | || |     ____     | || |     ______   | || |  ____  ____  | |\n");
    printf("| |  |_   _ \\    | || |  |_   _|     | || |   .'    `.   | || |   .' ___  |  | || | |_   ||   _| | |\n");
    printf("| |    | |_) |   | || |    | |       | || |  /  .--.  \\  | || |  / .'   \\_|  | || |   | |__| |   | |\n");
    printf("| |    |  __'.   | || |    | |   _   | || |  | |    | |  | || |  | |         | || |   |  __  |   | |\n");
    printf("| |   _| |__) |  | || |   _| |__/ |  | || |  \\  `--'  /  | || |  \\ `.___.'\\  | || |  _| |  | |_  | |\n");
    printf("| |  |_______/   | || |  |________|  | || |   `.____.'   | || |   `._____.'  | || | |____||____| | |\n");
    printf("| |              | || |              | || |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n");
    printf("\n");
    printf("                                        My BLOckCHain Manager\n");
    printf("\n");
}