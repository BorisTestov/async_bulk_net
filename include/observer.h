#pragma once

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class Observer
{
public:
    const char blockStart = '{';
    const char blockFinish = '}';
    Observer(void* handle);
    virtual ~Observer();

    /**
     * @brief Метод для парсинга входной строки. Вызывается классом, который подключает обработчики
     * @param command Строка для парсинга
     */
    void parseCommand(const std::string& command);

    /**
     * @brief Метод обработки команды
     * @param command Команда для обработки
     */
    virtual void handleCommand(const std::string& command) = 0;

    /**
     * @brief Метод обработки начала блока
     */
    virtual void startBlock() = 0;

    /**
     * @brief Метод обработки конца блока
     */
    virtual void finishBlock() = 0;

protected:
    void* handle_;
};

using observerPtr = std::shared_ptr<Observer>;