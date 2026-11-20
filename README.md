# CLibrary

**CLibrary是个人自定义C语言库，目前包含有automanage2库。**

## automanage2

C语言智能指针库。为了较少繁琐的内存释放操作而制作此库。

automanage2库目前仅包含auto_ptr_unique一种智能指针。

**使用要求**

- **编译器：**gcc, clang, MinGw
- **C语言版本：**C23及以上

**文件说明**

|           文件            |         作用          |
| :-----------------------: | :-------------------: |
| automanage2/automanage2.h |   automanage2头文件   |
| automanage2/automanage2.c | automanage2库代码文件 |

**使用方法**

对于基本数据类型的一级指针，使用`auto_ptr_unique(type, name)`定义`type*`类型指针`name`。下面以`int`类型为例。

```C
#include<stdlib.h>
#include "automanage2.h"

int main(void)
{
    int n=5;
    {
        auto_ptr_unique(int, a)=(int*)malloc(sizeof(int)*n);
        for(int i=0;i<5;i++)a[i]=i;
    }
    return 0;
}
```

以上代码中，`auto_ptr_unique(int, a)=(int*)malloc(sizeof(int)*5);`定义了一个`int*`类型的指针变量`a`，并从堆内存划分了5个整型类型的空间赋值给`a`。指针`a`在其生命周期（以上代码变量`a`生命周期为函数内部大括号，即`return 0;`之前的`}`处结束）结束时会自动释放内存空间，并将`a`置为`nullptr`。

对于二级指针和自定义类型，如结构体，在声明结构体结构的同时需要为该结构体类型定义清理函数。之后使用`auto_ptr_unique(type, name, cleanfunc)`定义`type*`类型指针`name`。下面以自定义结构体为例。

```C
#include<stdio.h>
#include<stdlib.h>
#include "automanage2.h"

// 定义结构体
typedef struct
{
    int age;
    const char* name;
    char** hobbies;
}Person;
// 定义清理函数
void _Person(Person** p)
{
    if(p&&*p)
    {
        if((*p)->hobbies)
        {
            free((*p)->hobbies);
            (*p)->hobbies=nullptr;
        }
        free(*p);
        *p=nullptr;
    }
}

int main(void)
{
    {
        auto_ptr_unique(Person, xiaoming, _Person)=(Person*)malloc(sizeof(Person));
        xiaoming->age=16;
        xiaoming->name="Xiao Ming";
        xiaoming->hobbies=(char**)malloc(sizeof(char*)*3);
        xiaoming->hobbies[0]="soccer";
        xiaoming->hobbies[1]="reading";
        xiaoming->hobbies[2]="computer games";
    }
    return 0;
}
```

**使用限制**

不可将两个使用该库定义的智能指针相互赋值，例如以下操作。

```C
auto_ptr_unique(int, a)=(int*)malloc(sizeof(int));
auto_ptr_unique(int, b)=(int*)malloc(sizeof(int));
b=a;
```

其中`b=a;`是不被允许的操作，但一下操作是可行的。

```C
auto_ptr_unique(int, a)=(int*)malloc(sizeof(int));
auto_ptr_unique(int, b)=(int*)malloc(sizeof(int));
int* t=a;
a=b;
b=t;
t=nullptr;
```

本质是，使用该库定义的多个智能指针不可在生命周期结束时指向同一块内存。