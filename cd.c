#include "all.h"

/**
 * @brief Change directory.
 *
 * This function changes the current working directory.
 *
 * @param args Parameter of type para p1.
 * @return 0 if successful, 1 otherwise.
 */
int cd(para *args)
{
    char *dest, *line = args->line;

    // Check if the command is "cd"
    if (!_strcmp(line, "cd"))
    {
        // If no arguments are provided, change to home directory
        if (args->n_token == 1)
            dest = _get_env(args->envp, "HOME", 4);
        else
        {
            line += 3;

            // If the argument is "-", change to the previous directory
            if (!_strcmp(line, "-"))
            {
                dest = args->old_pwd;
                write(1, dest, _strlen(dest));
                write(1, "\n", 1);
            }
            else
                dest = line;
        }

        // Change directory and handle errors
        if (chdir(dest) == -1)
        {
            _printf("%s: %i: cd: can't cd to %s\n", args->shell_name, args->count, dest);
            args->status = 2;
        }
        else
        {
            // Update old_pwd and PWD
            free(args->old_pwd);
            args->old_pwd = _strdup(args, &((*(args->pwd))[4]));
            if (!args->old_pwd)
                free_exit(args);

            change_pwd(args);
            args->status = 0;
        }

        return 1;
    }

    return 0;
}

/**
 * @brief Change the current working directory.
 *
 * This function updates the PWD environment variable.
 *
 * @param args Parameter of type para p1.
 */
void change_pwd(para *args)
{
    char buffer[250];
    char *pwd = _malloc(args, 256);

    // Get the current working directory
    getcwd(buffer, 250);

    pwd[0] = '\0';
    _strcat(pwd, "PWD=");
    _strcat(pwd, buffer);

    // Update the PWD environment variable
    free(*(args->pwd));
    *(args->pwd) = pwd;
}

/**
 * @brief Get the PWD from the environment variables.
 *
 * This function retrieves the PWD from the environment variables.
 *
 * @param args Parameter of type para p1.
 * @return Pointer to the PWD.
 */
char **get_PWD(para *args)
{
    int i;
    char *pwd = NULL;

    // Search for the PWD environment variable
    for (i = 0; args->envp[i] != NULL; i++)
    {
        if (_strncmp(args->envp[i], "PWD", 3) == 0)
        {
            // Duplicate and return the PWD
            pwd = _strdup(args, args->envp[i]);
            args->envp[i] = pwd;
            return &(args->envp[i]);
        }
    }

    return NULL;
}

/**
 * @brief Free allocated resources before exiting.
 *
 * This function frees allocated resources before exiting the program.
 *
 * @param args Parameter of type para p1.
 */
void free_exit(para *args)
{
    if (args->line)
        free(args->line);
    if (args->path)
        free(args->path);
    if (args->pwd)
        free(*(args->pwd));
    if (args->old_pwd)
        free(args->old_pwd);

    exit(255);
}

/**
 * @brief Allocate memory and handle malloc errors.
 *
 * This function handles memory allocation using malloc and exits if allocation fails.
 *
 * @param args Parameter of type para p1.
 * @param size The size to be allocated.
 * @return The allocated buffer.
 */
char *_malloc(para *args, int size)
{
    char *buff = malloc(size);

    // Handle memory allocation failure
    if (!buff)
        free_exit(args);

    return buff;
}

