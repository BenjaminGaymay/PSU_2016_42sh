/*
** which.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Fri May 12 20:50:31 2017 benoit pingris
** Last update Sat May 20 19:01:30 2017 Benjamin GAYMAY
*/

#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "my_printf.h"
#include "use_array.h"

static int	look_in_path(char *cmd, char **path)
{
  DIR		*dir;
  struct dirent	*file;
  int		i;

  i = 0;
  while (path[i])
    {
      if ((dir = opendir(path[i])) == NULL)
	return (FAILURE);
      while ((file = readdir(dir)) != NULL)
	{
	  if (my_strcmp(cmd, file->d_name) == 0)
	    {
	      my_printf("%s%s\n", path[i], file->d_name);
	      closedir(dir);
	      return (SUCCESS);
	    }
	}
      closedir(dir);
      ++i;
    }
  return (FAILURE);
}

int		my_which(char **cmd, char **envp)
{
  char		**path;
  int		i;
  int		ret;

  i = 1;
  ret = SUCCESS;
  if (cmd[1] == NULL)
    return (my_putstr_failure("which: Too few arguments.\n", FAILURE));
  if ((path = create_path(envp)) == NULL)
    return (ERROR);
  while (cmd[i])
    {
      if (is_alias(cmd[i], ":\taliased to") == FAILURE &&
	  is_builtin(cmd[i], WHICH) == FAILURE &&
	  look_in_path(cmd[i], path) == FAILURE)
	{
	  ret = (FAILURE);
	  my_printf("%s: Command not found.\n", cmd[i]);
	}
      ++i;
    }
  free_array(path);
  return (ret);
}
