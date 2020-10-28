#include "stream.h"

Stream::Stream(size_t bulk_size) :
    _processor(this, bulk_size)
{}

void Stream::commonInput(std::string line)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _processor.newCommand(line);
}

void Stream::flush()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _processor.flush();
}
