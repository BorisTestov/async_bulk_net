#include "observer.h"

Observer::Observer(void* handle) :
    handle_(handle)
{
    //ctor
}

Observer::~Observer()
{}

void Observer::parseCommand(const std::string& command)
{
    if (command.empty())
        handleCommand(command);
    else
    {
        char startChar = command.at(0);
        if (startChar == blockStart)
        {
            startBlock();
            return;
        }
        else if (startChar == blockFinish)
        {
            finishBlock();
            return;
        }
        else
        {
            handleCommand(command);
            return;
        }
    }
}