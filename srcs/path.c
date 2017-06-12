/*
** path.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed Mar 22 14:03:34 2017 Benjamin GAYMAY
** Last update	Thu Jun 01 15:00:47 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "back.h"
#include "macro.h"
#include "my.h"
#include "my_fprintf.h"
#include "use_array.h"

char	*find_path(char **envp)
{
  int	i;
  char	*path;

  i = 0;
  while (envp[i] != NULL)
    {
      if (my_strncmp(envp[i], "PATH=", 5) == SAME)
	return (strdup(&envp[i][5]));
      i++;
    }
  i = confstr(_CS_PATH, NULL, 0);
  if ((path = malloc(i)) == NULL)
    return (NULL);
  confstr(_CS_PATH, path, i);
  return (path);
}

char	**create_path(char **envp)
{
  int	i;
  char	*str;
  char	**path;

  if ((str = find_path(envp)) == NULL)
    return (NULL);
  if ((path = create_array(str, ':')) == NULL)
    return (NULL);
  i = 0;
  while (path[i] != NULL)
    {
      if ((path[i] = my_add_slash(path[i])) == NULL)
	return (NULL);
      ++i;
    }
  return (path);
}

char	*find_home(char **envp)
{
  int	i;

  i = 0;
  while (envp[i] != NULL)
    {
      if (my_strncmp(envp[i], "HOME=", 5) == SAME)
	return (&envp[i][5]);
      i++;
    }
  my_fprintf("cd: No home directory.\n");
  return (NULL);
}
