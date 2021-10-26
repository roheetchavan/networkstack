#ifndef __GRAPH__
#define __GRAPH__

#include <assert.h>

#include "gluelist/gllist.h"

#define IF_NAME_SZ 16
#define NODE_NAME_SZ 16
#define TOPOLOGY_NAME_SZ 32

#define MAX_INTF_PER_NODE 10

typedef struct node node_t;
typedef struct link link_t;

typedef struct interface{
    char if_name[IF_NAME_SZ];
    node_t *att_node;
    link_t *link;
}interface_t;

struct link{
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
};

struct node{
    char node_name[NODE_NAME_SZ];
    interface_t *intf[MAX_INTF_PER_NODE];
    gllist_t graph_glue;
};

typedef struct graph {
    char topology_name[TOPOLOGY_NAME_SZ];
    gllist_t node_list;
}graph_t;

GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, graph_glue);

/* Helper functions */
static inline node_t* get_nbr_node(interface_t* intf)
{
    assert(intf->att_node);
    assert(intf->link);

    link_t* lnk = intf->link;
    if(&lnk->intf1 == intf)
        return lnk->intf2.att_node;
    else
        return lnk->intf1.att_node;
}

static inline int get_node_intf_available_slot(node_t* node)
{
    int i;
    for(i = 0; i < MAX_INTF_PER_NODE; i++){
        if(node->intf[i])
            continue;
        return i;
    }
    return -1;
}

graph_t* create_graph(char* topology_name);
node_t* create_graph_node(graph_t* graph, char* node_name);
void insert_link_between_two_nodes( node_t* node1,
                                    node_t *node2,
                                    char* from_intf,
                                    char* to_intf,
                                    unsigned int cost);

void dump_graph(graph_t* graph);
void dump_node(node_t* node);
void dump_interface(interface_t* intf);

#endif /* GRAPH */
