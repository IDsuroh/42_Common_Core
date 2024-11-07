#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	int	x;

	if (mkfifo("my fifo 1", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("\n\t\tCan't create fifo file.\n");
			return (1);
		}
	}
	printf("Opening...\n");
	if ((fd = open("my fifo 1", O_WRONLY)) == -1)
		return (3);
	printf("Opened\n");
	x = 97;
	if (write(fd, &x, sizeof(x)) == -1)
	{
		return (2);
	}
	printf("Written\n");
	close(fd);
	printf("Closed\n");
	return (0);
}
