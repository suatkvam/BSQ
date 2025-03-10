#!/usr/bin/perl
use warnings;
use strict;

# Argüman kontrolü
die "Kullanım: program x y density\n" unless (scalar(@ARGV) == 3);
my ($x, $y, $density) = @ARGV;

# Dosya aç
open(my $fh, '>', 'map.txt') or die "Dosya açılamadı: $!";

# İlk satır (map yüksekliği + karakterler)
print $fh "$y.ox\n";

# Harita üretimi
for (my $i = 0; $i < $y; $i++) {
    for (my $j = 0; $j < $x; $j++) {
        if (int(rand(100)) < $density) {
            print $fh "o";  # Engel
        }
        else {
            print $fh ".";  # Boş alan
        }
    }
    print $fh "\n";  # Satır sonu
}

# Dosyayı kapat
close $fh;
