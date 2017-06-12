/*
** my_strlen.c for my_strlen in /home/benjamin.g/delivery/CPool_Day04
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Thu Oct  6 16:36:00 2016 Benjamin GAYMAY
** Last update Wed May 10 11:52:03 2017 Benjamin GAYMAY
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0')
    ++i;
  return (i);
}
