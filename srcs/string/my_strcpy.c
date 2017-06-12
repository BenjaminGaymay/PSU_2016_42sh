/*
** my_strcpy.c for my_strcpy in /home/benjamin.g/delivery/CPool_Day06
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Mon Oct 10 09:09:10 2016 Benjamin GAYMAY
** Last update Wed May 10 11:46:32 2017 Benjamin GAYMAY
*/

#include "my.h"

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  if (my_strlen(dest) > my_strlen(src))
    dest[i] = '\0';
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      ++i;
    }
  return (dest);
}
