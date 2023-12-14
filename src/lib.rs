#[cxx::bridge(namespace = "swss")]
pub mod ffi {
    unsafe extern "C++" {
        include!("sonic-swss-common-rs/wrapper.h");

        type DBConnector;
        type Table;
        type FieldValueTuple;
        
        fn create_dbconnector(dbName: &str, timeout: u32, isTcpConn: bool) -> UniquePtr<DBConnector>;
        fn create_table(db: &DBConnector, tableName: &str) -> UniquePtr<Table>;
        fn table_set(table: &UniquePtr<Table>, key: &str, fields: &Vec<String>, values: &Vec<String>, op: &str, prefix: &str);
        fn table_get(table: &UniquePtr<Table>, key: &str, fields: &mut Vec<String>, values: &mut Vec<String>) -> bool;
        fn table_hget(table: &UniquePtr<Table>, key: &str, field: &mut String, value: &mut String) -> bool;
        fn table_hset(table: &UniquePtr<Table>, key: &str, field: &String, value: &String, op: &str, prefix: &str);
        fn table_del(table: &UniquePtr<Table>, key: &str, op: &str, prefix: &str);
        fn table_hdel(table: &UniquePtr<Table>, key: &str, op: &str, prefix: &str);
        fn table_flush(table: &UniquePtr<Table>);
    }
}

pub fn to_table(table: &cxx::UniquePtr<ffi::Table>, key: &str, fvp: Vec<(String, String)>) {
    let (fields, values) = fvp.into_iter().unzip();

    ffi::table_set(table, key, &fields, &values, "", "");
}

