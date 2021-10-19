
#include "gllist.h"
#include <stdlib.h>

void init_gllist(gllist_t* base)
{
    base->left = NULL;
    base->right = NULL;
}

void gllist_add_next(gllist_t* curr, gllist_t* ele)
{
    // curr is at end
    if(!curr->right){
        curr->right = ele;
        ele->left = curr;
        return;
    }

    gllist_t* tmp = curr->right;
    curr->right = ele;
    ele->left = curr;
    ele->right = tmp;
    tmp->left = ele;
    return;
}

void gllist_add_before(gllist_t* curr, gllist_t* ele)
{
    // add at first position
    if(!curr->left){
        ele->left = NULL;
        ele->right = curr;
        curr->left = ele;
        return;
    }

    gllist_t* tmp = curr->left;
    tmp->right = ele;
    ele->left = tmp;
    ele->right = curr;
    curr->left = ele;
    return;
}

void gllist_add_last(gllist_t* base, gllist_t* ele)
{
    gllist_t* ptr = NULL;
    gllist_t* prev_ptr = NULL;

    ITERATE_GLLIST_START(base, ptr){
        prev_ptr = ptr;
    } ITERATE_GLLIST_END(base, ptr);

    if(prev_ptr)
        gllist_add_next(prev_ptr, ele);
    else
        gllist_add_next(base, ele);
    return;
}

void gllist_remove(gllist_t* curr)
{
    if(!curr->left){
        if(curr->right){
            curr->right->left = NULL;
            curr->right = 0;
            return;
        }
        return;
    }

    if(!curr->right){
        curr->left->right = NULL;
        curr->left = NULL;
        return;
    }

    curr->left->right = curr->right;
    curr->right->left = curr->left;
    curr->left = 0;
    curr->right = 0;
    return;
}

void gllist_delete_all(gllist_t* base)
{
    gllist_t* listptr = NULL;

    ITERATE_GLLIST_START(base, listptr){
        gllist_remove(listptr);
    } ITERATE_GLLIST_END(base, listptr);
    return;
}

unsigned int gllist_get_count(gllist_t* base)
{
    unsigned int count = 0;
    gllist_t* ptr = NULL;

    ITERATE_GLLIST_START(base, ptr){
        ++count;
    } ITERATE_GLLIST_END(base, ptr);
    return count;
}
