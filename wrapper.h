#include "ext/sonic-swss-common/common/dbconnector.h"  // Include the DBConnector header
#include "ext/sonic-swss-common/common/table.h"
#include <rust/cxx.h>  

namespace swss {
  std::unique_ptr<DBConnector> create_dbconnector(rust::Str dbName, unsigned int timeout, bool isTcpConn);
  std::unique_ptr<Table> create_table(const DBConnector& db, const rust::Str tableName);
  void table_set(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Vec<rust::String> &fields, const rust::Vec<rust::String> &values, const rust::Str op, const rust::Str prefix);
  bool table_get(const std::unique_ptr<swss::Table>& table, const rust::Str key, rust::Vec<rust::String> &fields, rust::Vec<rust::String> &values);
  bool table_hget(const std::unique_ptr<swss::Table>& table, const rust::Str key, rust::String &field, rust::String &value);
  void table_hset(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::String &field, const rust::String &value, const rust::Str op, const rust::Str prefix);
  void table_del(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Str op, const rust::Str prefix);
  void table_hdel(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Str op, const rust::Str prefix);
  void table_flush(const std::unique_ptr<swss::Table>& table);
}
