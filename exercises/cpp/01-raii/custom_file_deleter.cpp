// 为什么需要自定义删除器
// 普通的unique_ptr 默认执行delete pointer
// FILE* 类型的指针必须手动释放delete

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

// 自定义删除器
struct FileDeletr
{
    // 重载函数调用运算符(),使得类的对象可以像函数一样被调用
    void operator()(File *file) const noexcept
    {
        if (file != nullptr)
        {
            std::close(file);
        }
    }
};

using FilePtr = std::unique_ptr<File, FileDeletr>;
// 析构时自动调用FileDeletr()(ptr)释放资源