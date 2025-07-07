/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:31:58 by llechert          #+#    #+#             */
/*   Updated: 2025/07/07 12:22:02 by llechert         ###   ########.fr       */
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

typedef struct s_cmd
{
	int				cmd_nb;
	char			*cmd;
	char			**cmd_split;
	char			*path;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				exit_status;
	struct s_args	*next;
}	t_cmd;

typedef struct s_args
{
	int		nb_cmd;
	char	**av;
	char	**env;
	int		heredoc;
}	t_args;

/*main.c*/
void	fill_args(t_args *args, int argc, char **argv, char **envp);
t_cmd	*init_cmds(t_args *args);
void	fill_cmd(t_cmd *tab_cmds, t_args *args, int i);
int		wait_children(t_cmd *tab_cmds, int nb_cmd);

/*pipex.c*/
void	pipex(t_cmd *tab_cmds, t_args *args);
void	renew_pipe(t_cmd *tab_cmds, int i, int pipefd[2], t_args *args);
void	do_cmd(t_cmd *tab_cmds, int i, int pipefd[2], t_args *args);
void	exec_cmd(char **cmd_split, char *path, char **envp);

/*utils.c*/
char	**split_path(char **envp);
char	*get_path(char *cmd, char **envp);

/*files_free.c*/
int		open_infile(char *file, int	here_doc);
int		open_outfile(char *file, int here_doc);
void	close_fds(int fd_in, int fd_out);
void	free_cmds(t_cmd *cmds, int nb_cmd);
void	exit_error(t_cmd *tab_cmds, t_args *args, int nb_cmd, int error);

#endif