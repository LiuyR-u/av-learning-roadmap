#include "VideoFrameQueue.h"

#include <stdexcept>

void VideoFrameQueue::push(FramePtr frame)
{
    if (!frame)
    {
        throw std::invalid_argument(
            "Cannot push a null frame");
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (closed_)
        {
            throw std::runtime_error(
                "Cannot push to a closed queue");
        }

        queue_.push(std::move(frame));
    }
    condition_.notify_one();
}

FramePtr VideoFrameQueue::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]
                    { return closed_ || !queue_.empty(); });

    if (queue_.empty())
    {
        return nullptr;
    }

    FramePtr frame = std::move(queue_.front());
    queue_.pop();

    return frame;
}

void VideoFrameQueue::close()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        closed_ = true;
    }
    condition_.notify_all();
}
