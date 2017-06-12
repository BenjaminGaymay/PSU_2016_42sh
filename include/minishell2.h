/*
** minishell2.h for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2/include
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 19:10:31 2017 Benjamin GAYMAY
** Last update Wed May 17 11:59:32 2017 benoit pingris
*/

#ifndef MINISHELL2_H_
# define MINISHELL2_H_

void	*my_calloc(int, int);
void	*my_memset(void *, int, int, int);
int	my_exit(char **);
int	put_error(int, char *);
int	father(char *, char **);
char	*prompt(int *);
int	pwd_prompt();

#endif /* !MINISHELL2_H_ */
