Bilgisayar mühendisliği öğrencilik dönemim boyunca geliştirdiğim projeler, edindiğim teorik bilgileri pratiğe dökme ve farklı teknolojileri deneyimleme fırsatı sundu. GitHub repomda bulunan bu projelerin tamamı, donanımdan yazılıma, oyun geliştirmeden ağ ve sistem programlamaya kadar geniş bir yelpazeyi kapsamaktadır.

1. YKS Deneme Analizi Programı ve İstatistik Yazılımı (Bitirme Çalışması)
Bu proje, üniversiteye hazırlık sürecindeki öğrencilerin deneme sınavı verilerini takip edip analitik olarak anlamlandırmalarını sağlayan modern bir web platformudur.
Kullanılan Teknolojiler: React.js, Tailwind CSS, Google Gemini LLM API, Local Storage, Recharts.
Temel İşlevler: Veri giriş sürecini hızlandıran asenkron klavye dinleyicilerine sahip sanal optik okuyucu kullanılmıştır. Öğrencinin ham netleri hesaplandıktan sonra Z-Skoru ile ders bazlı zayıflıklar tespit edilmekte ve geçmiş yılların taban verilerine göre doğrusal regresyon kullanılarak Türkiye sıralaması simülasyonu üretilmektedir.
Yapay Zekâ Mentoru: Uygulamanın kalbini, Google Gemini API entegrasyonuyla çalışan otonom mentor motoru oluşturur. Yapay zekâ, arka planda öğrencinin sınav istatistiklerini analiz ederek, tespit ettiği eksik kazanımlara yönelik doğrudan sistem takvimine işlenen JSON formatında otonom çalışma programları üretir. Veriler dışarı sızmaması ve sunucu maliyeti yaratmaması için çevrimdışı öncelikli olarak tarayıcının yerel hafızasında (Local Storage) saklanmaktadır.

2. Hikâye Tabanlı 2D Piksel Oyun: Halisler (Bilgisayar Mühendisliği Tasarımı)
Geleneksel oyunlar yerine hikâye tabanlı ve 2D piksel sanat estetiğine sahip bir aksiyon-macera oyunudur.
Kullanılan Teknolojiler: Unity, C#, Google Gemini 2.5 Flash API (REST API katmanı).
Temel İşlevler: Mekanikler arasında rastgele tuş girişlerini ortadan kaldıran yüksek risk-yüksek ödül prensibine dayalı stratejik savuşturma (parry) sistemi ve kombo tabanlı büyü atışları bulunmaktadır. Oyun motorundaki "Custom Axis Sorting" ayarlarıyla, "Top-Down" (Kuş Bakışı) kamerada nesnelerin pivot noktaları referans alınarak 2D düzlemde 3 boyutlu derinlik ve oklüzyon algısı yaratılmıştır.
Dinamik NPC Etkileşimi: Sabit diyalog ağaçları yerine Üretken Yapay Zekâ (LLM) destekli NPC'ler kullanılmıştır. Modüler persona mühendisliği (NpcProfile) ile her karakterin kişilik özellikleri, görev bağlamları ve sınırları API'ye iletilir ve oyunculara serbest metin üzerinden gerçek zamanlı, bağlama duyarlı sohbet etme imkânı sunulur.

3. Akıllı Mama Otomatı Projesi (Nesnelerin İnterneti - IoT)
Kedi ve köpek sahiplerinin eve bağlı kalmasını engelleyen, porsiyon bazlı ve saat ayarlı bir akıllı otomasyon projesidir.
Kullanılan Teknolojiler: NodeMCU (ESP8266), Loadcell (Ağırlık Sensörü), HX711 ADC entegresi, Servo Motor, Blynk.io, Firebase, TinyDB, MIT App Inventor, 3D Baskı.
Temel İşlevler: Sistem içerisindeki 4 adet ağırlık sensörü (Loadcell) ile kaptaki mama miktarı anlık ölçülmektedir. Blynk.io ve MIT App Inventor kullanılarak geliştirilen kullanıcı dostu mobil arayüz ile motor kontrolü sağlanır; mama saati ve miktarı otomatik ayarlanabildiği gibi manuel olarak da komut verilebilir. Depodaki mama kritik seviyeye ulaştığında kullanıcı uyarılır. Ayrıca geçmiş veriler (TinyDB) sayesinde evcil hayvanın yeme düzeni takip edilebilir.

4. İşletim Sistemleri - Komut Satırı Yorumlayıcısı (Shell)
Linux işletim sistemleri mantığını pratik olarak kullanmak üzere geliştirilmiş, C programlama dilinde yazılmış özel bir komut satırı yorumlayıcısıdır (kabuk).
Temel İşlevler: Kullanıcı komutlarını yorumlar, fork, execvp ve waitpid çağrılarıyla ana kabuk içerisinde yeni prosesler oluşturup sonlanmalarını yönetir.
Gelişmiş Komutlar: Bir dosyadan okuma (<) ve bir dosyaya yazma (>) gibi I/O yönlendirmelerini yapabilir. Komut sonuna eklenen & ile işlemleri arka planda (background) yürütebilir. | sembolü ile bir komutun çıktısını diğerine girdi yapan borulama hattı ve ; ile aynı satırda ardışık komut yürütme desteği içermektedir.

