#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, string argv[])

{
    if (argc != 2) 
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {   
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./ceasar key\n");
                return 1;
            }
        string text = get_string("plaintext: ");
        int n = atoi(argv[1]);
        for (int i = 0, m = strlen(text); i < m; i++)
            if ((text[i] > 64) && (text[i] < 91))
            {
                text[i] = (text[i] + n - 65) % 26 + 65;
            }
            else if ((text[i] > 96) && (text[i] < 123))
            {
                text[i] = (text[i] + n - 97) % 26 + 97;
            }
        printf("ciphertext: %s\n", text);
    }
}
