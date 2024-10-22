#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "Invalid args" << std::endl;
		return 1;
	}

	int fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		std::cerr << "Can't open file" << std::endl;
		return errno;
	}

	char buf[64];
	ssize_t readbytes;
	while((readbytes = read(fd, buf, sizeof(buf))) > 0)
	{
		lseek(fd, -readbytes, SEEK_CUR);
		if(write(fd, "\0", readbytes) == -1)
		{
			std::cerr << "Can't write" << std::endl;
			close(fd);
			return errno;
		}
	}

	if(readbytes == -1)
	{
		std::cerr << "Can't read" << std::endl;
	}

	close(fd);

	if(unlink(argv[1]) == -1)
	{
		std::cerr << "Delete" << std::endl;
		return errno;
	}
		
	return 0;

}	

				

