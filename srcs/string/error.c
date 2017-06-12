/*
** error.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh/srcs/builtins
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue May  9 11:14:12 2017 Benjamin GAYMAY
** Last update Sat May 20 19:17:15 2017 Benjamin GAYMAY
*/

#include "my_fprintf.h"

int		my_putstr_failure(char *str, int ret)
{
  my_fprintf(str);
  return (ret);
}
