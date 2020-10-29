#pragma once

#include "block_processor.h"
#include "command_processor.h"
#include "observer.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <mutex>
#include <vector>

class Stream
{
public:
    Stream(size_t bulk_size);
    virtual ~Stream() = default;

    void commonInput(std::string);
    void flush();

private:
    CommandProcessor _processor;
    BlockProcessor _blockProcessor;
    std::mutex _mutex;
};
