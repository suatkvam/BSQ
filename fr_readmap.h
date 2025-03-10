#ifndef FR_READMAP_H
# define FR_READMAP_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define MAX_BUFFER_SIZE 1024

int     ft_openfile(const char *path);
ssize_t read_line(int fd, char *buffer, size_t max_len);
void    ft_readfile(int fd);

#endif