/*
** my_strcmp.c for my_strcmp in /home/benjamin.g/delivery/CPool_Day06
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Mon Oct 10 17:22:02 2016 Benjamin GAYMAY
** Last update Wed May 10 11:46:03 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"

#define ERROR -1

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (s1 == NULL || s2 == NULL)
    return (ERROR);
  while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
    ++i;
  return (s1[i] - s2[i]);
}
