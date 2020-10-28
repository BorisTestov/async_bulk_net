#include "command_container.h"

#include <sstream>

CommandContainer::CommandContainer(size_t size)
{
    _commands.reserve(size);
}

void CommandContainer::addCommand(const std::string& strCommand)
{
    _commands.push_back(strCommand);
}

void CommandContainer::printCommands(std::ostream& out) const
{
    if (!_commands.empty())
    {
        std::stringstream output;
        output << "bulk:";
        for (size_t i = 0; i < _commands.size(); i++)
        {
            output << _commands.at(i);
            if (i + 1 != _commands.size())
            {
                output << ",";
            }
        }
        out << output.str() << std::endl;
    };
}

void CommandContainer::clear()
{
    _commands.clear();
}

size_t CommandContainer::size() const
{
    return _commands.size();
}

bool CommandContainer::isEmpty() const
{
    return _commands.empty();
}