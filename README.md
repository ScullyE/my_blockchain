# my_blockchain

***

Project for Students @ [Qwasar Silicon Valley](https://qwasar.io/)

![Qwasar Silicon Valley Logo](https://qwasar.io/wp-content/uploads/2019/07/Qwasar-Logo-09.png "Qwasar Silicon Valley Logo")

Created by:
Ethan Scully

***

### Task

Create a program that simulates a blockchain manager, including the ability to create, remove, and synchronize nodes and blocks. Program must also create and load backups.

***
### Description

**my_blockchain** (also affectionately named BLOCH) is a program that imitates a blockchain system. A number of commands can be given to the program, including:

- `add node [NID]` - adds a node to the blockchain, the node ID (NID) must be a positive number.

- `rm node [NID]` - removes a node from the blockchain.

- `add block [BID] [NID]` - adds a block with the provided block ID (BID) to a node. You can use * instead of a specific NID to add the block to all nodes. The BID can be any alphanumerical (no spaces or symbols please) string under 100 characters.

- `rm block [BID]` - removes a block from all nodes.

- `ls` - lists all nodes. You can use the command `ls -l` to list all nodes with their respective blocks

- `sync` - Synchronizes the nodes, with older blocks given priority.

- `quit` - Quits the progam and saves a backup.

The program's prompt provides useful information. The first character is either `S` if the nodes are synchronized or `-` if they are not. The second will be the number of nodes in the system.

my_blockchain automatically saves backups when using the `quit` command, and automatically loads a backup if it exists. The backup is stored in `/backups`.

***
### Usage

To start using my_blockchain, simply run the following commands in the program's root folder.

```
$ make
$ ./my_blockchain
```


***
# Cheers!