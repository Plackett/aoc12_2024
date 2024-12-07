use std::io::{self, BufRead};
use std::fs::File;

pub fn day1()
{
    let file = File::open("../input1.txt");

    let file_reader = io::BufReader::new(file);

    let mut left_col: Vec<i32> = Vec::new();
    let mut right_col: Vec<i32> = Vec::new();

    for line in file_reader.lines() {
        let line = line?;
        let columns: Vec<&str> = line.split(' ').collect();

        if(columns.len() == 2)
        {
            left_col.push(columns[0].trim().parse());
            right_col.push(columns[1].trim().parse());
        }
    }

}