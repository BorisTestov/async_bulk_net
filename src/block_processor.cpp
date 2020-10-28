#include "block_processor.h"

BlockProcessor::BlockProcessor(void* handle) :
    Observer(handle),
    _blockCounter(0),
    _timeStart(std::time(nullptr)),
    _store()
{
}

BlockProcessor::~BlockProcessor()
{
    //dtor
}

void BlockProcessor::startBlock()
{
    ++_blockCounter;
}

void BlockProcessor::finishBlock()
{
    if (_blockCounter > 0)
        --_blockCounter;

    if (_blockCounter == 0)
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void BlockProcessor::handleCommand(const std::string& command)
{
    if (0 < _blockCounter)
        _store.addCommand(command);
}

void BlockProcessor::logBlock()
{
    std::stringstream sstream;
    sstream << "bulk" << _timeStart << "_" << handle_ << "_" << rand() << ".log";
    std::ofstream fileLog(sstream.str());
    _store.printCommands(fileLog);
}

std::time_t BlockProcessor::getTime() const
{
    return _timeStart;
}
