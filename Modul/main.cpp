#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cstring>

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    const char* file_path = argv[1];
    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
	std::cerr << "Error opening file";
        return 1;
    }

    const size_t buffer_size = 1024;
    char buffer[buffer_size];
    std::string file;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, buffer_size)) > 0)
    {
        file.append(buffer, bytes_read);
    }

    if (bytes_read == -1)
    {
	std::cerr << "Error reading file";
        close(fd);
        return 1;
    }

    close(fd);

    std::vector<int> numbers;
    size_t i = 0;
    while (i < file.size()) 
    {
        while (i < file.size() && isspace(file[i])) 
	{
            ++i;
        }

        std::string number_str;
        while (i < file.size() && isdigit(file[i]))
       	{
            number_str += file[i];
            ++i;
        }

        if (!number_str.empty()) 
	{
            numbers.push_back(std::stoi(number_str));
        }
    }

    if (numbers.empty())
    {
        std::cerr << "Datark" << std::endl;
        return 1;
    }

    double sum = 0;
    for (int num : numbers)
    {
        sum += num;
    }
    double mijin = sum / numbers.size();

    std::cout << mijin << std::endl;
    return 0;
}
