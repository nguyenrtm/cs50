#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void)

{
    string s = get_string("Text: ");
    int countletter = 0;
    int countword = 1;
    int countsentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            countletter++;
        }
    for (int i = 0, n = strlen(s); i < n; i++)
        if (s[i] == 32)
        {
            countword++;
        }
    for (int i = 0, n = strlen(s); i < n; i++)
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            countsentences++;
        }
    float L = (((float) countletter / countword) * 100);
    float X = (((float) countsentences / countword) * 100);
    float index = 0.0588 * L - 0.296 * X - 15.8;
    int final = round(index);
    if (final > 16)
    {
        printf("Grade 16+");
    }
    else if (final < 1)
    {
        printf("Before Grade 1");
    }
    else 
    {
        printf("Grade %i", final);
    }
    printf("\n");
}