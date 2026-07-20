# SimpleFS - Basit Dosya Sistemi Simülatörü

Bu proje, işletim sistemi seviyesinde dosya yönetimi kavramlarını öğrenmek amacıyla C++ ve sistem çağrılarını kullanarak basit bir dosya sistemi simülatörü (SimpleFS) oluşturur. Gerçek dosya sistemine yazmak yerine tek bir dosya (`disk.sim`) sanal disk olarak kullanılır.

## Özellikler

- **fs_format**: Sanal diski formatlayarak tüm verileri siler.
- **fs_create**: Yeni bir dosya oluşturur ve metadata günceller.
- **fs_delete**: Belirtilen dosyayı siler.
- **fs_write**: Dosyaya veri yazar. Dosya yoksa hata döner.
- **fs_read**: Ofset ve boyut parametreleriyle dosyadan veri okur.
- **fs_ls**: Diskteki dosya isimlerini ve boyutlarını listeler.
- **fs_rename**: Dosyanın adını değiştirir.
- **fs_append**: Mevcut veriyi silmeden dosyanın sonuna veri ekler.
- **fs_truncate**: Dosya içeriğini belirtilen boyuta keser.
- **fs_copy**: Bir dosyanın içeriğini başka bir dosyaya kopyalar.
- **fs_mv**: Dosyayı yeniden adlandırır veya klasörler arası taşımayı simüle eder.
- **fs_backup / fs_restore**: Tüm sanal diskin yedeğini alır veya geri yükler.
- **fs_cat**: Dosya içeriğini ekrana yazdırır.
- **fs_diff**: İki dosyanın bayt bayt farklarını kontrol eder.

## Gereksinimler

- C++11 veya üzeri
- POSIX uyumlu işletim sistemi (Linux, macOS, WSL/Cygwin)
- `g++`, `make`

## Dosya Yapısı

```
├── Makefile
├── fs.h
├── fs.cpp
├── main.cpp
├── disk.sim       # Sanal disk (1 MB)
└── README.md      # Bu doküman
```

## Derleme ve Çalıştırma

```bash
# Gerekli paketleri yükleyin (Ubuntu örneği):
sudo apt update
sudo apt install build-essential

# Proje kökünde:
make
./simplefs
```

## Kullanım

Program çalıştırıldığında aşağıdaki menü ekrana gelir. Seçim yapıp ilgili parametreleri girerek işlemleri gerçekleştirebilirsiniz.

```
SimpleFS Menu:
1. Format
2. Create file
3. Delete file
4. Write file
5. Read file
6. List files
7. Rename file
8. Append file
9. Truncate file
10. Copy file
11. Move file
12. Backup
13. Restore
14. Cat file
15. Diff files
0. Exit
Choice:
```

### Örnek Test Senaryosu

1. **Format** (`1`): Boş bir dosya sistemi oluşturur.
2. **List** (`6`): Hiç dosya olmadığını doğrular.
3. **Create** (`2`, `test.txt`): Yeni dosya oluşturur.
4. **Write** (`4`, `test.txt`, `Merhaba`): İçerik yazar.
5. **Cat** (`14`, `test.txt`): `Merhaba` çıktısını görür.
6. **Append** (`8`, `test.txt`, ` Dünya`): Yazıya ekleme yapar.
7. **Read** (`5`, `test.txt`, offset=7, size=5): `Dünya` okur.
8. **Truncate** (`9`, `test.txt`, new size=7): Sadece `Merhaba` kalır.
9. **Copy** (`10`, `test.txt`, `copy.txt`): Kopya dosya oluşturur.
10. **Rename** (`7`, `copy.txt`→`moved.txt`): Dosya adını değiştirir.
11. **Backup** (`12`, `disk.sim.bak`): Disk yedeği alır.
12. **Format** sonra **Restore** (`13`, `disk.sim.bak`): Dosyalar geri gelir.
13. **Diff** (`15`, `test.txt`, `moved.txt`): `Files are identical` mesajını alırsınız.

## Katkıda Bulunanlar

- Proje sahibi: Öğrenci A, Öğrenci B
