# C/C++ 音视频开发学习路线

这是我的 C/C++ 与音视频开发学习仓库，用于保存学习计划、笔记、练习、项目和阶段总结。

## 学习目标

- 掌握 C 语言基础、指针、内存管理和常用数据结构。
- 掌握现代 C++、面向对象、STL、RAII 和多线程基础。
- 理解 PCM、YUV、采样、封装、编码和解码等音视频概念。
- 学习 FFmpeg，并独立完成播放器和音视频处理项目。

## 仓库结构

```text
av-learning-roadmap/
├── README.md              # 总目标和仓库导航
├── progress.md            # 每日、每周学习记录
├── notes/                 # 分类知识笔记
│   ├── c/
│   ├── cpp/
│   ├── computer-basics/
│   ├── audio/
│   └── video/
├── exercises/             # C/C++ 小练习
├── projects/              # 阶段项目
├── resources/             # 资料索引
└── assets/                # 笔记图片（不放大型音视频文件）
```

## 当前阶段

阶段 1：C 语言基础与 Git 基本操作。

详细进度见 [progress.md](progress.md)。

## 学习与提交约定

每次学习完成后：

```powershell
git status
git add .
git commit -m "learn: complete today's study"
git push
```

提交信息示例：

- `learn: practice C pointers`
- `docs: add memory management notes`
- `feat: implement WAV header parser`
- `fix: correct buffer boundary check`

## 仓库原则

- 笔记尽量使用自己的语言总结。
- 每个练习都应能够独立编译运行。
- 项目需要包含说明、构建方法和运行示例。
- 不提交密码、令牌、个人隐私及大型媒体素材。
