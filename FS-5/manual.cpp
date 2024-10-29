#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return errno;
	}

	int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1)
	{
		std::cerr << "Can't open" << std::endl;
		return errno;
	}

	int newfd = dup(fd);
	if(newfd == -1)
	{
		std::cerr << "Can't dubble" << std::endl;
		return errno;
	}
	
	if((write(fd, "first line\n", 11)) < 0)
	{
		std::cerr << "Can't write" << std::endl;
		close(fd);
		return errno;
	}

	if((write(newfd, "second line\n", 12)) < 0)
        {
                std::cerr << "Can't write" << std::endl;
                close(fd);
		close(newfd);
                return errno;
        }
	
	close(fd);
	close(newfd);

	return 0;
}
