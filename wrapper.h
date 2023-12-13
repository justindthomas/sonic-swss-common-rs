#include "../common/dbconnector.h"  // Include the DBConnector header
#include "../common/table.h"
#include <rust/cxx.h>  

namespace swss {
  std::unique_ptr<DBConnector> create_dbconnector(rust::Str dbName, unsigned int timeout, bool isTcpConn);
  std::unique_ptr<Table> create_table(const DBConnector& db, const rust::Str tableName);
  void table_set(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Vec<rust::String> &fields, const rust::Vec<rust::String> &values, const rust::Str op, const rust::Str prefix);
}
