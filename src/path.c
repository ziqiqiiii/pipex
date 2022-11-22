
#include "../includes/pipex.h"

void    free_2D(char **twod)
{
    char    *temp;
    int     a;

    a = -1;
    while(twod[++a])
    {
        temp = twod[a];
        free(temp);
    }
    free(twod);

}

char    *split_argv(char *argv)
{
    char    **split;
    char    *cmd;

    split = ft_split(argv, ' ');
    cmd = ft_strdup(split[0]);
    free_2D(split);
    return (cmd);   
}

char    *exist_or_not(t_data *data, char *argv)
{
    char    *cmd;
    char    *join;
    int     i;

    cmd = split_argv(argv);
    i = -1;
    while (data->path[++i])
    {
        join = ft_strjoin(data->path[i], cmd);
        // printf(" %i %s\n", i ,join);
        if (access(join, F_OK) == 0)
        {
            free (cmd);
            return (join);
        }
        free (join);
    }
    free (cmd);
    return (NULL);

}

// void    check_path(t_data *data, int argc, char **argv)
// {
//     int     i;
//     int     j;
//     int     a;
//     char    *join;
//     char    *split;
//     char    **cmd;

//     cmd = ft_calloc(data->ncmd + 1, sizeof(char *));
//     j = 1;
//     a = -1;
//     while(++j < argc - 1)
//     {
//         i = -1;
//         while (data->path[++i])
//         {
//             split = split_argv(argv[j]);
//             join = ft_strjoin(data->path[i], split);
//             printf("join = [%s]\n", join);
//             if (access(join, F_OK) == 0)
//             {
//                 cmd[++a] = join;
//                 break ;
//             }
//             free(join);
//             free(split);
//         }
//         printf("%i\n", i);
//         free(split);
//         printf("\nafter break here\n\n");
//         if (cmd[0] == 0)
//         {
//             printf("it enter here");
//             free_2D(cmd);
//             ft_putstr_fd("Error: No such command\n", 2);
//             exit (1);
//         }
//     }
//     cmd[data->ncmd] = '\0';
//     data->cmd = cmd;
// }

void    check_path(t_data *data, int argc, char **argv)
{
    int     i;
    int     a;
    char    **cmd;
    char    *join;

    cmd = ft_calloc(data->ncmd + 1, sizeof(char *));
    i = 1;
    a = -1;
    while (++i < argc -1)
    {
        join = exist_or_not(data, argv[i]);
        // printf("%s\n", join);
        if (join == NULL)
        {
            free (join);
            free_2D(cmd);
            free_2D(data->path);
            ft_putstr_fd("Error :command doesn't exist\n", 2);
            exit (1);
        }
        cmd[++a] = join;
    }
    // printf("%i\n", data->ncmd);
    cmd[data->ncmd] = '\0';
    a = -1;
    while(cmd[++a])
        printf("%s\n", cmd[a]);
    // a = -1;
    // while (cmd[++a])
    // {
    //     printf("%s\n", cmd[a]);
    //     printf("heheheh\n");
    // }
    data->cmd = cmd;
}

void    split_path(t_data *data, int argc, char **argv, char **envp)
{
    int     i;
    char    *temp;
    char    *path;
    char    **split;
    
    
    i = -1;
    while (envp[++i])
    {
        path = ft_strnstr(envp[i], "PATH=", 5);
        if (path != NULL)
        {
            path = ft_substr(path, 5, ft_strlen(path));
            split = ft_split(path, ':');
            free(path);
            break ;
        }
    }
    if (path == NULL)
    {
        ft_putstr_fd("Wtf why you unset PATH\n", 2);
        exit (1);
    }
    i = -1;
    while (split[++i])
    {
        temp = ft_strjoin(split[i], "/");
        free(split[i]);
        split[i] = temp;
        // printf("%i path %s\n", i ,split[i]);
    }
    data->path = split;
    check_path(data, argc, argv);
}

void    free_semua(t_data *data, int f1, int f2)
{
   free_2D(data->path);
   free_2D(data->cmd);
   close(data->pipeline[0]);
   close(data->pipeline[1]);
//    close(f1);
   close(f2);
}