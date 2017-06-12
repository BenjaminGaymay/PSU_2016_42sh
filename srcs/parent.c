/*
** parent.c<PSU_2016_minishell2> for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Fri Mar 24 10:24:34 2017 Benjamin GAYMAY
** Last update Sat May 20 19:13:49 2017 Benjamin GAYMAY
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "my_printf.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"

static char	*free_return(char *command, char **path)
{
  free(command);
  free_array(path);
  return (NULL);
}

static char	*check_access(char *command, char **tab, char **path)
{
  if (access(command, F_OK) != 0)
    {
      my_fprintf("%s: Command not found.\n", tab[0]);
      return (free_return(command, path));
    }
  else if (tab[0][0] != '\0' &&
	   (access(command, X_OK) != 0 || check_is_dir(command) == SUCCESS))
    {
      my_fprintf("%s: Permission denied.\n", tab[0]);
      return (free_return(command, path));
    }
  if ((access(command, F_OK) != 0) || (access(command, X_OK) != 0))
    return (free_return(command, path));
  return (command);
}

static char	*search_path(char **path, char **tab)
{
  char		*command;
  int		i;

  i = 1;
  command = my_malloc_strcpy(tab[0]);
  if (my_strncmp(tab[0], "./", 2) != SAME &&
      my_strncmp(tab[0], "../", 3) != SAME &&
      my_strncmp(tab[0], "/", 1) != SAME &&
      is_path(tab[0]) == FAILURE)
    {
      free(command);
      command = (my_strcmp(path[0], "//") != SAME) ?
	my_malloc_strcat(path[0], tab[0]) : strdup(tab[0]);
      while (access(command, F_OK) != 0 && path[i] != NULL)
	{
	  free(command);
	  command = (my_strcmp(path[i], "//") != SAME) ?
	    my_malloc_strcat(path[i], tab[0]) : strdup(tab[0]);
	  ++i;
	}
    }
  return (check_access(command, tab, path));
}

int		parent(char **envp, char **tab)
{
  pid_t		pid;
  char		**path;
  char		*command;

  if (my_strcmp(tab[0], "\0") == SAME)
    return (SUCCESS);
  path = create_path(envp);
  if ((command = search_path(path, tab)) == NULL)
    return (FAILURE);
  free_array(path);
  if ((pid = fork()) == FD_ERROR)
    return (ERROR);
  if (pid != CHILD)
    return (father(command, tab));
  else
    return (child(envp, command, tab));
}
