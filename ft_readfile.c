#include "fr_readmap.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

void	ft_readfile(int fd)
{
	char	buffer[MAX_BUFFER_SIZE];
	ssize_t	bytes_read;
	int		map_height;
	char	empty_char;
	char	obstacle_char;
	char	filled_char;
	int		i;
	int		j;
	char	**map;

	(void)empty_char;
	(void)obstacle_char;
	(void)filled_char;

	// Dosyadan ilk satırı oku
	bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		write(2, "Error reading file header\n", 26); // Başlık okunamadı hatası
		return ;
	}
	
	// Harita yüksekliğini al
	map_height = 0;
	i = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9')
	{
		map_height = map_height * 10 + (buffer[i] - '0'); // Yüksekliği hesapla
		i++;
	}
	if (map_height <= 0)
	{
		write(2, "Error: Invalid map height\n", 26); // Geçersiz harita yüksekliği
		return ;
	}
	
	// Harita karakterlerini al
	empty_char = buffer[i++];
	obstacle_char = buffer[i++];
	filled_char = buffer[i++];
	
	// Harita belleğini ayır
	map = (char **)malloc(sizeof(char *) * map_height);
	if (!map)
	{
		write(2, "Memory allocation error\n", 24); // Bellek hatası
		return ;
	}
	
	// Harita satırlarını oku ve belleğe al
	j = 0;
	while (j < map_height)
	{
		bytes_read = read_line(fd, buffer, MAX_BUFFER_SIZE); // Satır oku
		if (bytes_read <= 0)
		{
			write(2, "Error reading map line\n", 23); // Harita satırı okuma hatası
			while (--j >= 0) // Belleği temizle
				free(map[j]);
			free(map);
			return ;
		}
		map[j] = (char *)malloc(bytes_read + 1); // Satır için bellek ayır
		if (!map[j])
		{
			write(2, "Memory allocation error\n", 24); // Bellek hatası
			while (--j >= 0) // Belleği temizle
				free(map[j]);
			free(map);
			return ;
		}
		i = 0;
		while (i < bytes_read) // Satırdaki karakterleri kopyala
		{
			map[j][i] = buffer[i];
			i++;
		}
		map[j][i] = '\0'; // Satır sonu karakterini ekle
		j++;
	}
	
	// Haritayı ekrana yazdır
	j = 0;
	while (j < map_height)
	{
		write(1, map[j], bytes_read); // Satırları yazdır
		free(map[j]); // Belleği temizle
		j++;
	}
	free(map); // Harita belleğini serbest bırak
}