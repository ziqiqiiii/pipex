#include "./pipex.h"

void child_process(int f1, char *cmd)
{

}

void pipex(int f1, int f2, char **argv, t_data *data)
{
    int     pipe_line[2];
    pid_t   children[data->npipe];
    int     status;

    pipe(pipe_line);
    children[0] = fork();
    if (children[0]  < 0)
        return (perror("Fork: "));
    if (!children[0])
    {
        // child_process(f1, argv[2]);
        printf("in the child process\n");
    }
    else
    {
        waitpid(-1, &status, 0);
        printf("in the parent process\n");
        // parent_process(f2, argv[3]);
    }

    
}

void    check_path(t_data *data, char **envp)
{
    int     i;
    char    *loop;
    char    *path;
    char    **split;
    char    *temp;
    
    i = -1;
    while (envp[++i])
    {
        loop = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
        if (loop != NULL)
        {
            path = ft_substr(loop, 5, ft_strlen(loop));
            // printf("%s\n", path);
            split = ft_split(path, ':');
            data->path = split;
            while (*split)
            {
                printf("%s\n", *split);
                split++;
                temp = *split;
                split++;
                free(temp);
            }
            // free(split);
            free(path);
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    int     f1;
    int     f2;
    t_data  data;

    if (argc < 0)
        return (-1);
    check_path(&data, envp);
    // data.npipe = argc - 3;
    // f1 = open(argv[1], O_RDONLY);
    // f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    // if (f1 < 0 || f2 < 0)
    //     return (-1);
    // pipex(f1, f2, argv, &data);
    return (0);
}

//Makefile 
//error handling
//child process