#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int C;
    do
    {
        C = get_int("Change owed: ");
    }
    while (C < 0);
    return C;
}

int calculate_quarters(int cents)
{
    int Q = 0;
    while (cents >= 25)
    {
        Q++;
        cents = cents - 25;
    }
    return Q;
}

int calculate_dimes(int cents)
{
    int D = 0;
    while (cents >= 10)
    {
        D++;
        cents = cents - 10;
    }
    return D;
}

int calculate_nickels(int cents)
{
    int N = 0;
    while (cents >= 5)
    {
        N++;
        cents = cents - 5;
    }
    return N;
}

int calculate_pennies(int cents)
{
    int P = 0;
    while (cents >= 1)
    {
        P++;
        cents = cents - 1;
    }
    return P;
}
