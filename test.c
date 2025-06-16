#include "./includes/pipex.h"
#include "./libft/libft.h"

int	main(int ac, char **av, char **envp)
{
	// printf("%d\n", access("/bin/ls", X_OK | R_OK));//fonctionne
	// printf("%d\n", access("./a.out", X_OK | R_OK));//fonctionne aussi

	char *args[] = {"ls", "-l", NULL};
    char *args2[] = {"ls", "brvm", NULL};
	// printf("%d\n", execve("/bin/ls", args, envp));//fonctionne
	// printf("%d\n", execve("/bin", args, envp));//KO
	// printf("%d\n", execve("/bin/ls", args2, envp));//ls renvoie qu'il connait pas brvm
	// printf("%d\n", execve("ls", args, envp));//KO


	int		i;
	int		j = 0;
	char	**split_path;
	char	*tmp_path;
	char	*full_path;

	i = 0;
	while (envp[i][j])
	{
		while (envp[i][j])
		{
			write(1, &envp[i][j], 1);
			j++;
		}
		i++;
		j = 0;
	}

	// i = 0;
	// while (envp[i] && ft_strncmp(envp[i], "$PATH", 5) != 0)
	// 	i++;
	// split_path = ft_split(envp[i] + 5, ':');//+5 pour depasser le $PATH dont on ne veut pas
	// i = 0;
	// while (split_path[i])
	// {
	// 	printf("%s\n", split_path[i]);
	// 	i++;
	// }
	return (0);
}