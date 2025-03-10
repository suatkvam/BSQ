#include "fr_readmap.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


// Satır okuma fonksiyonu
ssize_t	read_line(int fd, char *buffer, size_t max_len)
{
	ssize_t	i;
	char	c;
	ssize_t	ret;

	i = 0;
	// Dosyadan karakter karakter oku
	while (i < (ssize_t)(max_len - 1))
	{
		ret = read(fd, &c, 1); // Bir karakter oku
		if (ret <= 0)
			break ; // Dosya bitti veya hata oluştu
		buffer[i++] = c; // Okunan karakteri buffer'a ekle
		if (c == '\n') // Satır sonu (newline) karakterini bulursa, işlemi sonlandır
			break ;
	}
	buffer[i] = '\0'; // Sonlandırıcı ekle
	return (i); // Okunan karakter sayısını döndür
}