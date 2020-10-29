#include "stream.h"

Stream::Stream(size_t bulk_size) :
    _processor(this, bulk_size),
    _blockProcessor(this)
{}

void Stream::commonInput(std::string line)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _processor.parseCommand(line);
    _blockProcessor.parseCommand(line);
}

void Stream::flush()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _processor.flush();
}
