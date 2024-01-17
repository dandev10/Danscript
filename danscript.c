#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/*
1 : danscript.
2 : a programming language that uses few
3 : char which is in the comment 4
4 : + . [ ] > < 1 2 3 4 5 6 7 8 9 0 - *
5 : in this file is the code of Danscript
*/

int convert(long long n)
{

    uint8_t dec = 0;
    int i = 0, rem;

    while (n != 0)
    {

        // get remainder of n divided by 10
        rem = n % 10;

        // divide n by 10
        n /= 10;

        // multiply rem by (2 ^ i)
        // add the product to dec
        dec += rem * pow(2, i);

        // increment i
        ++i;
    }

    return dec;
}

void compile_code(const char *code, size_t code_size)
{
    uint8_t memory[32000];
    uint8_t address = 0;

    char binary[8] = "";

    for (int i = 0; i < code_size; i++)
    {
        switch (code[i])
        {
        case '[':
        {
            int j = 0;
            i++;
            while (code[i] != ']')
            {
                // printf("%c\n", code[i]);
                char id = '0';
                switch (code[i])
                {
                case '0':
                case '-':
                    id = '0';
                    break;

                case '1':
                case '+':
                    id = '1';
                    break;
                

                default:
                    break;
                }
                // printf("%d\n", id);
                binary[j] = id;

                i++;
                j++;
            }
            memory[address] = convert(atoll(binary));
            printf("%c", memory[address]);
        }
        break;

        case '>':
            address++;
            break;

        case '<':
            address--;
            break;

        case '.':
            printf("%c", memory[address]);
            break;

        default:
            break;
        }
    }
}

int main(int argc, char **argv)
{
    char src[4000];

    if (argc < 2)
    {
        printf("no .ds file were provided.\n");
        exit(1);
    }

    FILE *f = (errno = 0, fopen(argv[1], "r"));

    if (f == NULL)
    {
        if (errno != 0)
        {
            fprintf(stderr, "Could not open input file, for this reason: %s\n!",
                    strerror(errno));
            exit(1);
        }
        else
        {
            fprintf(stderr, "Could not open input file, for some reason.\n");
            exit(1);
        }
    }
    fread(src, 4000, 1, f);
    fclose(f);

    compile_code(src, strlen(src));
}

// Special Thanks for this code by nikeedev.