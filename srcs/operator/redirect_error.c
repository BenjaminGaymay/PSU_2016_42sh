/*
** redirect_error.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue May 16 11:48:38 2017 Benjamin GAYMAY
** Last update Sat May 20 19:12:33 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "back.h"
#include "macro.h"
#include "use_array.h"

int		check_redirect_error(char **tab)
{
  if (check_nb_redirect(tab, ">", ">>", 0) != SUCCESS ||
      check_nb_redirect(tab, "<", "<<", 0) != SUCCESS)
    return (FAILURE);
  return (SUCCESS);
}

int		get_redirect_error(char *command)
{
  char		**tab;
  int		ret;

  ret = 0;
  while ((tab = get_cmd(command, ';')) != NULL)
    {
      if (ret != FAILURE && check_redirect_error(tab) == FAILURE)
	ret = FAILURE;
      free_array(tab);
    }
  return (ret);
}
