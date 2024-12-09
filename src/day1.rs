use std::fs;
use std::collections::BTreeMap;

pub fn day1() {
    let file: String = fs::read_to_string("./input1.txt").unwrap();
    let lines : Vec<&str> = file.split('\n').filter(|line| !line.is_empty()).collect();

    let mut left_col : BTreeMap<i64,i64> = BTreeMap::new();
    let mut right_col : BTreeMap<i64,i64> = BTreeMap::new();

    for (_index,line) in lines.iter().enumerate() {
        let columns: Vec<&str> = line.split_whitespace().collect();

        if columns.len() == 2 {
            let left = columns[0].trim().parse();
            let right = columns[1].trim().parse();
            if let (Ok(left_val), Ok(right_val)) = (left, right) {
                *left_col.entry(left_val).or_insert(0) += 1;
                *right_col.entry(right_val).or_insert(0) += 1;
            }
        }
    }

    let mut distance_sum : i64 = 0;
    let mut left_it = left_col.iter();
    let mut right_it = right_col.iter();
    let mut current_left = left_it.next();
    let mut current_right = right_it.next();
    let mut left_count : i64 = 0;
    let mut right_count : i64 = 0;
    while let (Some((&left_value, &left_freq)), Some((&right_value, &right_freq))) = (current_left, current_right) {
        if left_count == 0 {
            left_count = left_freq;
        }

        if right_count == 0 {
            right_count = right_freq;
        }

        let pending_pairs = left_count.min(right_count);

        distance_sum += pending_pairs * (left_value - right_value).abs();

        left_count -= pending_pairs;
        right_count -= pending_pairs;

        if left_count == 0 {
            current_left = left_it.next();
        }

        if right_count == 0 {
            current_right = right_it.next();
        }
    }

    println!("The sum of the distances is: {}",distance_sum);

}