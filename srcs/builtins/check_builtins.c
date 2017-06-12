/*
** check_builtins.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sun May 14 17:03:27 2017 Benjamin GAYMAY
** Last update Sat May 20 18:54:55 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "macro.h"
#include "builtins.h"
#include "my_printf.h"

int		count_builtins()
{
  int		i;

  i = 0;
  while (builtins[i])
    ++i;
  return (i);
}

int		is_builtin(char *cmd, int type)
{
  int		i;

  i = 0;
  while (builtins[i])
    {
      if (my_strcmp(cmd, builtins[i]) == SAME)
	{
	  if (type == WHERE)
	    my_printf("%s is a shell built-in\n", builtins[i]);
	  else if (type == WHICH)
	    my_printf("%s: shell built-in command.\n", cmd);
	  return (SUCCESS);
	}
      ++i;
    }
  return (FAILURE);
}

int		disp_builtins()
{
  int		i;

  i = 0;
  while (builtins[i])
    {
      my_printf("%s\t", builtins[i]);
      ++i;
    }
  my_printf("\n");
  return (SUCCESS);
}

int		get_builtins_nb(char *command)
{
  int		nb_builtins;
  int		i;

  nb_builtins = count_builtins();
  i = 0;
  while (i != nb_builtins && my_strcmp(command, builtins[i]) != SAME)
    ++i;
  return (i);
}
