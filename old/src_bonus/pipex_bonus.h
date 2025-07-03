/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:31:58 by llechert          #+#    #+#             */
/*   Updated: 2025/06/18 21:40:21 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

/*main.c*/
int	is_here_doc(char *str);
void	wait_children(int i, int here_doc);

/*pipex.c*/
int	do_first_cmd(char **av, char **envp, int *pipefd, int here_doc);
int	do_last_cmd(char **av, char **envp, int pipefd[2][2], int i, int here_doc);
int	prepare_child( char **av, char **envp, int pipefd[2][2], int i, int here_doc);
int do_child_odd(char **av, char **envp, int pipefd[2][2], int i, int here_doc);
int	do_child_even(char **av, char **envp, int pipefd[2][2], int i, int here_doc);

/*utils.c*/
char	**split_path(char **envp);
char	*get_path(char *cmd, char **envp);
int		open_file(char *file, char *in_out, int here_doc);
void	exec_cmd(char *cmd, char **envp);

#endif