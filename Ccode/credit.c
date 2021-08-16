#include<cs50.h>
#include<stdio.h>

int main(void)

{
    //prompt
    long n;
    n = get_long("Number: ");
    if (n < 1e13 || n > 1e17 - 1)
    {
        printf("INVALID\n");
    }
    else
    {
        long number = n;

        //introduce variables
        int s1 = 0;
        int s2 = 0;
        int count;
        int length = 0;
        int digit;
        int sum;
        int digitofdigits;
        int length1 = 0;
        int digits;

        //get digits and s1, s2
        do
        {
            digit = n % 10;
            length++;
            if (length % 2 == 1)
            {
                s1 = s1 + digit;
            }
            else if (length % 2 == 0)
            {
                length1 = 0;
                digit = digit * 2;
                do
                {
                    digitofdigits = digit % 10;
                    length1 = length1 + 1;
                    s2 = s2 + digitofdigits;
                    digit = digit / 10;
                }
                while (length1 <= 2);
            }
            n = n / 10;
        }
        while (length <= 16);

        //get sum
        sum = s1 + s2;

        //get the final digit, check if card invalid
        digit = sum % 10;
        if (digit != 0)
        {
            printf("INVALID\n");
        }
        else if (digit == 0)
        {
            if (number > 999999999999999 && number < 10000000000000000)
            { 
                length = 0;
                do
                {
                    number = number / 10;
                    length++;
                }
                while (length < 14);
                if (number > 39 && number < 50)
                {
                    printf("VISA\n");
                }
                else if (number > 50 && number < 56)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (number > 99999999999999 && number < 1000000000000000)
            {
                length = 0;
                do
                {
                    number = number / 10;
                    length++;
                }
                while (length < 13);
                if (number == 34 || number == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (number > 999999999999 && number < 10000000000000)
            {
                length = 0;
                do
                {
                    number = number / 10;
                    length++;
                }
                while (length < 11);
                if (number > 39 && number < 50)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }
}
    
