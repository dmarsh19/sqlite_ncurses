#include "sqlite_query.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

int sqlite_query(const std::string &db_filepath,
  const std::string &table_name,
  const std::string &cols,
  std::vector<Record> &records)
{
  int rc = 0;
  int step;
  std::string sql_statement = "SELECT ";
  sqlite3 *pDb;
  sqlite3_stmt *pStmt;

  sql_statement += cols;
  sql_statement += " FROM ";
  sql_statement += table_name;

  rc = sqlite3_open(db_filepath.c_str(), &pDb);
  if (rc != SQLITE_OK) {
    std::cerr << "sqlite3_open err: " << rc << '\n';
    return rc;
  }

  rc = sqlite3_prepare_v2(pDb, sql_statement.c_str(), -1, &pStmt, 0);
  if (rc != SQLITE_OK)
    std::cerr << "sqlite3_prepare_v2 err: " << sqlite3_errmsg(pDb) << '\n';

  step = sqlite3_step(pStmt);
  while (step == SQLITE_ROW) {
    // The cast changes the type of the return value to match the type needed 
    // by the string constructor. Then construct a string using that pointer. 
    records.push_back({
      std::string(reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 0))),
      std::string(reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 1)))
    });
    step = sqlite3_step(pStmt);
  }

  rc = sqlite3_finalize(pStmt);
  if (rc != SQLITE_OK)
    std::cerr << "sqlite3_finalize err: " << rc << '\n';

  rc = sqlite3_close(pDb);
  if (rc != SQLITE_OK)
     std::cerr << "sqlite3_close err: " << rc << '\n';

  return rc;
}

