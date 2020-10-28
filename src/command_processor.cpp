#include "command_processor.h"

CommandProcessor::CommandProcessor(void* handle, size_t bulkSize) :
    Observer(handle),
    _bulkSize(bulkSize),
    _blockCounter(0),
    _store(bulkSize)
{
}

CommandProcessor::~CommandProcessor()
{
    if (!_store.isEmpty())
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void CommandProcessor::newCommand(const std::string& newCommand)
{
    if (_store.isEmpty())
        _timeStart = std::time(nullptr);
    _store.addCommand(newCommand);
}

void CommandProcessor::startBlock()
{
    if (0 == _blockCounter && 0 < _store.size())
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
    ++_blockCounter;
}

void CommandProcessor::finishBlock()
{
    if (_blockCounter > 0)
        --_blockCounter;
}

void CommandProcessor::handleCommand(const std::string& command)
{
    if (_blockCounter == 0)
    {
        newCommand(command);
        if (_bulkSize == _store.size())
        {
            _store.printCommands();
            logBlock();
            _store.clear();
        }
    }
}

void CommandProcessor::logBlock()
{
    std::stringstream sstream;
    sstream << "bulk" << _timeStart << "_" << handle_ << "_" << rand() << ".log";
    std::ofstream fileLog(sstream.str());
    _store.printCommands(fileLog);
}

void CommandProcessor::flush()
{
    if (not _store.isEmpty())
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}
