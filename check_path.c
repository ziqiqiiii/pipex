
#include "./pipex.h"

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
            split = ft_split(path, ':');
            data->path = split;
            while (*split)
            {
                // temp = *split;
                // split++;
                // free(temp);
            }
            // free(split);
            free(path);
        }
    }

}