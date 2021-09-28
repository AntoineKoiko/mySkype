/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database
*/

#include "Database.hpp"

int main(int argc, char *argv[])
{
    Database database;

    if (argc != 3) {
        std::cout << "Wrong number of arguments -- ./??? name sql" << std::endl;
        return 84;
    }
    database.func(argv[1], argv[2]);
    return 0;
}
