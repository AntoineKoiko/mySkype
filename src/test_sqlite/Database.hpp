/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Databse
*/

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

class Database
{
    public :
        Database();
        ~Database();

        int func(const char *name, const char *sql);

    protected :

    private :

};



#endif /* !DATABASE_HPP */
