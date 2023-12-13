#include "wrapper.h"

namespace swss {
  std::unique_ptr<DBConnector> create_dbconnector(rust::Str dbName, unsigned int timeout, bool isTcpConn) {
    std::string dbNameCpp(dbName);  // Convert from rust::Str to std::string
    return std::make_unique<DBConnector>(dbNameCpp, timeout, isTcpConn);
  }

  std::unique_ptr<Table> create_table(const DBConnector& db, const rust::Str tableName) {
    std::string tableNameCpp(tableName);  // Convert from rust::Str to std::string
    return std::make_unique<Table>(&db, tableNameCpp);
  }

  void table_set(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Vec<rust::String> &fields, const rust::Vec<rust::String> &values, const rust::Str op, const rust::Str prefix) {
    // Convert Rust Vecs to std::vector<FieldValueTuple>
    std::vector<FieldValueTuple> convertedValues;
    for (size_t i = 0; i < fields.size(); i++) {
      std::string fieldCpp(fields[i]);
      std::string valueCpp(values[i]);
      convertedValues.emplace_back(fieldCpp, valueCpp);
    }

    std::string keyCpp(key);
    std::string opCpp(op);
    std::string prefixCpp(prefix);
    
    // Call the set method on the table
    table->set(keyCpp, convertedValues, opCpp, prefixCpp);
  }  
}
