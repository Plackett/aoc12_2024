use std::fs::File;
use std::io::{self, BufRead, BufReader};

pub fn day1() -> io::Result<()> {
    // Handle the result of File::open
    let file = File::open("../input1.txt")?;
    let file_reader = BufReader::new(file);

    let mut left_col: Vec<i32> = vec![];
    let mut right_col: Vec<i32> = vec![];

    for line in file_reader.lines() {
        let line = line?; // Handle the result of line reading
        let columns: Vec<&str> = line.split(' ').collect();

        if columns.len() == 2 {
            if let Ok(left) = columns[0].trim().parse() {
                left_col.push(left);
            }
            if let Ok(right) = columns[1].trim().parse() {
                right_col.push(right);
            }
        }
    }

    println!("Left Column: {:?}", left_col);
    println!("Right Column: {:?}", right_col);

    Ok(())
}