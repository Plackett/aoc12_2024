use std::fs;
use std::collections::BTreeMap;

/*pub fn day1() {
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

}*/

pub fn day1() -> Result<(), Box<dyn std::error::Error>> {
    let data_in = fs::read_to_string("./input1.txt")?;
    let binding: Vec<i32> = data_in.split_whitespace().map(|a| a.parse::<i32>().unwrap()).collect();
    let size = binding.len();

    let (mut left, mut right) = (BTreeMap::new(), BTreeMap::new());

    let mut bind_it = binding.iter();

    loop {
        if let (Some(l), Some(r)) = (bind_it.next(), bind_it.next()) {
            *right.entry(*l).or_insert(0) += 1;
            *left.entry(*r).or_insert(0) += 1;
        } else {
            break
        }
    }

    // println!("{:?}, {:?}", left, right);

    let mut sum = 0;

    let mut left_it = left.iter();
    let mut right_it = right.iter();

    let (mut val_left, mut val_right) = (0, 0);
    let (mut left_left, mut left_right) = (0, 0);

    let mut count = 0;
    while count < size / 2 {
        if left_left == 0 {
            let temp = left_it.next().unwrap();
            val_left = *temp.0;
            left_left = *temp.1;
        }

        if left_right == 0 {
            let temp = right_it.next().unwrap();
            val_right = *temp.0;
            left_right = *temp.1;
        }

        let min: i32 = left_left.min(left_right);

        sum += min * val_left.abs_diff(val_right) as i32;
        // println!("{}, {}, {}, {}", min, sum, val_left, val_right);

        count += usize::try_from(min)?;

        if left_left == left_right {
            left_right = 0;
            left_left = 0;
        } else if left_left < left_right {
            left_left = 0;
            left_right -= min;
        } else {
            left_right = 0;
            left_left -= min;
        }
    }

    println!("{}", sum);

    let mut dup = 0;

    for (key, val) in left {
        dup += key * val * *right.entry(key).or_insert(0);
    }

    println!("{}", dup);

    Ok(())
}