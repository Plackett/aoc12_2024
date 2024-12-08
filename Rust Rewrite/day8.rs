use std::fs;
use std::collections::HashMap;
use std::collections::HashSet;

pub fn day8() {
    let file: String = fs::read_to_string("../input8.txt").unwrap();
    let lines: Vec<&str> = file.split('\n').filter(|line| !line.is_empty()).collect();

    let mut antennas = HashMap::<char, Vec<(i32, i32)>>::new();
    let mut direct_antinodes = HashSet::<(i32, i32)>::new();
    let mut harmonic_antinodes = HashSet::<(i32, i32)>::new();

    let vert_size = i32::try_from(lines.len()).unwrap();
    let horz_size = if let Some(first_line) = lines.get(0) {
        i32::try_from(first_line.len()).unwrap()
    } else {
        0
    };

    for (curr_line, line) in lines.iter().enumerate() {
        for (index, c) in line.chars().enumerate() {
            if c != '.' {
                antennas
                    .entry(c)
                    .or_insert(Vec::new())
                    .push((i32::try_from(index).unwrap(), i32::try_from(curr_line).unwrap()));
            }
        }
    }

    for group in antennas {
        let antenna_positions = group.1;
        for (i, pos) in antenna_positions.iter().enumerate() {
            for (j, postwo) in antenna_positions.iter().enumerate() {
                if i == j {
                    continue;
                }
                let dist_x = postwo.0 - pos.0;
                let dist_y = postwo.1 - pos.1;

                let candidate_one = (pos.0 - dist_x, pos.1 - dist_y);
                let candidate_two = (postwo.0 + dist_x, postwo.1 + dist_y);

                // why does pointer work here? explain how I am dereferencing a tuple?
                harmonic_antinodes.insert(*pos);
                harmonic_antinodes.insert(*postwo);

                if candidate_one.0 >= 0
                    && candidate_one.1 >= 0
                    && candidate_one.0 < horz_size
                    && candidate_one.1 < vert_size
                {
                    direct_antinodes.insert(candidate_one);
                    harmonic_antinodes.insert(candidate_one);
                }

                if candidate_two.0 >= 0
                    && candidate_two.1 >= 0
                    && candidate_two.0 < horz_size
                    && candidate_two.1 < vert_size
                {
                    direct_antinodes.insert(candidate_two);
                    harmonic_antinodes.insert(candidate_two);
                }

                let mut next_candidate = candidate_one;
                loop {
                    next_candidate.0 -= dist_x;
                    next_candidate.1 -= dist_y;
                    if next_candidate.0 < 0
                        || next_candidate.1 < 0
                        || next_candidate.0 >= horz_size
                        || next_candidate.1 >= vert_size
                    {
                        break;
                    }
                    harmonic_antinodes.insert(next_candidate);
                }

                next_candidate = candidate_two;
                loop {
                    next_candidate.0 += dist_x;
                    next_candidate.1 += dist_y;
                    if next_candidate.0 < 0
                        || next_candidate.1 < 0
                        || next_candidate.0 >= horz_size
                        || next_candidate.1 >= vert_size
                    {
                        break;
                    }
                    harmonic_antinodes.insert(next_candidate);
                }
            }
        }
    }

    println!("Number of direct antinodes: {}", direct_antinodes.len());
    println!(
        "Number of harmonic antinodes (including direct): {}",
        harmonic_antinodes.len()
    );
}