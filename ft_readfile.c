// #include "fr_readmap.h"

// #include <unistd.h>
// #include <fcntl.h>
// #include <stdlib.h>

// #define MAX_BUFFER_SIZE 1024

// void	ft_readfile(int fd)
// {
// 	char	buffer[MAX_BUFFER_SIZE];
// 	ssize_t	bytes_read;
// 	int		map_height;
// 	char	empty_char;
// 	char	obstacle_char;
// 	char	filled_char;
// 	int		i;
// 	int		j;
// 	char	**map;

// 	(void)empty_char;
// 	(void)obstacle_char;
// 	(void)filled_char;

// 	// Dosyadan ilk satırı oku
// 	bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		write(2, "Error reading file header\n", 26); // Başlık okunamadı hatası
// 		return ;
// 	}
	
// 	// Harita yüksekliğini al
// 	map_height = 0;
// 	i = 0;
// 	while (buffer[i] >= '0' && buffer[i] <= '9')
// 	{
// 		map_height = map_height * 10 + (buffer[i] - '0'); // Yüksekliği hesapla
// 		i++;
// 	}
// 	if (map_height <= 0)
// 	{
// 		write(2, "Error: Invalid map height\n", 26); // Geçersiz harita yüksekliği
// 		return ;
// 	}
	
// 	// Harita karakterlerini al
// 	empty_char = buffer[i++];
// 	obstacle_char = buffer[i++];
// 	filled_char = buffer[i++];
	
// 	// Harita belleğini ayır
// 	map = (char **)malloc(sizeof(char *) * map_height);
// 	if (!map)
// 	{
// 		write(2, "Memory allocation error\n", 24); // Bellek hatası
// 		return ;
// 	}
	
// 	// Harita satırlarını oku ve belleğe al
// 	j = 0;
// 	while (j < map_height)
// 	{
// 		bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE); // Satır oku
// 		if (bytes_read <= 0)
// 		{
// 			write(2, "Error reading map line\n", 23); // Harita satırı okuma hatası
// 			while (--j >= 0) // Belleği temizle
// 				free(map[j]);
// 			free(map);
// 			return ;
// 		}
// 		map[j] = (char *)malloc(bytes_read + 1); // Satır için bellek ayır
// 		if (!map[j])
// 		{
// 			write(2, "Memory allocation error\n", 24); // Bellek hatası
// 			while (--j >= 0) // Belleği temizle
// 				free(map[j]);
// 			free(map);
// 			return ;
// 		}
// 		i = 0;
// 		while (i < bytes_read) // Satırdaki karakterleri kopyala
// 		{
// 			map[j][i] = buffer[i];
// 			i++;
// 		}
// 		map[j][i] = '\0'; // Satır sonu karakterini ekle
// 		j++;
// 	}
	
// 	// Haritayı ekrana yazdır
// 	j = 0;
// 	while (j < map_height)
// 	{
// 		write(1, map[j], bytes_read); // Satırları yazdır
// 		free(map[j]); // Belleği temizle
// 		j++;
// 	}
// 	free(map); // Harita belleğini serbest bırak
// }


#include "fr_readmap.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_BUFFER_SIZE 1024

typedef struct s_map_info {
    int height;
    char empty;
    char obstacle;
    char filled;
    char **data;
} t_map_info;

void free_map(char **map, int rows)
{
    while (--rows >= 0)
        free(map[rows]);
    free(map);
}

int parse_header(char *buffer, t_map_info *map)
{
    int i = 0;
    
    map->height = 0;
    while (buffer[i] >= '0' && buffer[i] <= '9')
        map->height = map->height * 10 + (buffer[i++] - '0');
        
    if (map->height <= 0)
        return 0;
        
    map->empty = buffer[i++];
    map->obstacle = buffer[i++];
    map->filled = buffer[i++];
    
    map->data = (char **)malloc(sizeof(char *) * map->height);
    return (map->data != NULL);
}

int read_map_lines(int fd, t_map_info *map)
{
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;
    int i, j = 0;
    
    while (j < map->height)
    {
        bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE);
        if (bytes_read <= 0)
            return 0;
            
        map->data[j] = (char *)malloc(bytes_read + 1);
        if (!map->data[j])
            return 0;
            
        i = 0;
        while (i < bytes_read)
        {
            map->data[j][i] = buffer[i];
            i++;
        }
        map->data[j][i] = '\0';
        j++;
    }
    return bytes_read;
}

void ft_readfile(int fd)
{
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;
    t_map_info map;
    int j = 0;
    
    bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE);
    if (bytes_read <= 0 || !parse_header(buffer, &map))
    {
        write(2, "Error reading map header\n", 25);
        return;
    }
    bytes_read = read_map_lines(fd, &map);
    if (bytes_read <= 0)
    {
        write(2, "Error reading map content\n", 26);
        if (map.data)
            free_map(map.data, j);
        return;
    }
    while (j < map.height)
    {
        write(1, map.data[j], bytes_read);
        j++;
    }
    free_map(map.data, map.height);
}
