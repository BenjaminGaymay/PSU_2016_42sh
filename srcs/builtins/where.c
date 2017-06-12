/*
** where.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh/srcs/where
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Fri May 12 15:23:36 2017 benoit pingris
** Last update Sat May 20 19:01:11 2017 Benjamin GAYMAY
*/

#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "my_printf.h"
#include "use_array.h"

int		is_alias(char *cmd, char *msg)
{
  char			**alias;
  char			*connection;

  alias = get_alias(GET, NULL);
  if ((connection = get_alias_line(alias, cmd)) != NULL)
    {
      my_printf("%s%s %s\n", cmd, msg, connection);
      return (SUCCESS);
    }
  return (FAILURE);
}

static int	look_in_path(char *cmd, char **path)
{
  DIR		*dir;
  struct dirent	*file;
  int		i;
  int		ret;

  ret = FAILURE;
  i = 0;
  while (path[i])
    {
      if ((dir = opendir(path[i])) == NULL)
	return (ret);
      while ((file = readdir(dir)) != NULL)
	{
	  if (my_strcmp(cmd, file->d_name) == 0)
	    {
	      my_printf("%s%s\n", path[i], file->d_name);
	      ret = SUCCESS;
	    }
	}
      closedir(dir);
      ++i;
    }
  return (ret);
}

int		my_where(char **cmd, char **envp)
{
  char		**path;
  int		ret;
  int		i;
  int		var;

  i = 1;
  ret = SUCCESS;
  if (cmd[1] == NULL)
    return (my_putstr_failure("where: Too few arguments.\n", FAILURE));
  if ((path = create_path(envp)) == NULL)
    return (ERROR);
  while (cmd[i])
    {
      var = 0;
      var += is_alias(cmd[i], " is aliased to");
      var += is_builtin(cmd[i], WHERE);
      var += look_in_path(cmd[i], path);
      if (var == 3)
	ret = FAILURE;
      ++i;
    }
  free_array(path);
  return (ret);
}
