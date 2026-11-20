#include <stdio.h>

// 课题：内存、生命周期与未定义行为
int *get_value()
{
    int valude = 42;
    return &valude;
}

// 正确写法
// 1.返回副本
int get_value()
{
    int value = 42;
    return value; // 返回值本身，不是地址
}

// 2.调用方提供缓冲区
void get_value(int *out)
{
    *out = 42;
}

// 调用
// int v;
// get_value(&v);

// 3. 静态变量/堆内存
int *get_value_static()
{
    static int value = 42; // 静态变量生命周期 = 程序运行期
    return &value;
}

int *get_value_heap()
{
    int *p = malloc(sizeof(int));
    *p = 42;
    return p; // 记得调用方 free(p)
}

// 当前程序执行没有输出
// "程序没有输出"本身也是一种未定义行为的表现
void main()
{
    int *ptr = get_value();
    printf("%d\n", *ptr); // 未定义行为
}
/*
如果size+1发生整数溢出，会产生什么问题？
size_t 是64位无符号整数类型，最大值为 2^64 - 1。如果 size + 1 发生整数溢出，结果将会回绕到 0，这会导致以下问题：
1. 内存分配失败：如果 size + 1 溢出为 0，malloc(0) 可能返回 NULL 或一个有效的指针，但无法分配任何实际内存。这会导致后续对 buffer->data 的访问出现未定义行为。
2. 缓冲区溢出：如果程序继续使用 buffer->data 进行写操作，可能会写入未分配的内存区域，导致缓冲区溢出和潜在的安全漏洞。
3. 逻辑错误：程序可能会认为分配了足够的内存，但实际上没有，这会导致逻辑错误和程序崩溃。
为了避免这些问题，应该在分配内存之前检查 size 是否接近 size_t 的最大值，确保 size + 1 不会溢出。例如，可以在分配前添加一个检查：
if (size >= SIZE_MAX - 1) {
    // Handle error: size is too large
    return 0;
}

这个Buffer能否安全地复制？
    隐患：
        浅拷贝，有可能拥有者双方造成悬空指针，导致内存泄漏或重复释放。
    结构体本身可以拷贝C允许，但是语义上不安全。正确做法三选一：
        1. 禁止拷贝 约定：Buffer只能传指针，绝不赋值。注释写清楚
            具体如何实现：
                ①不透明指针，定义在.c文件中，外部无法访问结构体成员(在外部)
                    优势：编译器强制阻止栈上分配和拷贝，是C语言中模拟封装的标准做法(Linux内核中大量使用 )
                ②添加魔法数+校验 只能提醒 实际的拷贝还是会发生
        2. 显式拷贝函数，深拷贝
        int buffer_clone(Buffer *dest, const Buffer *src)
        {
            if (!buffer_create(dst, src->size)) return 0;
            memcpy(dst->data, src->data.src->size);
            return 1;
        }
        3. C++的RAII:
        用拷贝构造函数+赋值运算符重载+析构函数，保证拷贝时深拷贝，析构时释放内存。C语言没有RAII机制，所以需要手动管理内存。

*/
