#include "VideoFrame.h"

#include <iostream>

VideoFrame::VideoFrame(
    int width,
    int height,
    std::int64_t pts)
    : width_(width),
      height_(height),
      pts_(pts),
      pixels_(
          static_cast<std::size_t>(width) *
          static_cast<std::size_t>(height) *
          3) // RGB 三通道
{
    std::cout
        << "Create frame, pts = "
        << pts_
        << "\n";
}

VideoFrame::~VideoFrame()
{
    std::cout
        << "Destroy frame, pts = "
        << pts_
        << '\n';
}

std::int64_t VideoFrame::pts() const noexcept
{
    return pts_;
}

std::size_t VideoFrame::size() const noexcept
{
    return pixels_.size();
}
