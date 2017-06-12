/*
** do_builtins_3.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed May 17 10:38:24 2017 Benjamin GAYMAY
** Last update Sat May 20 18:56:58 2017 Benjamin GAYMAY
*/

#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"

int		exec_repeat(char **envp, char **tab, int *ret)
{
  int		nb_rep;

  *ret = FAILURE;
  if (tab_len(tab) < 3)
    return (my_putstr_failure("repeat: Too few arguments.\n", *ret));
  if (my_str_isnum(tab[1]) == 1)
    nb_rep = my_getnbr(tab[1]) + 1;
  else
    return (my_putstr_failure("repeat: Badly formed number.\n", *ret));
  *ret = SUCCESS;
  my_dup(GET);
  while (--nb_rep != 0)
    check_my_tab(envp, copy_array(&tab[2]), -1, ret);
  my_dup(SAVE);
  return (*ret);
}
