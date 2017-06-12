/*
** operator_basics.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Thu May 11 12:22:21 2017 Benjamin GAYMAY
** Last update Sat May 20 19:06:47 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "minishell2.h"

int		nb_op(char **tab)
{
  int		i;
  int		nb;

  i = -1;
  nb = 0;
  while (tab[++i] != NULL)
    {
      if (my_strcmp(tab[i], "|") == SUCCESS ||
	  my_strcmp(tab[i], "||") == SUCCESS)
	{
	  if (tab[i + 1] == NULL || NEXT_IS_PIPE(tab[i + 1]) == SUCCESS ||
	      (i == 0) || my_strcmp(tab[i + 1], "&&") == SAME)
	    return (PIPE_ERROR);
	  ++nb;
	}
      else if (my_strcmp(tab[i], "&&") == SUCCESS && tab[i + 1] != NULL &&
	       NEXT_IS_PIPE(tab[i + 1]) == SUCCESS)
	return (PIPE_ERROR);
      else if (my_strcmp(tab[i], "&&") == SUCCESS)
	++nb;
    }
  return (nb);
}

char		**copy_op_tab(char **tab, char *sep1, char *sep2)
{
  int		i;
  char		**new;

  i = -1;
  while (tab[++i] != NULL && my_strcmp(tab[i], sep1) != SAME &&
	 my_strcmp(tab[i], sep2) != SAME)
    ;
  if ((new = my_calloc(i + 1, sizeof(char *))) == NULL)
    return (NULL);
  i =  -1;
  while (tab[++i] != NULL && my_strcmp(tab[i], sep1) != SAME &&
	 my_strcmp(tab[i], sep2) != SAME)
    new[i] = tab[i];
  new[i] = NULL;
  return (new);
}

char		**copy_first_op(char **tab)
{
  int		i;
  char		**new;

  i = -1;
  while (tab[++i] != NULL && my_strcmp(tab[i], "|") != SAME &&
	 my_strcmp(tab[i], "||") != SAME && my_strcmp(tab[i], "&&") != SAME)
    ;
  if ((new = my_calloc(i + 1, sizeof(char *))) == NULL)
    return (NULL);
  i =  -1;
  while (tab[++i] != NULL && my_strcmp(tab[i], "|") != SAME &&
	 my_strcmp(tab[i], "||") != SAME && my_strcmp(tab[i], "&&") != SAME)
    new[i] = tab[i];
  new[i] = NULL;
  return (new);
}

int		nb_pipe(char **tab)
{
  int		i;
  int		nb;

  i = -1;
  nb = 0;
  while (tab[++i] != NULL &&
	 my_strcmp(tab[i], "&&") != SAME &&
	 my_strcmp(tab[i], "||") != SAME)
    {
      if (my_strcmp(tab[i], "|") == SAME)
	{
	  if (tab[i + 1] == NULL || my_strcmp(tab[i + 1], "|") == SAME)
	    return (-1);
	  ++nb;
	}
      else if (my_strcmp(tab[i], "||") == SAME)
	return (-1);
    }
  return (nb);
}
