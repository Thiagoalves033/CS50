from cs50 import SQL
import csv

database = SQL("sqlite:///prophecies.db")

with open("students.csv") as csvfile:
    file = csv.DictReader(csvfile)

    houses = [
    ('Slytherin', 'Severus Snape'),
    ('Ravenclaw', 'Filius Flitwick'),
    ('Hufflepuff', 'Pomona Sprout'),
    ('Gryffindor', 'Minerva McGonagall')
    ]

    for house in houses:
             database.execute(
            "INSERT INTO houses(house_name, head_name) VALUES(?)", house
        )

    for row in file:

        database.execute(
            "INSERT INTO students(id, student_name) VALUES(?, ?)",
            row["id"],
            row["student_name"],
        )

        hid = database.execute("SELECT id FROM houses WHERE house_name = ?", row["house"])

        database.execute(
            "INSERT INTO assignments(student_id, house_id) VALUES(?, ?)",
            row["id"],
            hid[0]["id"],
        )
