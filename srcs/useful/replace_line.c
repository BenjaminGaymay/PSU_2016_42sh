/*
** replace_line.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Thu May 11 11:13:42 2017 Benjamin GAYMAY
** Last update Thu May 11 11:14:51 2017 Benjamin GAYMAY
*/

#include <stdlib.h>

void	replace_line(char **tab, int i, char *line)
{
  free(tab[i]);
  tab[i] = line;
}
