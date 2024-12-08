use std::fs;
use std::collections::HashMap;
use std::collections::HashSet;

pub fn day8()
{
    let file : String = fs::read_to_string("../input8.txt").unwrap();
    let lines : Vec<&str> = file.split('\n').collect();

    let mut antennas = HashMap::<char,Vec<(i32,i32)>>::new();
    let mut direct_antinodes = HashSet::<(i32,i32)>::new();
    let mut harmonic_antinodes = HashSet::<(i32,i32)>::new();

    let mut vert_size = i32::try_from(lines.len()).unwrap();
    let mut horz_size = 0;

    for (curr_line,line) in lines.iter().enumerate() {
        for (index,c) in line.chars().enumerate() {
            if c != '.' {
                antennas.entry(c).or_insert(Vec::new()).push((i32::try_from(index).unwrap(),i32::try_from(curr_line).unwrap()));
            }
        }
        horz_size = i32::try_from(line.len()).unwrap();
    }

    for group in antennas {
        let mut antenna_positions = group.1;
        for pos in &antenna_positions {
            for postwo in &antenna_positions {
                if pos == postwo { continue };
                let dist_x = postwo.0 - pos.0;
                let dist_y = postwo.1 - pos.1;
                let candidate_one = (pos.0 - dist_x,pos.1 - dist_y);
                let candidate_two = (pos.0 + dist_x,pos.1 + dist_y);
                if candidate_one.0 >= 0 && candidate_one.1 >= 0 && candidate_one.0 < horz_size && candidate_one.1 < vert_size {
                    direct_antinodes.insert(candidate_one);
                }
                if candidate_two.0 >= 0 && candidate_two.1 >= 0 && candidate_two.0 < horz_size && candidate_two.1 < vert_size {
                    direct_antinodes.insert(candidate_two);
                }
            }
        }
    }
    println!("Number of direct antinodes: {:?}",direct_antinodes);
    println!("Number of harmonic antinodes (including direct): {}", harmonic_antinodes.len());
}