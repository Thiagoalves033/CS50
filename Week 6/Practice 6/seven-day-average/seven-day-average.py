import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    # Read each row of the file
    for row in reader:
        case = {"state": row["state"], "date": row["date"], "cases": int(row["cases"])}

        # Adding the state to the dictionary and correcting the number of cases
        if case["state"] in new_cases:
            n = case["cases"] - previous_cases[case["state"]]["cases"]
            new_cases[case["state"]].append({"date": case["date"], "cases": n})

            previous_cases[case["state"]]["cases"] += n

            # No more than 14 days
            if len(new_cases[case["state"]]) > 14:
                del new_cases[case["state"]][0]

        elif case["state"] not in new_cases:
            new_cases[case["state"]] = [{"date": row["date"], "cases": row["cases"]}]
            previous_cases[case["state"]] = {"cases": int(row["cases"])}

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    # Creating a list with the cases
    for state in states:
        case_list = []
        current_state = new_cases[state]
        for date in current_state:
            case_list.append(date["cases"])

        # Previous week average
        previous = sum(case_list[0:7]) // 7

        # Current week average
        current = sum(case_list[7:14]) // 7

        # Percent increase or decrease
        percent = round(((current - previous) / previous) * 100)

        # Printing
        if percent < 0:
            percent *= -1
            print(
                f"{state} had a 7-day average of {current} cases and a decrease of {percent}%."
            )
        else:
            print(
                f"{state} had a 7-day average of {current} and a increase of {percent}%."
            )


main()
