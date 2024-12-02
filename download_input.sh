echo "Enter your session token: "
read session
echo "Enter the day you would like to grab or * for all days: "
read day

if [[ "$day" == "*" ]]; then
  for i in {1..25}; do
    curl "https://adventofcode.com/2024/day/$i/input" -H "Cookie: session=$session" > "input$i.txt"
  done
else
  curl "https://adventofcode.com/2024/day/$day/input" -H "Cookie: session=$session" > "input$day.txt"
fi

echo "Done!"