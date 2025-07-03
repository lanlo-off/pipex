/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:31:58 by llechert          #+#    #+#             */
/*   Updated: 2025/06/20 11:48:30 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
int		is_here_doc(char *str);
void	wait_children(int nb_cmd);


/*pipex.c*/
int		do_first_cmd(char **av, char **envp, int i, int fd_in);
int		do_last_cmd(char *cmd, char **envp, int fd_in, int fd_out);
int		process_child(char **av, char **envp, int i, int fd_in);

/*utils.c*/
char	**split_path(char **envp);
char	*get_path(char *cmd, char **envp);
int		open_file(char *file, char *in_out, int here_doc);
void	exec_cmd(char *cmd, char **envp);
void	close_fds(int fd_in, int fd_out);

#endif