/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:26:08 by llechert          #+#    #+#             */
/*   Updated: 2025/07/07 12:26:12 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(t_cmd *tab_cmds, t_args *args)
{
	int	i;
	int	pipefd[2];

	i = 0;
	// if (args->heredoc)
	// {
	// 	do_first_here_doc(tab_cmds, args);
	// 	i++;
	// }
	while (i < args->nb_cmd)
	{
		renew_pipe(tab_cmds, i, pipefd, args);
		do_cmd(tab_cmds, i, pipefd, args);
		i++;
	}
}

void	renew_pipe(t_cmd *tab_cmds, int i, int pipefd[2], t_args *args)
{
	if (i < args->nb_cmd - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit_error(tab_cmds, args, args->nb_cmd, 1);
		}
		if (i > 0)
			tab_cmds[i].fd_in = tab_cmds[i - 1].fd_out;
		tab_cmds[i].fd_out = pipefd[1];
	}
	else//(i == nb_cmd)
		tab_cmds[i].fd_in = tab_cmds[i - 1].fd_out;
}

void	do_cmd(t_cmd *tab_cmds, int i, int pipefd[2], t_args *args)
{
	tab_cmds[i].pid = fork();
	if (tab_cmds[i].pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2));
	else if (tab_cmds[i].pid == 0)
	{
		if (i < args->nb_cmd - 1)
			close(tab_cmds[args->nb_cmd - 1].fd_out);
		dup2(tab_cmds[i].fd_in, STDIN_FILENO);//est-ce que ca marche sur la premiere ecriture de heredoc ca ?
		dup2(tab_cmds[i].fd_out, STDOUT_FILENO);//pipe cote ecriture = fd_out
		close(pipefd[0]);
		close(pipefd[1]);
		if (tab_cmds[i].fd_in != STDIN_FILENO)
			close(tab_cmds[i].fd_in);
		if (tab_cmds[i].fd_out != STDOUT_FILENO)
			close(tab_cmds[i].fd_out);
		exec_cmd(tab_cmds[i].cmd_split, tab_cmds[i].path, args->env);
	}
	else
	{
		close(pipefd[1]);
		if (i < args->nb_cmd - 1)
			tab_cmds[i].fd_out = pipefd[0];
		if (tab_cmds[i].fd_in != STDIN_FILENO)
			close(tab_cmds[i].fd_in);
	}
}

void	exec_cmd(char **cmd_split, char *path, char **envp)
{
	if (!cmd_split)
	{
		ft_putstr_fd("Could not split cmd: ", 2);
		exit(127);
	}
	if (!cmd_split[0])
	{
		free_tab_str(cmd_split);
		ft_putstr_fd("Command empty: ", 2);
		exit(127);
	}
	if (path == NULL)
	{
		ft_putstr_fd("path not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		exit(127);
	}
	execve(path, cmd_split, envp);//si la commande fonctionne ca stoppe tout
	perror("execve");
	free_tab_str(cmd_split);
	exit(126);
}
