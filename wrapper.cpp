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

  bool table_get(const std::unique_ptr<swss::Table>& table, const rust::Str key, rust::Vec<rust::String> &fields, rust::Vec<rust::String> &values) {

    std::vector<FieldValueTuple> outputValues;
    
    std::string keyCpp(key);
    
    bool result = table->get(keyCpp, outputValues);

    if (result) {
      for (size_t i = 0; i < outputValues.size(); i++) {
        fields.emplace_back(outputValues[i].first);
        values.emplace_back(outputValues[i].second);
      }
    }

    return result;
  }

  bool table_hget(const std::unique_ptr<swss::Table>& table, const rust::Str key, rust::String &field, rust::String &value) {
    std::string keyCpp(key);
    std::string fieldCpp;
    std::string valueCpp;

    bool result = table->hget(keyCpp, fieldCpp, valueCpp);

    if (result) {
      field = fieldCpp;
      value = valueCpp;
    }

    return result;
  }

  void table_hset(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::String &field, const rust::String &value, const rust::Str op, const rust::Str prefix) {
    std::string fieldCpp(field);
    std::string valueCpp(value);
    std::string keyCpp(key);
    std::string opCpp(op);
    std::string prefixCpp(prefix);
    
    // Call the set method on the table
    table->hset(keyCpp, fieldCpp, valueCpp, opCpp, prefixCpp);
  }

  void table_del(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Str op, const rust::Str prefix) {

    std::string keyCpp(key);
    std::string opCpp(op);
    std::string prefixCpp(prefix);
    
    // Call the set method on the table
    table->del(keyCpp, opCpp, prefixCpp);
  }

  void table_hdel(const std::unique_ptr<swss::Table>& table, const rust::Str key, const rust::Str op, const rust::Str prefix) {

    std::string keyCpp(key);
    std::string opCpp(op);
    std::string prefixCpp(prefix);
    
    // Call the set method on the table
    table->hdel(keyCpp, opCpp, prefixCpp);
  }

  void table_flush(const std::unique_ptr<swss::Table>& table) {
    table->flush();
  }
}
