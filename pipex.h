#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "./libft/libft.h"

typedef struct sdata
{
    int     npipe;
    char    **path;
}   t_data;

#endif