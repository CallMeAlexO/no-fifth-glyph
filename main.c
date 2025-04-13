// This function prints to stdout.
int puts(const char *);

// This function prints a char to stdout.
int putc(int, void *);

// This function calls linux syscall
long syscall(long num, ...);

// If glyph is found in string, `has_glyph` == 1. If not, `has_glyph == 0`.
void glyph_in_str(const char *string, char *has_glyph);

// Count all chars in string
void char_count(const char *string, long int *chars);

// If program has -f flag, `has_flag == 1`.
void has_f_flag(int argc, char *argv[], char *has_flag);

// Status == 0
void good_quit();

// Status == 1
void bad_quit();

// Program for inputs that match ptr.
void do_scanp(const char *input);

// Program for inputs that match -f flag.
void do_scanf(int argc, char *argv[]);

// Work on an input - stop program if glyph found.
void work_on_input(const char *input);

/***************************************************/
/****************** Program Start ******************/
/***************************************************/
void work_on_input(const char *input)
{
    if (input == 0)
    {
        bad_quit();
    }

    int fd = syscall(5, input, 0, 0);
    if (fd == -1)
    {
        bad_quit();
    }

    char buff_start[256] = {0};
    char *buff_curr = buff_start;
    char input_has_glyph = 0;
    for (; syscall(3, fd, buff_curr, 1) > 0;)
    {

        // Flush
        if (*buff_curr == '\n' || buff_curr - buff_start == 255)
        {
            *buff_curr = 0;
            glyph_in_str(buff_start, &input_has_glyph);
            if (input_has_glyph) {
                bad_quit();
            }

            buff_curr = buff_start - 1; // Off-by-1 in loop.
        }

        buff_curr++;

    }

    *buff_curr = 0;
    glyph_in_str(buff_start, &input_has_glyph);
    if (input_has_glyph) {
        bad_quit();
    }
}

void glyph_in_str(const char *string, char *has_glyph)
{   
    *has_glyph = 0;
    for (;;)
    {
        if (*string == '\0')
        {
            goto finish;
        }
        if (*string == 69 || *string == 101)
        {
            *has_glyph = 1;
            goto finish;
        }
        string++;
    }
finish:
    asm("nop");
}

void char_count(const char *string, long int *chars)
{
    *chars = 0;
    for (;;)
    {
        if (*string == '\0')
        {
            goto finish;
        }
        (*chars)++;
        string++;
    }
finish:
    asm("nop");
}

void has_f_flag(int argc, char *argv[], char *has_flag)
{
    *has_flag = 0;
    for (int i = 1; i < argc; i++)
    {
        long int chars = 0;
        char_count(argv[i], &chars);
        if (chars == 2 && argv[i][0] == '-' && argv[i][1] == 'f')
        {
            *has_flag = 1;
            goto finish;
        }
    }
finish:
    asm("nop");
}

void do_scanp(const char *input)
{
    char input_has_glyph = 0;
    glyph_in_str(input, &input_has_glyph);

    if (input_has_glyph)
    {
        bad_quit();
    }
    good_quit();
}

void do_scanf(int argc, char *argv[])
{
    if (argc == 2)
    {
        bad_quit();
    }
    for (int i = 1; i < argc; i++)
    {
        if (*argv[i] != '-')
        {
            puts(argv[i]);
            work_on_input(argv[i]);
        }
    }
    good_quit();
}

// This program scans an input and says "WOW!" if your input has no fifth-glyph.
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        bad_quit();
    }

    // Find -f option
    char bool_has_f_flag = 0;
    has_f_flag(argc, argv, &bool_has_f_flag);
    if (bool_has_f_flag)
    {
        do_scanf(argc, argv);
    }
    do_scanp(argv[1]);
}

void good_quit()
{
    puts("WOW!");
    syscall(1, 0);
}

void bad_quit()
{
    puts("Your input is bad!");
    syscall(1, 1);
}