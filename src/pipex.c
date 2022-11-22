
#include "../includes/pipex.h"

void	child_process_1(int f1, char *cmd, t_data *data, char **envp)
{
    // printf("%s\n", cmd);
    dup2(f1, 0);
	close(f1);
    dup2(data->pipeline[1], 1);
	// printf("It enter here\n");
    close(data->pipeline[1]);
	printf("exec child\n");
    if (execve(data->cmd[0], (char * const*)cmd, envp) < -1)
	{
		ft_putstr_fd("Error:", 2);
		exit (1);
	}
}

// void	parent_process(int f2, char *cmd, t_data *data, char **envp)
// {
// 	dup2(f2, STDOUT_FILENO);
// 	dup2(data->pipeline[0], STDIN_FILENO);
// 	close(data->pipeline[1]);
// 	// close(f2);
// 	printf("exec parant\n");
// 	if (execve(data->cmd[1], (char * const*)cmd, envp) < -1)
// 	{
// 		ft_putstr_fd("Error:", 2);
// 		exit (1);
// 	}
// }

void	child_process_2(int f2, char *cmd, t_data *data, char **envp)
{
	dup2(f2, 1);
	close(f2);
	dup2(data->pipeline[0], 0);
	close(data->pipeline[0]);
	close(data->pipeline[1]);
	// close(f2);
	// printf("exec parant\n");
	if (execve(data->cmd[1], (char * const*)cmd, envp) < -1)
	{
		ft_putstr_fd("Error:", 2);
		exit (1);
	}
}

void	pipex(int f1, int f2, char **argv, t_data *data, char **envp)
{
	int		status;
    pid_t   children[data->ncmd];

    if (pipe(data->pipeline) < 0)
        ft_putstr_fd("Error: Error Creating The Interprocess Communications Pipe\n", 2);
    children[0] = fork();
    if (children[0]  < 0)
        return (perror("Fork: "));
    if (children[0] == 0)
    {
        printf("in the child process 1\n");
        child_process_1(f1, argv[2], data, envp);
    }
	children[1] = fork();
	if (children[1] < 0)
		return (perror("Fork: "));
	if (children[1] == 0)
    {
        printf("in the child process 2\n");
        child_process_2(f2, argv[3], data, envp);
    }
	waitpid(children[0], 0, 0);
	waitpid(children[1], 0, 0);
    // else
    // {
	// 	waitpid(-1, &status, 0);
    //     printf("in the parent process\n");
    //     parent_process(f2, argv[3], data, envp);
    // }

    
}

int error_checking(int argc, char **argv)
{
    if (argc < 5)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (-1);
    }
    if (access(argv[1], F_OK && R_OK && X_OK) != 0)
    {
        ft_putstr_fd("Error: No such file\n", 2);
        return (-1);
    }
    return (0);
}

void    init_data(int argc, char **argv, char **envp, t_data *data)
{
    data->ncmd = argc - 3;
    split_path(data, argc, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    int     f1;
    int     f2;
    t_data  data;

    if (error_checking(argc, argv) != 0)
        return (-1);
    init_data(argc, argv, envp, &data);
    f1 = open(argv[1], O_RDONLY, 0666);
    f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (f1 < 0 || f2 < 0)
        return (-1);
    pipex(f1, f2, argv, &data, envp);
    free_semua(&data, f1, f2);
    return (0);
}

//Makefile (done)
//error handling (done)
//child process -> execve -> parent process