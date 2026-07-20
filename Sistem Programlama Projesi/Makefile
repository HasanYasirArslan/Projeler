# Makefile

CC      := g++
CFLAGS  := -std=c++11 -Wall

# Phony hedefler
.PHONY: all clean

# Default hedef: önce simplefs'i oluştur, sonra çalıştır
all: simplefs
	@echo ">>> Running SimpleFS..."
	@./simplefs

# Link aşaması
simplefs: main.o fs.o
	$(CC) $(CFLAGS) -o $@ $^

# Derleme aşamaları
main.o: main.cpp fs.h
	$(CC) $(CFLAGS) -c main.cpp

fs.o: fs.cpp fs.h
	$(CC) $(CFLAGS) -c fs.cpp

# Geçici dosyaları ve disk simülasyon dosyasını silmek için
clean:
	rm -f *.o simplefs disk.sim
