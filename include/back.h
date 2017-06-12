/*
** back.h for back in /home/benjamin.g/delivery/PSU_2016_back/include
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 19:10:31 2017 Benjamin GAYMAY
** Last update Sat May 20 18:42:16 2017 Benjamin GAYMAY
*/

#ifndef BACK_H_
# define BACK_H_

void	delete_alias(char **, char *);
void	replace_line(char **, int, char *);

int	my_ps1();
int	my_dup(int);
int	nb_op(char **);
int	is_path(char *);
int	change_ps1(char *);
int	disp_builtins();
int	my_echo(char **);
int	nb_pipe(char **);
int	count_builtins();
int	add_alias(char **);
int	check_is_dir(char *);
int	remove_alias(char **);
int	get_builtins_nb(char *);
int	clear_tab(char **, int);
int	my_cd(char **, char **);
int	is_alias(char *, char *);
int	parent(char **, char **);
int	my_where(char **, char **);
int	my_which(char **, char **);
int	get_redirect_error(char *);
int	is_redir(char **, int*, int);
int	change_var(char **, int, int);
int	start_mysh(char **, int, int);
int	my_unsetenv(char **, char **);
int	my_putstr_failure(char *, int);
int	check_redirect(char **, int *);
int	exec_cd(char **, char **, int *);
int	exec_set(char **, char **, int *);
int	exec_ps1(char **, char **, int *);
int	my_setenv(char **, char *, char *);
int	exec_echo(char **, char **, int *);
int	exec_unset(char **, char **, int *);
int	exec_built(char **, char **, int *);
int	exec_alias(char **, char **, int *);
int	exec_where(char **, char **, int *);
int	exec_which(char **, char **, int *);
int	exec_repeat(char **, char **, int *);
int	exec_setenv(char **, char **, int *);
int	exec_unalias(char **, char **, int *);
int	exec_op(char **, char **, int, int *);
int	exec_unsetenv(char **, char **, int *);
int	exec_pipe(char **, char **, int, int *);
int	check_exit(char **, char **, int, int*);
int	treat_cmd(char *, int *, char **, int *);
int	check_pipe_redir(char **, int *, int, int);
int	check_my_tab(char **, char **, int, int *);
int	exec_final_command(char **, char **, int *);
int	put_newtab(char **, char **, char *, char *);
int	check_nb_redirect(char **, char *, char *, int);

char	child(char **, char *, char **);

char	*delete_str(char *, char);
char	*super_str(char *, int, int);
char	*check_command(char *);
char	*find_home(char **);
char	*my_ps2(int, char *);
char	*my_add_slash(char *);
char	*find_oldpwd(char **);
char	*get_oldpwd(int, char *);
char	*clear_str(char *, char);
char	*give_ret_value(int, int);
char	*get_alias_line(char **, char *);
char	*transform_char(char *, char, char);
char	*get_short_cmd(int *, char *, char);
char	*get_great_var(char **, char **, char *);

char	**my_inhib(char **);
char	**ascii_order(char **);
char	**create_path(char **);
char	**concat_quote(char **);
char	**get_cmd(char *, char);
char	**get_alias(int, char **);
char	**my_get_env(int, char **);
char	**realloc_var(char **, int);
char	**get_var_tab(int, char **);
char	**put_alias(char **, char **);
char	**delete_line(char **, char *);
char	**copy_first_op(char **);
char	**copy_op_tab(char **, char *, char *);

#endif /* !BACK_H_ */
