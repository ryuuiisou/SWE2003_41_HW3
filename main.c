#include <stdio.h>
#include <string.h>
#define BUF_MAX 10000

int is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int is_underscore(char c)
{
    return c == '_';
}

const char *keywords[] = {
    "int", "double", "char", "for", "while", "if", "else",
    "break", "continue", "goto", "return"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

int is_keyword(const char *str)
{
    for (int i = 0; i < num_keywords; ++i)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void check_token(const char *input_string)
{
    int state = 0;
    int i = 0;

    if (input_string == NULL || input_string[0] == '\0')
    {
        printf("invalid\n");
        return;
    }

    while (input_string[i] != '\0')
    {
        char current_char = input_string[i];
        int next_state = -1;

        if (state == 0)
        {
            if (is_letter(current_char))
            {
                next_state = 1;
            }
            else if (is_underscore(current_char))
            {
                next_state = 2;
            }
            else if (is_digit(current_char))
            {
                next_state = 3;
            }
            else
            {
                next_state = -1;
            }
        }
        else if (state == 1)
        {
            if (is_letter(current_char) || is_digit(current_char) || is_underscore(current_char))
            {
                next_state = 1;
            }
            else
            {
                next_state = -1;
            }
        }
        else if (state == 2)
        {
            if (is_letter(current_char) || is_digit(current_char) || is_underscore(current_char))
            {
                next_state = 1;
            }
            else
            {
                next_state = -1;
            }
        }
        else if (state == 3)
        {
            if (is_digit(current_char))
            {
                next_state = 3;
            }
            else
            {
                next_state = -1;
            }
        }
        else
        {
            next_state = -1;
        }

        if (next_state == -1)
        {
            state = -1;
            break;
        }

        state = next_state;
        i++;
    }

    if (state == -1)
    {
        printf("invalid\n");
    }
    else if (state == 1)
    {
        if (is_keyword(input_string))
        {
            printf("<keyword>\n");
        }
        else
        {
            printf("<id>\n");
        }
    }
    else if (state == 2)
    {
        printf("ID\n");
    }
    else if (state == 3)
    {
        printf("<number>\n");
    }
    else
    {
        printf("invalid\n");
    }
}

int main()
{
    char input[BUF_MAX];

    printf("input: ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        input[strcspn(input, "\n")] = '\0';

        check_token(input);
    }
    else
    {
        fprintf(stderr, "input error\n");
    }

    return 0;
}