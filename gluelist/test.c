

#include "gllist.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct student{
    int roll_no;
    int marks;
    gllist_t list;
}student_t;

#define offset(strcut_name, field)  \
    (unsigned int)&((struct_name*)0)->field)

int main(int argc, char**argv)
{

    student_t studs[3];
    memset(studs, 0, sizeof(student_t)*3);
    studs[0].roll_no = 1;
    studs[0].marks = 70;

    studs[1].roll_no = 2;
    studs[1].marks = 60;

    studs[2].roll_no = 3;
    studs[3].marks = 62;


    gllist_t base;
    init_gllist(&base);

    gllist_add_next(&base, &studs[0].list);
    gllist_add_next(&base, &studs[1].list);
    gllist_add_next(&base, &studs[2].list);

    /* check data */
    printf("Number of records:%u\n", gllist_get_count(&base));
    gllist_remove(&studs[2].list);
    assert(gllist_get_count(&base) == 2);
    printf("Number of records:%u\n", gllist_get_count(&base));
    gllist_delete_all(&base);
    printf("Number of records:%u\n", gllist_get_count(&base));
    assert(gllist_get_count(&base) == 0);

    return 0;
}
