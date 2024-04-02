#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Variable necessary to get the number of digits
    int Digits = 1;
//Number prompted by the user
    long N;
    do
    {
        N = get_long("Credit card number: ");
    }
    while (N <= 0);

//Luhn's Algorithm
    int Ar1[8] = {0};
    int Ar2[8] = {0};
    int ArS[8] = {0};
    long K = N;
    long U = N;
//Starting with the number’s second-to-last digit
    for (int i = 0; i < 8; i++)
    {
        U  /= 10;
        Ar1[i] = U % 10 * 2;
        U /= 10;
    }
//Other numbers
    for (int w = 0; w < 8; w++)
    {
        Ar2[w] = K % 10;
        K /= 100;
    }
//Break into digits and sum them
    for (int y = 0; y < 8; y++)
    {
        ArS[y] = Ar1[y] % 10;
        Ar1[y] /= 10;
        ArS[y] += Ar1[y];
    }
//Sum of the array 1
    int T1 = 0;
    for (int z = 0; z < 8; z++)
    {
        T1 += ArS[z];
    }
//Sum of the array 2
    int T2 = 0;
    for (int c = 0; c < 8; c++)
    {
        T2 += Ar2[c];
    }
//Array 1 + Array 2
    int Total = T1 + T2;
    Total = Total % 10;

//Getting the first and second number
    while (N >= 100)
    {
        N /= 10;
        Digits++;
    }
    int S = N;

//Getting the first number
    while (N >= 10)
    {
        N /= 10;
        Digits++;
    }
    int F = N;

//Luhn's algorithm
    if (Total != 0)
    {
        printf("INVALID\n");
    }

//Starts with 4 and has 13 or 16 digits
    else if ((Digits == 13 || Digits == 16) && (F == 4))
    {
        printf("VISA\n");
    }
//Starts with 51,52,53,54 or 55 and has 16 digits
    else if ((Digits == 16) && (S >= 51 && S <= 55))
    {
        printf("MASTERCARD\n");
    }
//Starts with 34 or 37 and has 15 digit number
    else if ((Digits == 15) && (S == 34 || S == 37))
    {
        printf("AMEX\n");
    }
//Other invalid numbers
    else
    {
        printf("INVALID\n");
    }
}