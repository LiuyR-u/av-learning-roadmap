#pragma once

#include <cstdint>
#include <vector>

class VideoFrame
{
public:
    VideoFrame(
        int width,
        int height,
        std::int64_t pts);

    ~VideoFrame();

    // 禁止拷贝，允许移动
    VideoFrame(const VideoFrame &) = delete;
    VideoFrame &operator=(const VideoFrame &) = delete;
    VideoFrame(VideoFrame &&) noexcept = default;
    VideoFrame &operator=(VideoFrame &&) noexcept = default;

    [[nodiscard]]
    std::int64_t pts() const noexcept;

    [[nodiscard]]
    std::size_t size() const noexcept;

private:
    int width_{};
    int height_{};
    std::int64_t pts_{};
    std::vector<std::uint8_t> pixels_;
};
