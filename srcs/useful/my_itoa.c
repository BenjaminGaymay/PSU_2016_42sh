/*
** my_itoa.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh/srcs
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue May  9 12:56:02 2017 Benjamin GAYMAY
** Last update Tue May  9 13:04:48 2017 Benjamin GAYMAY
*/

#include <stdlib.h>

char	*my_itoa(int nb)
{
  char	*s;
  int	i;
  int	tmp;

  tmp = nb;
  i = 1;
  while ((tmp /= 10) > 0)
    ++i;
  if ((s = malloc(sizeof(char) * (i + 1))) == NULL)
    return (NULL);
  s[i] = '\0';
  while (i--)
    {
      s[i] = nb % 10 + '0';
      nb /= 10;
    }
  return (s);
}
