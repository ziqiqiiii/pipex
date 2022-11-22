
#include "../includes/pipex.h"

char	*split_argv(t_data *data, char *argv)
{
	char	**split;
	char	*cmd;
	int		i;

	split = ft_split(argv, ' ');
	cmd = ft_strdup(split[0]);
	free_twod(split);
	return (cmd);
}

char	*exist_or_not(t_data *data, char *argv)
{
	char	*cmd;
	char	*join;
	int		i;

	cmd = split_argv(data, argv);
	i = -1;
	while (data->envp[++i])
	{
		join = ft_strjoin(data->envp[i], cmd);
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

void	check_path(t_data *data, int argc, char **argv)
{
	int		i;
	int		a;
	char	**cmd;
	char	*join;

	cmd = ft_calloc(data->ncmd + 1, sizeof(char *));
	i = 1;
	a = -1;
	while (++i < argc -1)
	{
		join = exist_or_not(data, argv[i]);
		if (join == NULL)
		{
			free (join);
			free_twod(cmd);
			free_twod(data->envp);
			ft_putstr_fd("Error :command doesn't exist\n", 2);
			exit (1);
		}
		cmd[++a] = join;
	}
	a = -1;
	cmd[data->ncmd] = NULL;
	data->path = cmd;
}

void	split_path(t_data *data, int argc, char **argv, char **envp)
{
	int		i;
	char	*temp;
	char	*path;
	char	**split;

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
	}
	data->envp = split;
	check_path(data, argc, argv);
}
