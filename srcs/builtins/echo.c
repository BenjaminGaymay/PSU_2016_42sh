/*
** echo.c for  in /home/Sola/delivery/PSU_2016_42sh/back
**
** Made by Erwann LeLetty
** Login   <Sola@epitech.net>
**
** Started on  Wed Apr 19 10:47:55 2017 Erwann LeLetty
** Last update Sat May 20 18:58:17 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include "my.h"
#include "macro.h"
#include "my_printf.h"
#include "minishell2.h"

static void	my_print_echo_s(char **tab, int cmt)
{
  while (tab[++cmt] != NULL)
    my_printf(tab[cmt + 1] == NULL ? "%s" : "%s ", tab[cmt]);
}

int		my_echo(char **tab)
{
  if (tab[1] == NULL)
    my_putchar('\n');
  else if (my_strcmp(tab[1], "-n") == SAME)
    my_print_echo_s(tab, 1);
  else
    {
      my_print_echo_s(tab, 0);
      my_putchar('\n');
    }
  return (SUCCESS);
}
