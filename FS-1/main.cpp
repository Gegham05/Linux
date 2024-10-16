#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
        	std::cerr << argv[0] << std::endl;
        	return 1;
        }
	int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
	{
        	std::cerr << errno << std::endl;
        	return errno;
   	 }
    	 char buf[32];
    	 ssize_t readbytes;
	 while ((readbytes = read(fd, buf, sizeof(buf))) > 0)
	 {
        	 std::cout.write(buf, readbytes);
   	 }
	 if (readbytes == -1)
	 {
         	std::cerr << errno << std::endl;
         	close(fd);
         	return errno;
   	 }
    	 if (close(fd) == -1)
	 {
        	 std::cerr << errno << std::endl;
        	 return errno;
    	 }

	 return 0;
}
