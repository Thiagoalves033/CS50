-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Studying reports from the theft that took place 7/28/2021, Humphrey Street — 10:15am.
SELECT *
FROM crime_scene_reports
WHERE street = 'Humphrey Street'
AND day = 28
AND month = 7;

-- Reading the transcripts from the interviews conducted with the three witnesses
SELECT *
FROM interviews
WHERE transcript LIKE '%bakery%'
AND day = 28;

-- Interview #1: Searching for the licence plates in the security footage from the bakery parking lot
SELECT *
FROM bakery_security_logs
WHERE month = 7
AND day = 28
AND hour = 10
AND (minute >= 15 AND minute <= 25);
-- Plates: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- Interview #2: Checking the bank accounts that withdrew money at the ATM, Leggett Street, earlier in the morning
SELECT account_number
FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND month = 7
AND day = 28
AND transaction_type = 'withdraw';
-- Accounts: 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199

-- Interview #3: Identifying phone calls
SELECT caller, receiver
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <= 60;
--        Caller | Receiver:
--(130) 555-0289 | (996) 555-8899
--(499) 555-9472 | (892) 555-8872
--(367) 555-5533 | (375) 555-8161
--(609) 555-5876 | (389) 555-5198
--(499) 555-9472 | (717) 555-1342
--(286) 555-6063 | (676) 555-6554
--(770) 555-1861 | (725) 555-3243
--(031) 555-6622 | (910) 555-3251
--(826) 555-1652 | (066) 555-9701
--(338) 555-6650 | (704) 555-2131

-- Figuring the earliest flight leaving Fiftyville tomorrow
SELECT flights.id, full_name
FROM flights
JOIN airports ON destination_airport_id = airports.id
WHERE month = 7 AND day = 29
ORDER BY hour
LIMIT 1;
-- Airport: LaGuardia Airport, New York City
-- Flight ID: 36

-- Investigating the flight
SELECT passport_number
FROM passengers
WHERE flight_id = 36;
-- Passport Numbers: 7214083635,1695452385,5773159633,1540955065,8294398571,1988161715,9878712108,8496433585

-- Comparing informations obtained with people credentials
SELECT name, phone_number
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND hour = 10
    AND (minute >= 15 AND minute <= 25)
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND duration <= 60
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE atm_location = 'Leggett Street'
        AND month = 7
        AND day = 28
        AND transaction_type = 'withdraw'
    )
);
-- Thief: Bruce

-- Figuring out who the accomplice is
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
-- Accomplice: Robin