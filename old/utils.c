/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:32 by llechert          #+#    #+#             */
/*   Updated: 2025/06/18 16:39:56 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**split_path(char **envp)
{
	int		i;
	int		j;
	char	*sub;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strncmp(sub, "PATH", 5) == 0)
		{
			free(sub);
			paths = ft_split(envp[i] + j + 1, ':');
			return (paths);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**all_path;
	char	*tmp_path;
	char	*full_path;

	if (*cmd == '/')
	
	all_path = split_path(envp);
	i = 0;
	while (all_path[i])
	{
		tmp_path = ft_strjoin(all_path[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, F_OK | X_OK) == 0)//Masque | car en binaire : F_OK correspond a 0000 alors que X_OK = 0001 donc si on fait & ca sera toujours faux
		{
			free_tab(all_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(all_path);
	return (cmd);
}

int	open_file(char *file, char *in_out)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(in_out, "in", 3) == 0)
		fd = open(file, O_RDONLY);
	else if (ft_strncmp(in_out, "out", 4) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open one of the files!\n", 2);
		exit(-1);//voir si on ne doit pas close et/ou free certains trucs avant d'exit ici
	}
	return (fd);
}
