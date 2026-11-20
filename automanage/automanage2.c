#include "automanage2.h"
#include<stdlib.h>

void memory_cleanup_default(void* ptr)
{
    void** p=(void**)ptr;
    if(p&&*p)
    {
        free(*p);
        *p=nullptr;
    }
}