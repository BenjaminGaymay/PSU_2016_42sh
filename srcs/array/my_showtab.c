/*
** my_showtab.c for my_showtab in /home/benjamin.g/save/Create/library
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Jan 17 20:56:55 2017 Benjamin GAYMAY
** Last update Sat May 20 18:52:36 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "use_array.h"

char		**ascii_order(char **array)
{
  int		i;
  int		f;
  char		*tmp;

  f = tab_len(array);
  while (f != 0)
    {
      i = 0;
      while (array[i + 1] != NULL)
	{
	  if (my_strcmp(array[i], array[i + 1]) > 0)
	    {
	      tmp = array[i];
	      array[i] = array[i + 1];
	      array[i + 1] = tmp;
	    }
	  ++i;
	}
      --f;
    }
  return (array);
}

int		my_showtab(char **array)
{
  int		i;

  i = 0;
  while (array[i] != NULL)
    {
      my_putstr(array[i]);
      my_putchar('\n');
      ++i;
    }
  return (0);
}
