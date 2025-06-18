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
	int fd = 0;

	fd = open("infile.txt", O_RDONLY);
	// close(fd);
	// close(fd);
	// close(fd);

	return (0);
}