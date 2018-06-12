#ifndef C_SQLITE_SQLITE_QUERY_H_
#define C_SQLITE_SQLITE_QUERY_H_

#include <string>
#include <vector>

struct Record
{
  std::string key;
  std::string description;
};

int sqlite_query(const std::string &db_filepath,
  const std::string &table_name,
  const std::string &cols,
  std::vector<Record> &records);

#endif
