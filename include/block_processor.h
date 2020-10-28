#pragma once

#include "command_container.h"
#include "observer.h"

#include <ctime>
#include <fstream>

class BlockProcessor : public Observer
{
public:
    BlockProcessor(void* handle);
    virtual ~BlockProcessor();

    /**
     * @brief Возвращает время первой команды
     * @return Время первой команды (time_t)
     */
    std::time_t getTime() const;

protected:
    void handleCommand(const std::string& command) override;
    void startBlock() override;
    void finishBlock() override;

    /**
     * @brief Метод логгирования блока команд
     */
    void logBlock();

private:
    size_t _blockCounter = 0;
    std::time_t _timeStart = 0;
    CommandContainer _store;
};