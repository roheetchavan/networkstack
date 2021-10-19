
#ifndef __GLUELIST__
#define __GLUELIST__

typedef struct _gllist{
    struct _gllist* left;
    struct _gllist* right;
}gllist_t;

/* Some useful macros */
#define IS_GLLIST_EMPTY(gllistptr)  \
    ((gllistptr)->right == 0 && (gllistptr)->left == 0)

#define BASE(gllistptr) ((gllistptr)->right)

#define ITERATE_GLLIST_START(glliststartptr, gllistptr) \
{                                                       \
    gllist_t* ptr = NULL;                               \
    gllistptr = BASE(glliststartptr);                   \
    for(; gllistptr != NULL; gllistptr = ptr){          \
        ptr = (gllistptr)->right;                       \

#define ITERATE_GLLIST_END(glliststartptr, gllistptr)   \
    }}

#define GLLIST_GET_DATA_FROM_OFFSET(glliststartptr, offset) \
    (void*)((char*)(glliststartptr) - offset)

/* List of supported functions */
void init_gllist(gllist_t* gllist);
void gllist_add_next(gllist_t* curr, gllist_t* ele);
void gllist_add_before(gllist_t* curr, gllist_t* ele);
void gllist_add_last(gllist_t* base, gllist_t* ele);
void gllist_remove(gllist_t* ele);
void gllist_delete_all(gllist_t* base);
unsigned int gllist_get_count(gllist_t* base);

//void gllist_priority_insert(gllist_t* base, gllist_t* ele, int (*compare_fn)(void*, void*), int offset);

#endif
