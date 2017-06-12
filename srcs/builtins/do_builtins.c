/*
** do_builtins.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sun May 14 17:37:05 2017 Benjamin GAYMAY
** Last update Sat May 20 18:57:51 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include <unistd.h>
#include "back.h"
#include "use_array.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"

int		exec_alias(char **envp, char **tab, int *ret)
{
  (void)envp;
  if ((*ret = add_alias(tab)) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

int		exec_cd(char **envp, char **tab, int *ret)
{
  char		*pwd;

  pwd = NULL;
  pwd = getcwd(pwd, 0);
  if ((*ret = my_cd(envp, tab)) == SUCCESS)
    get_oldpwd(SAVE, pwd);
  else
    free(pwd);
  return (SUCCESS);
}

int		exec_echo(char **envp, char **tab, int *ret)
{
  (void)envp;
  *ret = my_echo(tab);
  return (SUCCESS);
}

int		exec_setenv(char **envp, char **tab, int *ret)
{
  *ret = FAILURE;
  if (tab[1] == NULL)
    *ret = my_showtab(envp);
  else if (tab[2] != NULL && tab[3] != NULL)
    my_fprintf("setenv: Too many arguments.\n");
  else
    if ((*ret = my_setenv(envp, tab[1], tab[2])) == ERROR)
      return (ERROR);
  return (SUCCESS);
}

int		exec_unalias(char **envp, char **tab, int *ret)
{
  (void)envp;
  *ret = remove_alias(tab);
  return (SUCCESS);
}
