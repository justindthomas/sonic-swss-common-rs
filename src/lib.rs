#[cxx::bridge(namespace = "swss")]
mod ffi {
    unsafe extern "C++" {
        include!("sonic-swss-common-rs/wrapper.h");

        type DBConnector;
        type Table;
        type FieldValueTuple;
        
        fn create_dbconnector(dbName: &str, timeout: u32, isTcpConn: bool) -> UniquePtr<DBConnector>;
        fn create_table(db: &DBConnector, tableName: &str) -> UniquePtr<Table>;
        fn table_set(table: &UniquePtr<Table>, key: &str, fields: &Vec<String>, values: &Vec<String>, op: &str, prefix: &str);
    }
}

pub fn to_table(table: &cxx::UniquePtr<crate::ffi::Table>, fvp: Vec<(String, String)>) {
    let (fields, values) = fvp.into_iter().unzip();

    crate::ffi::table_set(table, "key1", &fields, &values, "", "");
}

pub fn connect() {
    let connector = crate::ffi::create_dbconnector("STATE_DB", 0, true);
    let table = crate::ffi::create_table(&connector, "TEST_TABLE_3");

    let fvp = vec! [
        ("field1".to_string(), "value1".to_string()),
        ("field2".to_string(), "value2".to_string())
    ];
   
    to_table(&table, fvp);
}
