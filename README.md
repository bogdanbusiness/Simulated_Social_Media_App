# Social Media App

## Introduction

This command line Social Media Application allows users to befriend
one another, to create posts on the platform and get a personalised
feed, among other things.

## Table of contents

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [Settings](#settings)
  - [User Interactions](#user-interactions)
  - [Post Interactions](#post-interactions)
  - [Platform Interactions](#platform-interactions)
- [Documentation](#documentation)
  - [Bigger Picture](#bigger-picture)
  - [Data Structures](#data-structures)
    - [Doubly Linked Lists](#doubly-linked-list)
    - [Queue](#queue)
    - [Graph](#graph)
    - [Tree](#tree)
  - [Files](#files)

## Settings

### User Interactions

add <name-1> <name-2>      Adds a connection between 2 friends.
remove <name-1> <name-2>   Removes the connection between 2 (ex-)friends.
distance <name-1> <name-2> Gets the distance between 2 people.
suggestions <name>         Gives friend request suggestions to a user.
common <name-1> <name-2>   Finds the common friends between 2 users.
friends <name>             Returns the number of friends a user has.
popular <name>             Finds who is the most popular friend of a user.

### Post Interactions

create <name> <title>                            Creates a new post.
repost <name> <post-id> {repost-id}              Reposts a post.
common-repost <post> <repost-id-1> <repost-id-2> Finds the common reposts
                                                 between 2 reposts.
like <name> <post-id> {repost-id}                Likes a (re)post.
ratio <post-id>                                  Finds if a post got ratio'd.
delete <post-id> {repost-id}                     Delets a (re)post.
get-likes <post-id> {repost-id}                  Returns the likes of (re)post.

### Platform Interactions

feed <name> <feed-size>         Creates a personilized feed for the user.
view-profile <name>             Views the profile of a user.
friends-repost <name> <post-id> Finds all the reposts of friends of a user.
common-group <name>             Finds the biggest clique a user is part of.

## Documentation

### Bigger picture

The program relies rather heavily on generic functions and functional
programming to achive its goals, since a lot of the tasks can be broken
down into similar enough functions.

The connections between users are modeled using a list graph.
The list graph is composed of a vector of DLL lists. Each element in the vector
is a user and each element in the DLL list is a friend of that user.

The posts are stored in a "database" which is a cronological vector.
Each (re)post is a structure that contains among others a structure of likes
and a tree of reposts.

The likes structure contains the number of likes a (re)post has and a vector
of user_ids of the people that have liked that post.

The tree of reposts is the representation for which reposts are reposts of
other (re)posts. The root of this tree is the original post and contains no
data (important for how functions are implemented inside the program, where
functions usually treat the root differently from other nodes).
Every other node contains the structure to the repost.
Reposts don't have a tree of reposts.

### Data Structures

#### Doubly Linked List

Defined by 3 structs:
1. Header struct
2. Node struct
3. Info struct

1. Header struct is responsible for holding the pointer to the first node,
the size of the list and the size of the nodes.

2. Node struct is the node of the DLL and is generic, holding only the
pointers to the next and previous node along with a void pointer to data.

3. Info struct is the one responsible for holding the actual data.
In its current implementation it stores only an integer.

#### Queue

The queue is implemented generically and is comprised of the following
elements:
1. A buffer which stores the elements in the queue.
2. Size of the elements in the queue.
3. Maximum size of the queue.
4. Size of the queue.
5. Read index.
6. Write index.
7. Data duplicator.
8. Data destructor.

Each of this elements shouldn't be accessed (unless absolutely necessary),
since the functions already implemented should allow full control of the queue.

#### Graph

The graph we use is a generic list graph.
It is implemented using a vector for every node that stores a DLL which
represents all the connections that node has.

#### Tree

The tree we use is a generic k-nary tree.
Defined by 3 structs:
1. Header struct
2. Node struct

1. Header struct is responsible for holding the pointer to root,
the size of the nodes and a destructor for the data in the nodes.

2. Node struct is the node of the tree and is generic, holding the pointer
to data, a vector which stores pointers to the children of the node and 
the occupied and allocated size of the children vector.

### Files

1. <helpers.c/h> stores implementations to random helper functions, along
with some functional programming functions.

2. <data_structure.c/h> stores implementations to the data structures.

3. <algorithms.c/h> stores the implementations of all the algorithms used.
They are dependent on the implementation of the data structures.

4. <friends.c/h> stores the user interactions.

5. <posts.c/h> stores the post interactions.

6. <feed.c/h> stores the platform interactions.

#### Copyright: 2024 - Gheorghe Andrei-Bogdan
