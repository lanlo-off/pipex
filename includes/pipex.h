/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:31:58 by llechert          #+#    #+#             */
/*   Updated: 2025/06/17 15:28:29 by llechert         ###   ########.fr       */
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

/*pipex.c*/
void	do_child(int *pipefd, char **av, char **envp);
void	do_parent(int *pipefd, char **av, char **envp);
void	exec_cmd(char *cmd, char **envp);

/*utils.c*/
char	**split_path(char **envp);
char	*get_path(char *cmd, char **envp);
int	open_file(char *file, char *in_out);
void	free_tab(char **tab);

#endif