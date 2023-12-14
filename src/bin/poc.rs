use sonic_swss_common_rs::{
    to_table,
    ffi::{create_dbconnector, create_table, table_get}
};

fn insert_values() {
    let connector = create_dbconnector("STATE_DB", 0, true);
    let table = create_table(&connector, "TEST_TABLE_4");

    let fvp = vec! [
        ("field1".to_string(), "value1".to_string()),
        ("field2".to_string(), "value2".to_string())
    ];
   
    to_table(&table, "key1", fvp);
}

fn retrieve_value() {
    let connector = create_dbconnector("STATE_DB", 0, true);
    let table = create_table(&connector, "TEST_TABLE_4");

    let mut output_fields: Vec<String> = vec![];
    let mut output_values: Vec<String> = vec![];

    table_get(&table, "key1", &mut output_fields, &mut output_values);

    println!("{output_fields:#?} {output_values:#?}");
}
    
fn main() {
    println!("main!");

    insert_values();
    retrieve_value();
}
