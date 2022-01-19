#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <pqxx/pqxx>

#include "doctest.h"


int test_db()
{
    // Connect to the database.
    pqxx::connection c{"postgresql://sa@localhost/sa"};
    std::cout << "Connected to " << c.dbname() << '\n';

    // Start a transaction.
    pqxx::work W{c};

    // Perform a query and retrieve all results.
    pqxx::result R{W.exec("SELECT name FROM employee")};

    // Iterate over results.
    std::cout << "Found " << R.size() << "employees:\n";
    for (auto row: R)
        std::cout << row[0].c_str() << '\n';

    // Perform a query and check that it returns no result.
    std::cout << "Doubling all employees' salaries...\n";
    W.exec0("UPDATE employee SET salary = salary*2");

    // Commit the transaction.
    std::cout << "Making changes definite: ";
    W.commit();
    std::cout << "OK.\n";
}
