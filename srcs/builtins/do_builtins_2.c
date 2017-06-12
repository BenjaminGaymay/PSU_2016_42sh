/*
** do_builtins_2.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sun May 14 17:38:14 2017 Benjamin GAYMAY
** Last update Sat May 20 18:56:37 2017 Benjamin GAYMAY
*/

#include "back.h"
#include "macro.h"

int		exec_unsetenv(char **envp, char **tab, int *ret)
{
  (void)envp;
  *ret = my_unsetenv(envp, tab);
  return (SUCCESS);
}

int		exec_where(char **envp, char **tab, int *ret)
{
  if ((*ret = my_where(tab, envp)) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

int		exec_which(char **envp, char **tab, int *ret)
{
  if ((*ret = my_which(tab, envp)) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

int		exec_built(char **envp, char **tab, int *ret)
{
  (void)envp;
  (void)tab;
  disp_builtins();
  return (*ret = SUCCESS);
}

int		exec_ps1(char **envp, char **tab, int *ret)
{
  (void)envp;
  (void)tab;
  if ((*ret = (change_ps1(tab[1]))) == ERROR)
    return (ERROR);
  return (SUCCESS);
}
