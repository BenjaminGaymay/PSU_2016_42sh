/*
** my_malloc_strcpy.c for my_malloc_strcpy in /home/benjamin.g/save/Create/library
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Thu Jan 19 18:13:18 2017 Benjamin GAYMAY
** Last update Wed May 10 11:44:44 2017 Benjamin GAYMAY
*/

#include <stdlib.h>

char	*my_malloc_strncpy(char *s2, const int n)
{
  int	i;
  char	*s1;

  if ((s1 = malloc(sizeof(char) * (n + 1))) == NULL)
    return (NULL);
  i = 0;
  while (s2[i] != '\0' && i != n)
    {
      s1[i] = s2[i];
      ++i;
    }
  s1[i] = '\0';
  return (s1);
}
