/*
** my_strncat.c for my_strncat in /home/benjamin.g/delivery/CPool_Day07/lib/my
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Oct 11 13:36:58 2016 Benjamin GAYMAY
** Last update Wed May 10 11:49:24 2017 Benjamin GAYMAY
*/

#include <stdlib.h>

char	*my_strncat(char *dest, char *src, const int nb)
{
  int	i;
  int	f;

  i = 0;
  f = 0;
  if (dest == NULL || src == NULL)
    return (NULL);
  while (dest[i] != '\0')
    i++;
  while (f != nb)
    {
      dest[i] = src[f];
      i++;
      f++;
    }
  dest[i] = '\0';
  return (dest);
}
