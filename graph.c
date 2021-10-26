

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

graph_t* create_graph(char* topology_name)
{
    graph_t* graph = calloc(1, sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, TOPOLOGY_NAME_SZ);
    graph->topology_name[TOPOLOGY_NAME_SZ] = '\0';

    init_gllist(&graph->node_list);
    return graph;
}

node_t* create_graph_node(graph_t* graph, char* node_name)
{
    node_t* node = calloc(1, sizeof(node_t));
    strncpy(node->node_name, node_name, NODE_NAME_SZ);
    node->node_name[NODE_NAME_SZ] = '\0';

    init_gllist(&node->graph_glue);
    gllist_add_next(&graph->node_list, &node->graph_glue);

    return node;
}

void insert_link_between_two_nodes( node_t* node1,
                                    node_t *node2,
                                    char* from_intf,
                                    char* to_intf,
                                    unsigned int cost)
{
     link_t* link = calloc(1, sizeof(link_t));

     /*Set interface properties*/
     strncpy(link->intf1.if_name, from_intf, IF_NAME_SZ);
     link->intf1.if_name[IF_NAME_SZ] = '\0';
     strncpy(link->intf2.if_name, to_intf, IF_NAME_SZ);
     link->intf2.if_name[IF_NAME_SZ] = '\0';

     link->intf1.link= link; /*set back pointer to link*/
     link->intf2.link= link; /*set back pointer to link*/

     link->intf1.att_node = node1;
     link->intf2.att_node = node2;
     link->cost = cost;

     int empty_intf_slot;

     /*Plugin interface ends into Node*/
     empty_intf_slot = get_node_intf_available_slot(node1);
     node1->intf[empty_intf_slot] = &link->intf1;

     empty_intf_slot = get_node_intf_available_slot(node2);
     node2->intf[empty_intf_slot] = &link->intf2;
}

void dump_node(node_t* node)
{
    unsigned int i;
    interface_t* intf;
 
    printf("Node Name : %s \n", node->node_name);
    for(i = 0; i < MAX_INTF_PER_NODE; i++){
        intf = node->intf[i];
        if(!intf)   break;
        dump_interface(intf);
    }
}

void dump_interface(interface_t* intf)
{
    link_t* lnk = intf->link;
    node_t* nbr_node = get_nbr_node(intf);

    printf(" Local Node : %s Interface name : %s Nbr node : %s cost:%u\n",
            intf->att_node->node_name, intf->if_name, nbr_node->node_name, lnk->cost);
}

void dump_graph(graph_t* graph)
{
    gllist_t* curr;
    node_t* node;

    printf("Topology Name = %s\n", graph->topology_name);
    ITERATE_GLLIST_START(&graph->node_list, curr){

         node = graph_glue_to_node(curr);
         dump_node(node);
     } ITERATE_GLLIST_END(&graph->node_list, curr);    
}
