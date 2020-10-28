#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class CommandContainer
{
public:
    CommandContainer() = default;
    CommandContainer(size_t size);

    /**
     * @brief Добавление в хранилище комманд
     * @param strCommand
     */
    void addCommand(const std::string& strCommand);

    /**
     * @brief Вывод комманд в поток
     * @param out
     */
    void printCommands(std::ostream& out = std::cout) const;

    /**
     * @brief Очистка хранилища
     */
    void clear();

    /**
     * @brief Количество команд в хранилище
     * @return Количество команд в хранилище, тип size_t
     */
    size_t size() const;

    /**
     * @brief Проверка на то, пустое ли хранилище команд
     * @return true, если пустое, иначе false
     */
    bool isEmpty() const;

private:
    std::vector<std::string> _commands;
};