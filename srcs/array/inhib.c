/*
** inhib.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Tue May 16 10:48:16 2017 benoit pingris
** Last update Sat May 20 18:52:16 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"

char		*delete_str(char *str, char letter)
{
  int		i;
  int		j;
  char		*new;

  i = 0;
  j = 0;
  if ((new = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  while (i < my_strlen(str))
    {
      while (str[i] != letter && str[i])
	{
	  new[j] = str[i];
	  ++j;
	  ++i;
	}
      ++i;
    }
  new[j] = '\0';
  free(str);
  return (new);
}

char		**my_inhib(char **tab)
{
  int	i;

  i = 0;
  if (tab[0][0] == '\\')
    {
      tab[0][0] = ' ';
      if ((tab[0] = clear_str(tab[0], ' ')) == NULL)
	return (NULL);
    }
  while (tab[i])
    {
      if (my_strstr(tab[i], "\\") != -1)
	if ((tab[i] = delete_str(tab[i], '\\')) == NULL)
	  return (NULL);
      ++i;
    }
  return (tab);
}
