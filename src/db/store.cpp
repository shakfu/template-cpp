#include "db/store.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>

namespace db
{

void Store::demo()
{
    try
    {
        SQLite::Database db("demo.db3",
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        db.exec("DROP TABLE IF EXISTS test");

        // Begin transaction
        SQLite::Transaction transaction(db);

        db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
        std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned "
                  << nb << std::endl;

        // Commit transaction
        transaction.commit();
    }
    catch (std::exception &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

} // namespace db
