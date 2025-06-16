/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:32 by llechert          #+#    #+#             */
/*   Updated: 2025/06/16 18:51:16 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**split_path;
	char	*tmp_path;
	char	*full_path;

	i = 0;
	/*Reprendre ici car ca marche pas ca*/while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	split_path = ft_split(envp[i] + 5, ":");//+5 pour depasser le $PATH dont on ne veut pas
	i = 0;
	while (split_path[i])
	{
		tmp_path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, X_OK | R_OK))
			return (full_path);
		free(full_path);
		i++;
	}
	free_tab(split_path);
	return (cmd);
}

int	open_file(char *file, char *in_out)
{
	int	fd;

	if (ft_strncmp(in_out, "in", 3) == 0)
		fd = open(file, O_RDONLY);
	else if (ft_strncmp(in_out, "out", 4) == 0)
		fd = open(file, O_WRONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open one of the files!\n", 2);
		exit(-1);//voir si on ne doit pas close et/ou free certains trucs avant d'exit ici
	}
	return (fd);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
