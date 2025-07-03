/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:39:09 by llechert          #+#    #+#             */
/*   Updated: 2025/07/03 19:03:08 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_infile(char *file, int	here_doc)
{
	int	fd;

	fd = -1;
	if (here_doc == 1)
		return (0);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Could not read infile!\n", 2);//free apres le retour de la fonction
	return (fd);
}

int	open_outfile(char *file, int here_doc)
{
	int	fd;

	fd = -1;
	if (here_doc == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		ft_putstr_fd("Could not open outfile!\n", 2);//free apres le retour de la fonction
	return (fd);
}

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in > 0 && fd_in != STDIN_FILENO && fd_in != STDOUT_FILENO
		&& fd_in != STDERR_FILENO)
		close(fd_in);
	if (fd_out > 0 && fd_out != STDIN_FILENO && fd_out != STDOUT_FILENO
		&& fd_out != STDERR_FILENO)
		close(fd_out);
}

void	free_cmds(t_cmd *tab_cmds, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (tab_cmds[i].path && tab_cmds[i].path != tab_cmds[i].cmd_split[0])
			free(tab_cmds[i].path);// seulement si path a été malloc séparément de cmd_split
		if (tab_cmds[i].cmd_split)
			free_tab_str(tab_cmds[i].cmd_split);
		i++;
	}
	free(tab_cmds);
}

void	exit_error(t_cmd *tab_cmds, t_args *args, int nb_cmd, int error)
{
	free_cmds(tab_cmds, nb_cmd);
	free(args);
	exit(error);
}