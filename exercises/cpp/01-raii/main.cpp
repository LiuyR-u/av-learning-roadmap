#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "VideoFrameQueue.h"
#include "producer.h"

void write_test_file()
{
    const char *filename = "test_640x360.rgb";

    const int width = 640;
    const int height = 360;
    const int channels = 3;

    // 创建 RGB 测试图像（红绿渐变）
    std::vector<uint8_t> frame(width * height * channels);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; ++x)
        {
            size_t idx = (y * width + x) * channels;
            frame[idx + 0] = static_cast<uint8_t>(x % 256); // R
            frame[idx + 1] = static_cast<uint8_t>(y % 256); // G
            frame[idx + 2] = 128;                           // B
        }
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to create test file");
    }

    file.write(
        reinterpret_cast<const char *>(frame.data()),
        frame.size());

    std::cout << "Create test file: " << filename
               << " (" << frame.size() << " bytes)\n";
}

int main()
{
    try
    {
        write_test_file();

        VideoFrameQueue queue;
        std::thread producer_thread(
            producer,
            std::ref(queue));

        std::thread consumer_thread(
            consumer,
            std::ref(queue));

        producer_thread.join();
        consumer_thread.join();
    }
    catch (const std::exception &error)
    {
        std::cerr
            << "Error: "
            << error.what()
            << '\n';

        return 1;
    }

    return 0;
}
