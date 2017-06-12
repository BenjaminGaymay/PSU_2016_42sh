/*
** exit.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2/back
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed Mar 22 10:27:54 2017 Benjamin GAYMAY
** Last update Sat May 20 18:58:27 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"

static void	check_exit_error(char *str)
{
  if (str[0] == '-')
    my_fprintf("exit: Badly formed number.\n");
  else if (str[0] >= '0' && str[0] <= '9')
    my_fprintf("exit: Badly formed number.\n");
  else
    my_fprintf("exit: Expression Syntax.\n");
}

int		my_exit(char **tab)
{
  if (tab[1] == NULL)
    return (SUCCESS);
  else if (tab[1] != NULL && tab[2] == NULL)
    {
      if (my_str_isnum(tab[1]) == 1)
	return (SUCCESS);
      else
	check_exit_error(tab[1]);
    }
  else
    my_fprintf("exit: Expression Syntax.\n");
  return (FAILURE);
}
