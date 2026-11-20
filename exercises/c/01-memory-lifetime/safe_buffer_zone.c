/*
#include <stdio.h>   // printf, fprintf, stderr
#include <stdlib.h>  // malloc, free, EXIT_SUCCESS, EXIT_FAILURE
#include <stdint.h>  // uint8_t, size_t

// ✅ 用 uint8_t 表示原始字节（可移植）
// ✅ 用 size_t 表示大小（无符号，与 malloc 匹配）
// ✅ 错误信息用 fprintf(stderr, ...)
// ✅ 用 EXIT_SUCCESS / EXIT_FAILURE 表示退出状态
// ✅ 失败时返回 0，成功时返回 1（buffer_create 的约定）
// ✅ 释放后置 NULL，防止悬空指针（buffer_destory）

// 栈空间申请的值未初始化，内容是随机的，初始化后更干净
// 传指针 值拷贝
// free(NULL) 是安全的，什么都不做
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint8_t *data;
    size_t size;
} Buffer;

int buffer_create(Buffer *buffer, size_t size)
{
    if (buffer == NULL || size == 0)
    {
        return 0; // Invalid parameters
    }

    buffer->data = (uint8_t *)malloc(size);
    if (buffer->data == NULL)
    {
        buffer->size = 0; // 防止内存分配失败后, size是上次残留数据 造成歧义
        return 0;
    }

    buffer->size = size;
    return 1;
}

void buffer_destory(Buffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }
    free(buffer->data);
    buffer->data = NULL;    // free 后置 NULL，防止悬空指针
    buffer->size = 0;
}

int main()
{
    Buffer buffer;
    if (!buffer_create(&buffer, 1024))
    {
        fprintf(stderr, "Failed to create buffer\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer.size; i++)
    {
        buffer.data[i] = (uint8_t)(i % 256);
    }

    printf("size: %zu\n", buffer.size);
    printf("first byte: %u\n", (unsigned)buffer.data[0]);
    printf("last byte:%u\n", (unsigned)buffer.data[buffer.size - 1]);

    buffer_destory(&buffer);
    return EXIT_SUCCESS;
}