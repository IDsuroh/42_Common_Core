#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	parent(char **av, char **envp, int *fd)
{
	close(fd[1]);
	bytesread = read(fd[0], buffer, sizeof(buffer) - 1);
	
}

void	child(char **av, char **envp, int *fd, int filein)
{
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(filein);
	execve("/bin/cat", av + 2, envp);
}

int	main(int ac, char **av, char **envp)
{
	int	filein;
	int	fd[2];
	pid_t	pid;
	
	pid = fork();
	pipe(fd);
	if (ac <2)
	{
		write(2, "Error1\n", 7);
		return 1;
	}
	filein = open(av[1], O_RDONLY);
	if (filein == -1)
	{	
		write(2, "Error2\n", 7);
		return 1;
	}
	if (pid == 0)
		child(av, envp, fd, filein);
	waitpid(pid, NULL, 0);
	parent(av, envp, fd);
	return 0;
}