5. Basit Dosya Sistemi Simülatörü - SimpleFS (Sistem Programlama)
İşletim sistemi seviyesindeki dosya depolama ve tahsis mimarisini anlamaya yönelik C++ tabanlı bir simülatördür.
Temel İşlevler: Fiziksel bir disk yerine disk.sim isimli 1 MB'lık tek bir dosya üzerinden çalışır. Sistemin ilk 4 KB'lık alanı metadata (üst veri) işlemlerine, kalanı ise 512 B'lık bloklar halinde asıl dosya verisi depolamasına ayrılmıştır.
Sistem çağrılarının kullanımını simüle ederek konsol tabanlı bir arayüzle dosya oluşturma, okuma, yazma, ekleme, taşıma, parçalanmaları birleştirme (defragmantasyon) ve yedekleme gibi karmaşık yönetim süreçlerini modüler olarak yerine getirir.

6. ICMP İstemci-Sunucu Uygulaması (Ağ Programlama)
C dilinde ve libpcap kütüphanesi kullanılarak geliştirilmiş bir ping haberleşme simülasyonudur.
Temel İşlevler: Bu projede, Ethernet, IP ve ICMP paket başlıkları kütüphaneler yerine tamamen manuel olarak inşa edilir. Sunucu, kendine gelen paketlerin IP hedeflerini "etiket" olarak tanır.
Ağ üzerinde kullanıcı komutuna göre "Echo Reply", "Host Unreachable" veya "TTL Exceeded" gibi çeşitli ICMP hata kodları dönebilir. Veri bütünlüğünde bozulma olan paketler (bad checksum) tespit edildiğinde ise otomatik olarak "Parameter Problem" ile cevap verilmektedir.

7. Süpermarket Tek Kasalı Kuyruk Sistemi Simülasyonu
Excel üzerinde ayrık olay yaklaşımıyla kurgulanan bir sistem benzetimidir.
Temel İşlevler: Tek bir kasa ve İlk Giren İlk Çıkar (FIFO) kuralına dayalı olarak çalışır. Sistemde müşteri geliş süreleri (interarrival) üstel dağılım olarak tespit edilmiş ve istatistiksel modele oturtulmuştur.
Doğrulama: Simülasyonda kullanılan rastgele sayılar "Lineer Eşlenik Üreteç (LCG)" ile üretilmiş ve Kolmogorov-Smirnov Testi ile doğru dağılımda oldukları ispatlanmıştır. Kuyruktaki ortalama müşteri sayısı ve sistem bekleme süreleri performans ölçütü olarak modellenmiştir.

8. Veri Yapıları Projeleri (DNA ve İkili Arama Ağacı)
Veri yapılarının (C++) temel ve gelişmiş kullanımlarını pekiştiren iki ödevden oluşmaktadır.
Ödev 1 (DNA): Tek bağlı listeler kullanılarak kromozom ve DNA dizilimleri oluşturulmuş; bu dizilimler üzerinde çaprazlama ve mutasyon algoritmaları uygulanmıştır. Tek yönlü listede geriye dönüş imkânı olmadığı için ekrana yazdırma işleminde listelerin ters çevrilmesi mantığıyla çözüm geliştirilmiştir.
Ödev 2 (BST): Konsolda, klavye kontrolleri ile oklarla görselleştirilerek bir ikili arama ağacının içerisinde gezinilmiştir. En fazla 10 düğümün sayfalandırılması, ağacın toplam değerinin bulunması, düğüm silinmesi ve yapının aynalanması (mirroring) algoritmalarını içerir.

9. Oyun Platformu Veri Tabanı Tasarımı (VTYS)
Bir oyun satış ve topluluk platformunun veri tabanını yapılandıran modelleme projesidir.
Temel İşlevler: Oyun, geliştirici, satış, stok, kategori, sunucu ve oyuncu tabloları oluşturulmuştur. İş kurallarına göre entiteler arası bağlar belirlenmiş ve bu bağlar metinsel gösterimler ile Crow's Foot gösterimli ER (Varlık-İlişki) diyagramları ile görselleştirilerek sunulmuştur.

10. Programlamaya Giriş Projeleri (Üniversite Bilgi Sistemi ve Karmaşık Sayılar)
Yazılım geliştirmeye giriş adımlarında C++ dilinin pratik edildiği temel iki çalışmayı kapsamaktadır.
Üniversite Bilgi Sistemi: C++ ile öğrenci ad, soyad ve notları struct yapıları kullanılarak oluşturulan dizilerde tutulmuştur. Sınıf geçme sistemindeki standart sapma ve ortalama hesabı algoritmaları kodlanarak, do-while döngüsüne ve koşul yapılarına (if-else) sahip interaktif bir konsol menüsü yapılmıştır.
Karmaşık Sayılar: Yine bu repo dahilinde, C++ kullanılarak karmaşık sayılar arasında dört işlemin uygulandığı obje odaklı temel bir yapıdır.