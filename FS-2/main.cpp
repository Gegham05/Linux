#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << argv[0] << std::endl;
        return 1;
    }
    
    int source_file = open(argv[1], O_RDONLY);
    int new_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (source_file == -1 || new_file == -1)
    {
        std::cerr << "opening" << std::endl;
        if (source_file != -1)
	{
		close(source_file);
        	return errno;
	}
    }

    char buf[32];
    ssize_t readbytes;
    while ((readbytes = read(source_file, buf, sizeof(buf))) > 0) 
    {
        if (write(new_file, buf, readbytes) != readbytes)
        {
            std::cerr << "writing" << std::endl;
            close(source_file);
            close(new_file);
            return errno;
        }
    }

    if (readbytes == -1)
    {
	    std::cerr << "reading" << std::endl;
    }

    close(source_file);
    close(new_file);

    if (readbytes == -1)
    {
	    return errno;
    }

    std::cout << "copied" << std::endl;
    return 0;
}
