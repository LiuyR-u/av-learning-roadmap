// 生产者与消费者
#include "producer.h"

#include <chrono>
#include <iostream>
#include <thread>

void producer(VideoFrameQueue &queue)
{
    constexpr int frame_count = 5;

    for (int index = 0; index < frame_count; ++index)
    {
        const std::int64_t pts = index * 40;
        auto frame = std::make_unique<VideoFrame>(
            640,
            360,
            pts);
        std::cout
            << "Producer created pts = "
            << frame->pts()
            << "\n";

        queue.push(std::move(frame));
        if (!frame)
        {
            std::cout
                << "Producer no longer owns frame\n";
        }
        std::this_thread::sleep_for(
            std::chrono::milliseconds(20));
    }

    queue.close();
}

void consumer(VideoFrameQueue &queue)
{
    while (true)
    {
        FramePtr frame = queue.pop();
        if (!frame)
        {
            break;
        }

        std::cout
            << "Consumer rendering pts = "
            << frame->pts()
            << ", bytes = "
            << frame->size()
            << '\n';

        std::this_thread::sleep_for(
            std::chrono::milliseconds(30));
    }
    std::cout << "Consumer finished\n";
}
