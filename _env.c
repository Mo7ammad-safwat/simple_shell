#include "all.h"

/**
 * @brief Reallocate memory and copy the content from the old buffer.
 *
 * This function reallocates memory for a buffer and copies the content from the old buffer.
 *
 * @param ptr Old buffer.
 * @param old_size The old buffer size.
 * @param new_size The new buffer size.
 * @return The new buffer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *buffer;
unsigned int i;

if (new_size == old_size)
return ptr;

if (new_size == 0 && ptr != NULL)
{
free(ptr);
return NULL;
}

buffer = malloc(new_size);

if (buffer == NULL)
{
if (ptr)
free(ptr);
return NULL;
}

if (ptr == NULL)
return buffer;

for (i = 0; i < old_size && i < new_size; i++)
{
buffer[i] = ((char *)ptr)[i];
}

free(ptr);
return buffer;
}

/**
 * @brief Convert a string to an integer.
 *
 * This function converts a string to an integer.
 *
 * @param str The input string.
 * @return The converted integer.
 */
int _atoi(char *str)
{
int i = (_strlen(str) - 1), j, num = 0, power = 1;

for (j = 0; j <= i; j++)
{
if (str[i - j] > 47 && str[i - j] < 58)
{
num += (str[i - j] - 48) * power;
power *= 10;
}
else
return  -1;  
}

return  num;
}

/**
 * @brief Check if the input is "env" and print environment variables.
 *
 * This function checks if the input is "env" and prints the environment variables.
 *
 * @param args Parameter of type para.
 * @return 1 if input is "env", 0 otherwise.
 */
int _env(para *args)
{
int i;

if (rev_cmp(args->line, "env"))
{
for (i = 0; args->envp[i] != NULL; i++)
{
write(1, args->envp[i], _strlen(args->envp[i]));
write(1, "\n", 1);
}

args->status = 0;
return 1;
}

return 0;
}

/**
 * @brief Get the value of a specific environmental variable.
 *
 * This function retrieves the value of a specific environmental variable.
 *
 * @param envp Array of environmental variables.
 * @param env The variable to search for.
 * @param len Length of the variable to search for.
 * @return The value of the variable or NULL if not found.
 */
char *_get_env(char **envp, char *env, int len)
{
int i;

for (i = 0; envp[i] != NULL; i++)
{
if (_strncmp(envp[i], env, len) == 0)
return &(envp[i][len + 1]);
}

return NULL;
}

/**
 * @brief Handle realloc and free resources in case of failure.
 *
 * This function handles realloc and frees resources in case of failure.
 *
 * @param args Parameter of type para.
 * @param buffer Buffer to be reallocated.
 * @param buffer_size The current buffer size.
 * @param extra The size to be added.
 * @param max The number to compare the buffer size with.
 * @return The reallocated buffer.
 */
char *handle_realloc(para *args, char *buffer, int *buffer_size, int extra, int max)
{
if (*buffer_size <= max)
{
buffer = _realloc(buffer, *buffer_size, *buffer_size + extra);

if (buffer == NULL)
{
free_exit(args);
}

*buffer_size += extra;
}

return buffer;
}
