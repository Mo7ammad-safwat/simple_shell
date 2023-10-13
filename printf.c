#include "all.h"

/**
 * @brief Custom printf function.
 *
 * This function prints formatted output according to a format string.
 *
 * @param format The format string.
 * @param ... Variable arguments list.
 * @return The number of characters printed.
 */
int _printf(const char *format, ...)
{
    unsigned int i, len = 0;
    va_list args;

    // Validate format string
    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format[i]; i++)
    {
        // If the character is not '%', print it directly
        if (format[i] != '%')
        {
            len += print_char(format[i]);
            continue;
        }

        // Handle format specifier
        if ((int)i++ == _strlen((char *)format) - 1)
            return (-1);

        len += specifier(format[i], args);
    }

    va_end(args);
    return (len);
}

/**
 * @brief Handle dots in the passed parameters.
 *
 * This function processes dots in the input line and modifies the parameters accordingly.
 *
 * @param line Input string.
 * @param args Parameter of type para p2.
 */
void handle_dots(char **line, para *args)
{
    int i = 0, len;
    char *line_c = *line, *buffer;

    if (line_c[0] == '.')
    {
        // Initialize buffer
        buffer = malloc2(*line, args, 512);
        buffer[0] = '\0';

        // Concatenate buffer with pwd
        _strcat(buffer, &((*(args->pwd))[4]));
        len = _strlen(buffer);

        while (line_c[i] && line_c[i] != ' ')
        {
            if (line_c[i] == '.' && line_c[i + 1] == '.')
            {
                // Handle dots in the buffer
                while (buffer[len - 1] != '/')
                    buffer[(len--) - 1] = '\0';

                buffer[(len--) - 1] = '\0';
                i++;
            }
            else if (line_c[i] != '/' && line_c[i] != '.')
            {
                // Handle characters other than '/' and '.'
                buffer[len++] = '/';
                while (line_c[i] && line_c[i] != '/' && line_c[i] != ' ')
                    buffer[len++] = line_c[i++];

                i--;
            }
            i++;
        }

        buffer[len] = '\0';

        // Check if the modified buffer is executable
        if (access(buffer, X_OK) == 0)
        {
            _strcat(buffer, &line_c[i]);
            free(*line);
            *line = buffer;
        }
    }
}

/**
 * @brief Allocate memory using malloc2.
 *
 * This function handles memory allocation using malloc2.
 *
 * @param line Input string.
 * @param args Parameter of type para p2.
 * @param size The size of the buffer.
 * @return The allocated buffer.
 */
char *malloc2(char *line, para *args, int size)
{
    char *buffer = malloc(size);

    // Handle memory allocation failure
    if (!buffer)
    {
        free(line);
        free_exit(args);
    }

    return buffer;
}

/**
 * @brief Tokenize a string.
 *
 * This function returns the number of tokens obtained by splitting the input string.
 *
 * @param line The string to be split.
 * @param delim The delimiter used to split the string.
 * @return The number of tokens.
 */
int token(char *line, char *delim)
{
    int n_token = 0;
    char *str_token = _strtok(line, delim);

    while (str_token)
    {
        str_token = _strtok(NULL, delim);
        n_token++;
    }

    return n_token;
}

