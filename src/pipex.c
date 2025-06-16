/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:27 by llechert          #+#    #+#             */
/*   Updated: 2025/06/16 18:00:57 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	do_child(int *pipefd, char **av, char **envp)
{
	int	fd;

	fd = open_file(av[1], "in");
	dup2(fd, 0);//on fait pointer l'entree standard sur le infile
	close(pipefd[0]);//on ferme le cote lecture du pipe
	dup2(pipefd[1], 1);//on fait pointer la sortie standard sur la sortie du pipe ==> comme ca le process parent pourra lire ce qui vient du pipe
	exec_cmd(av[2], envp);
}

void	do_parent(int *pipefd, char **av, char **envp)
{
	int	fd;

	fd = open_file(av[4], "out");
	dup2(pipefd[1], 0);//on fait pointer l'entree standard sur la sortie du pipe
	close(pipefd[0]);//on ferme la sortie du pipe (la ou on ecrit)
	dup2(fd, 1);//on fait pointer la sortie standard sur l'outfile ==> comme ca le process parent pourra ecrire dans l'outfile
	exec_cmd(av[3], envp);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');//on separe la commande des options eventuelles
	path = get_path(cmd_split[0], envp);//
	if (execve(path, cmd_split, envp) == -1)//si la commande n'existe pas
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		ft_free_tab(cmd_split);
		free(path);
		exit(0);
	}
	free(path);//utile ou pas ?
}