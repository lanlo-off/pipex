/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:27 by llechert          #+#    #+#             */
/*   Updated: 2025/06/19 14:46:58 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	do_first_cmd(char **av, char **envp, int i, int fd_in)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)
	{
		ft_printf("first child [%d] || fd : %d\n", i, pipefd[1]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		exec_cmd(av[i], envp);
	}
	else
	{
		ft_printf("process first parent [%d] || fd : %d\n", i, pipefd[0]);
		dup2(pipefd[0], STDOUT_FILENO);
		close(pipefd[1]);
	}
	return (pipefd[0]);
}

int	process_child(char **av, char **envp, int i, int fd_in)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)
	{
		ft_printf("process child [%d] || fd : %d\n", i, pipefd[1]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		exec_cmd(av[i], envp);
	}
	else
	{
		ft_printf("process parent [%d] || fd : %d\n", i, pipefd[0]);
		// dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	return (pipefd[0]);
}

int	do_last_cmd(int ac, char **av, char **envp, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)//lorsque la premiere commande arrive ici on a encore le dup2(fd_in, 0) du main donc ok
	{
		ft_printf("last process [%d] || fd : %d\n", ac - 2, fd_out);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		exec_cmd(av[ac - 2], envp);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (0);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');//on separe la commande des options eventuelles
	if (cmd_split == NULL)
	{
		ft_putstr_fd("Command empty: ", 2);
		return ;
	}
	path = get_path(cmd_split[0], envp);
	if (path == NULL)
	{
		ft_printf("path not found: %s\n", cmd_split[0]);
		free_tab(cmd_split);
		free(path);
	}
	else if (execve(path, cmd_split, envp) == -1)//si la commande n'existe pas
	{
		ft_printf("command not found: %s\n", cmd_split[0]);
		free_tab(cmd_split);
		free(path);
	}
}
