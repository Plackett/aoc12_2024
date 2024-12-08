use std::time::Instant;

use console::Term;

mod day1;
use day1::day1;

mod day8;
use day8::day8;

fn user_input(term : &Term)
{
    match term.read_char() {
        // I will never understand Result<char, std::io::Error> type
        Ok(input) => match input {
            '1' => {
                let start_time = Instant::now();
                day1();
                println!("Execution time: {:.2?} seconds", start_time.elapsed().as_secs_f64());
            },
            '8' => {
                let start_time = Instant::now();
                day8();
                println!("Execution time: {:.2?} seconds", start_time.elapsed().as_secs_f64());
            },
            // add more as I rewrite them ig
            '*' => {
                let start_time = Instant::now();
                // all days go here
                day1();
                day8();

                println!("Execution time for all days: {:.2?} seconds", start_time.elapsed().as_secs_f64());
            },
            _ => {
                println!("try again with a day number or *.");
                user_input(term);
            }
        },
        Err(e) => {
            println!("I know where you live {}", e);
        }
    }
}

fn main()
{

    let term = Term::stdout();
    println!("Enter the number of the day or * for all days: ");
    user_input(&term);
}