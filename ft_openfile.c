#include "fr_readmap.h"

// Dosya açma fonksiyonu
int	ft_openfile(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY); // Dosyayı okuma modunda aç
	if (fd == -1)
	{
		write(2, "File is not here\n", 17); // Hata mesajı yazdır
		return (-1);
	}
	return (fd); // Dosya başarıyla açıldı, dosya tanımlayıcısını döndür
}