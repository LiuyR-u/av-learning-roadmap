// 实现线程安全队列
#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

#include "VideoFrame.h"

using FramePtr = std::unique_ptr<VideoFrame>;

class VideoFrameQueue
{
public:
    void push(FramePtr frame);

    FramePtr pop();

    void close();

private:
    std::queue<FramePtr> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool closed_{false};
};
