/*
** main.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2/back
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 18:54:05 2017 Benjamin GAYMAY
** Last update	Thu Jun 01 17:24:00 2017 Full Name
*/

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "minishell2.h"
#include "get_next_line.h"

static void	my_ctrl_c()
{
  if (isatty(0) == 1)
    {
      my_putchar('\n');
      pwd_prompt();
    }
}

static int	exec_42shrc(char **envp)
{
  int		fd;
  int		tmp;
  char		*cmd;

  tmp = 0;
  if ((fd = open(".42shrc", O_RDONLY)) == FD_ERROR)
    return (FD_ERROR);
  while ((cmd = get_next_line(fd)))
    {
      if (cmd[0] != '#')
	treat_cmd(cmd, &tmp, envp, &tmp);
      free(cmd);
    }
  close(fd);
  return (SUCCESS);
}

static int	load_sh(char **envp)
{
  char		**new_envp;
  char		**alias;
  int		ret;

  signal(2, my_ctrl_c);
  if ((new_envp = copy_array(envp)) == NULL)
    return (ERROR);
  if ((alias = malloc(sizeof(*alias))) == NULL)
    return (ERROR);
  alias[0] = NULL;
  get_alias(SAVE, alias);
  my_get_env(SAVE, new_envp);
  give_ret_value(SAVE, 0);
  get_var_tab(SAVE, realloc_var(NULL, 1));
  exec_42shrc(new_envp);
  ret = start_mysh(new_envp, SUCCESS, CONTINUE);
  new_envp = my_get_env(GET, NULL);
  free_array(new_envp);
  free_array(get_alias(GET, NULL));
  free_array(get_var_tab(GET, NULL));
  free(get_oldpwd(GET, NULL));
  my_ps2(FREE, NULL);
  return (ret);
}

int		main(const int ac, const char **av, char **envp)
{
  (void)ac;
  (void)av;
  return (load_sh(envp));
}
