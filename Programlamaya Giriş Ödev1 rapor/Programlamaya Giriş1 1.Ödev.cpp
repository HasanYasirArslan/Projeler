/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI…...:1
**				ÖĞRENCİ ADI...............:Hasan Yasir
**				ÖĞRENCİ SOYADI............:Arslan
**				ÖĞRENCİ NUMARASI.:B221210096
**				DERS GRUBU…………:A
****************************************************************************/



using namespace std;//her seferinde std yazmamak icin
#include <iostream>
#include<iomanip>	//setw kullanimi icin
#include<cstdlib>	// srand ve rand fonksiyonlarinin kullanimi icin
#include<ctime>		//time() fonksiyonu icin
#include<string>	//string kullanimi icin
#include<cmath>		//karekok islemleri icin
struct Tarih		//tarihi gun.ay.yil olarak tanimlamak icin struct kullanimi
{
	int gun;
	int ay;
	int yil;
};
struct ogrBilgi		//ogrenci bilgilerini(isim,soyisim,numara,vize vb yapi uye degiskenlerini tanimlamak icin struct kullanimi
{
	string ad;
	string soyad;
	int numara;
	float vize;
	float kisaSinav1;
	float kisaSinav2;
	float odev1;
	float odev2;
	float proje;
	float final;
	struct Tarih DogumTarihi;		//tarih struct i veri turunden dogumTarihi olmasi icin ic ice struct kullanimi
};
string ogrAd[30] = { "Selim","Ahmet","Bayram","Burak","Kemal","Muhammet","Ali","Hasan","Mustafa","Said","Kerim","Aynur","Elif","Sultan","Fatih","Kenan","Kamuran","Ramazan","Sebahat","Beyza","Furkan","Mete","Zafer","Zehra","Feyza","Bahattin",
	"Akif","Yusuf","Yasir","Yavuz" };		//rastgele atanacak isimlerin dizisi
string ogrSoyad[30] = { "Arslan","Karamete","Geylani","Ceyhan","Ayhan","Akkoyun","Akkor","Aksakal","Karasakal","Cabar","Yaman","Bademci","Ekici","Ersan","Kol","Kandemir","Saray","Kara","Aslan","Aksaray","Ergin","Acer",
"Okur","Olgun","Alemdar","Selek","Turan","Serter","Sertan","Karakoyun" };		//rastgele atanacak soyisimlerin dizisi
float EnBuyuk = 0, EnKucuk = 999, AltSinir, UstSinir, yilİci, SinifinOrtalamasi, BasariNotu[100];		//degisken tanimlamalari
int islem, DegiskenMevcut;
const int Mevcut = 100;
char karar{}, secim{}, HarfNo[2] = { 'B','G' }, HarfNumara[Mevcut], kararK{};
ogrBilgi sinif[100];		//sturct sinif dizisi tanimlamasi
string HarfNotu[100];		//harf notu icin dizi tanimlama
void rastgele_ogr_atama(); //Rastgele ogrenci atamak icin tanimlanan fonksiyon
void elle_ogr_atama();		//Elle ogrenci atamak icin tanimlanan fonksiyon
void ElleNotOrtHesabi();	//Elle girilen not bilgileriyle sinifin not ortalamasi hesabi icin tanimlanan fonksiyon
void ElleYuksekNotHesabi(); //Elle girilen not bilgileriyle en yuksek basari notununun yazdirilmasi icin tanimlanan fonksiyon
void ElleDusukNotHesabi();	//Elle girilen not bilgileriyle en dusuk basari notununun yazdirilmasi icin tanimlanan fonksiyon
void ElleStandartSapmaHesabi();	//Standart sapmanin hesaplanip yazdirilmasi icin tanimlanan fonksiyon
void ElleNotAltiList();		//Belirli bir notun altindaki ogrencilerin liste halinde yazdirilmasi icin		
void rastgele_sinif_listesi();		//Rastgele atanan ogrenci bilgilerinin liste biciminde yazdirilmasi icin tanimlanan fonksiyon
void elle_sinif_listesi();		//Elle girilen ogrenci bilgilerinin liste biciminde yazdirilmasi icin tanimlanan fonksiyon
void YuksekNotHesabi();			//Rastgele atanan ogrenci bilgileriyle en yuksek basari notununun yazdirilmasi icin tanimlanan fonksiyon
void DusukNotHesabi();			//Rastgele atanan ogrenci bilgileriyle en dusuk basari notununun yazdirilmasi icin tanimlanan fonksiyon
void NotOrtHesabi();		//Rastgele atanan ogrenci bilgileriyle sinifin not ortalamasi hesabi icin tanimlanan fonksiyon
void StandartSapmaHesabi();		//Rastgele atanan ogrenci bilgileriyle standart sapmanin hesaplanip yazdirilmasi icin tanimlanan fonksiyon
void NotAraligiList();		//Belirli not araligindaki ogrencilerin liste halinde yazdirilmasi icin
void NotUstuList();		//Belirli bir notun ustundeki ogrencilerin liste halinde yazdirilmasi icin
void NotAltiList();		//Belirli bir notun altindaki ogrencilerin liste halinde yazdirilmasi icin
int main()
{
	cout << "Ogrenci Bilgi Sistemine hosgeldiniz!" << endl;
	cout << "Bilgilerin rastgele atanmasi icin 'r/R' yi;kullanici girisli olmasi icin 'k/K' yi tuslayiniz." << endl;
	cin >> secim; //Rastgele veya kullanici girisli olmasi icin kullanici secim yapar
	if (secim == 'r' || secim == 'R') //rastgele secenegi
	{
		rastgele_ogr_atama(); //tanimlanan fonksiyon araciligiyla ogrencileri atama
		do	//do while dongusu ile kullanici isterse menuye donus saglanir
		{
			system("CLS"); //Onceden yazdirilan her seyi siler
			cout << "Menuye hosgeldiniz.Lutfen yapmak istediginiz islemi seciniz.(1,2,3,4,5,6,7,8)" << endl;  //Menu Ekrani
			cout << "1. Sinifin listesini yazdir." << endl;
			cout << "2. Sinifin en yuksek notunu hesapla." << endl;
			cout << "3. Sinifin en dusuk notunu hesapla." << endl;
			cout << "4. Sinifin ortalamasini hesapla." << endl;
			cout << "5. Sinifin standart sapmasini hesapla." << endl;
			cout << "6. Basari notu belirli bir aralikta olan ogrencileri listele." << endl;
			cout << "7. Basari notu belirli bir degerin altinda olan ogrencileri listele." << endl;
			cout << "8. Basari notu belirli bir degerin ustunde olan ogrencileri listele." << endl;
			cin >> islem;	//kullanici hangi maddeye gidecegini secer
			if (islem == 1)		//if-else if yapisiyla hangi islem gerceklestirilecekse onun gerceklesmesi saglanir
			{
				rastgele_sinif_listesi(); //tanimlanan fonksiyon araciligiyla sinif listesi yazdirilir
			}
			else if (islem == 2)	
			{
				YuksekNotHesabi();		//tanimlanan fonksiyon araciligiyla en yuksek not yazdirilir
			}
			else if (islem == 3)
			{
				DusukNotHesabi();	//tanimlanan fonksiyon araciligiyla dusuk not yazdirilir
			}
			else if (islem == 4)
			{
				NotOrtHesabi();		//tanimlanan fonksiyon araciligiyla sinifin not ortalamasi hesaplanip yazdirilir
			}
			else if (islem == 5)	
			{
				StandartSapmaHesabi();	//tanimlanan fonksiyon araciligiyla standart sapma hesaplanip yazdirilir
			}
			else if (islem == 6)
			{
				NotAraligiList();	//tanimlanan fonksiyon araciligiyla kullanici tarafindan belirlenen not araligindaki ogrenciler yazdirilir
			}
			else if (islem == 7)
			{
				NotAltiList();		//tanimlanan fonksiyon araciligiyla kullanici tarafindan belirlenen notun altindaki ogrenciler yazdirilir
			}
			else if (islem == 8)
			{
				NotUstuList();		//tanimlanan fonksiyon araciligiyla kullanici tarafindan belirlenen notun ustundeki ogrenciler yazdirilir
			}
		} while (karar == 'e' || karar == 'E');
	}
	if (secim == 'k' || secim == 'K') //kullanici girisi secenegi
	{
		cout << "#ELLE GIRIS SISTEMINE HOSGELDINIZ.#" << endl;
		elle_ogr_atama(); //Kullanici bilgileri elle girer.Girilen notlarla basari notu hesabi yapilir.Hangi harf notuna karsilik geldigi belirlenir.
		do //Do while dongusu ile kullanici isterse menuye donus saglanir
		{
			system("CLS");
			cout << "Menuye hosgeldiniz.Lutfen yapmak istediginiz islemi seciniz.(1,2,3,4,5,6,7,8)" << endl;
			cout << "1. Sinifin listesini yazdir." << endl;
			cout << "2. Sinifin en yuksek notunu hesapla." << endl;
			cout << "3. Sinifin en dusuk notunu hesapla." << endl;
			cout << "4. Sinifin ortalamasini hesapla." << endl;
			cout << "5. Sinifin standart sapmasini hesapla." << endl;
			cout << "6. Basari notu belirli bir aralikta olan ogrencileri listele." << endl;
			cout << "7. Basari notu belirli bir degerin altinda olan ogrencileri listele." << endl;
			cout << "8. Basari notu belirli bir degerin ustunde olan ogrencileri listele." << endl;
			cin >> islem; //kullanici hangi maddeye gidecegini secer
			if (islem == 1)		//if-else if yapisiyla hangi islem gerceklestirilecekse onun gerceklesmesi saglanir
			{
				elle_sinif_listesi(); //  girilen bilgiler liste halinde yazdirilir
			}
			else if (islem == 2)
			{
				ElleYuksekNotHesabi(); // basari notlari karsilastirilarak sinifin en yuksek notu yazdirilir
			}
			else if (islem == 3)
			{
				ElleDusukNotHesabi(); //sinifin en dusuk notu yazdirilir
			}
			else if (islem == 4)
			{
				ElleNotOrtHesabi();	//sinifin not ortalamasi hesaplanip yazdirilir
			}
			else if (islem == 5)
			{
				ElleStandartSapmaHesabi(); //Standart sapma hesaplanarak yazdirilir
			}
			else if (islem == 6)
			{
				NotAraligiList(); //Kullanici tarafindan belirlenen not araligindaki ogrenciler yazdirilir
			}
			else if (islem == 7)
			{
				
				ElleNotAltiList();  //Kullanici tarafindan belirlenen notun altindaki ogrenciler yazdirilir
			}
			else if (islem == 8)
			{
				NotUstuList();	//Kullanici tarafindan belirlenen notun ustundeki ogrenciler yazdirilir
			}
		} while (karar == 'e' || karar == 'E');		//fonksiyonlarin her birinde kullaniciya menuye donmek istegi sorulur.Cevap olumlu olursa menuye donus yapilir
	}
}
void rastgele_ogr_atama()
{
	srand(time(NULL));		//her seferinde farkli yazdirmak icin
	for (int i = 0; i < Mevcut; i++)	 //for dongusuyle 100 ogrencinin not bilgileri,dogum tarihleri random atanir
	{
		sinif[i].ad = ogrAd[rand() % 30];	//adlar random atanir
		sinif[i].soyad = ogrSoyad[rand() % 30];		//soyadlar random atanir
		if (i < 10)		//Ogrencilerin %10 una 0-40 arasında rastgele not atanır		//if-else if yapisiyla belirli yüzdeliklerde ogrencilere belirli not araliginda notlar rastgele atanir
		{
			sinif[i].vize = rand() % 41;
			sinif[i].kisaSinav1 = rand() % 41;
			sinif[i].kisaSinav2 = rand() % 41;
			sinif[i].odev1 = rand() % 41;
			sinif[i].odev2 = rand() % 41;
			sinif[i].proje = rand() % 41;
			sinif[i].final = rand() % 41;
		}
		else if (i < 60)	//Ogrencilerin %50 sine 40-70 arasında rastgele not atanır
		{
			sinif[i].vize = rand() % 31 + 40;
			sinif[i].kisaSinav1 = rand() % 31 + 40;
			sinif[i].kisaSinav2 = rand() % 31 + 40;
			sinif[i].odev1 = rand() % 31 + 40;
			sinif[i].odev2 = rand() % 31 + 40;
			sinif[i].proje = rand() % 31 + 40;
			sinif[i].final = rand() % 31 + 40;
		}
		else if (i < 75)	//Ogrencilerin %15 ine  70-80 arasında rastgele not atanır
		{
			sinif[i].vize = rand() % 11 + 70;
			sinif[i].kisaSinav1 = rand() % 11 + 70;
			sinif[i].kisaSinav2 = rand() % 10 + 70;
			sinif[i].odev1 = rand() % 11 + 70;
			sinif[i].odev2 = rand() % 11 + 70;
			sinif[i].proje = rand() % 11 + 70;
			sinif[i].final = rand() % 11 + 70;
		}
		else	//Ogrencilerin %25 ine  80-100 arasında rastgele not atanır
		{
			sinif[i].vize = rand() % 21 + 80;
			sinif[i].kisaSinav1 = rand() % 20 + 80;
			sinif[i].kisaSinav2 = rand() % 20 + 80;
			sinif[i].odev1 = rand() % 21 + 80;
			sinif[i].odev2 = rand() % 21 + 80;
			sinif[i].proje = rand() % 21 + 80;
			sinif[i].final = rand() % 21 + 80;
		}
		yilİci = sinif[i].vize * 0.5 + sinif[i].kisaSinav1 * 0.07 + sinif[i].kisaSinav2 * 0.07 + sinif[i].odev1 * 0.1 + sinif[i].odev2 * 0.1 + sinif[i].proje * 0.16;  //Yil ici notu hesaplaniyor
		BasariNotu[i] = yilİci * 0.55 + sinif[i].final * 0.45;	//Basari notu hesaplaniyor
		HarfNumara[i] = HarfNo[rand() % 2];		//rastgele harf no ataniyor.(B veye G)
		sinif[i].numara = rand() % 100 + 1;	 //rastgele numara ataniyor (1-100 arasi)
		sinif[i].DogumTarihi.gun = rand() % 30 + 1; //rastgele dogum tarihi ataniyor
		sinif[i].DogumTarihi.ay = rand() % 12 + 1;
		sinif[i].DogumTarihi.yil = rand() % 5 + 2000;
		if (BasariNotu[i] >= 90)	//Basari notuna karsilik gelen harf notu bulunuyor	//if-else if yapisiyla basari notuna karsilik gelen harf notu belirlenir
		{
			HarfNotu[i] = "AA";
		}
		else if (BasariNotu[i] >= 85)
		{
			HarfNotu[i] = "BA";
		}
		else if (BasariNotu[i] >= 80)
		{
			HarfNotu[i] = "BB";
		}
		else if (BasariNotu[i] >= 70)
		{
			HarfNotu[i] = "CB";
		}
		else if (BasariNotu[i] >= 60)
		{
			HarfNotu[i] = "CC";
		}
		else if (BasariNotu[i] >= 55)
		{
			HarfNotu[i] = "DC";
		}
		else if (BasariNotu[i] >= 50)
		{
			HarfNotu[i] = "DD";
		}
		else if (BasariNotu[i] >= 40)
		{
			HarfNotu[i] = "FD";
		}
		else
		{
			HarfNotu[i] = "FF";
		}
	}
}
void rastgele_sinif_listesi()	
{
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle degerler yazdiriliyor
	{
		cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNumara[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(13) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		if (i == 19)		//if-else if yapisiyla atanan degerler 20 serli gruplar halinde liste biciminde ekrana yazdiriliyor
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 39)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 59)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 79)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl; 
	cin >> karar;
	system("CLS");
}
void YuksekNotHesabi()
{
	system("CLS");
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle notlar karsilastirilip en buyuk not hesaplaniyor
	{
		if (BasariNotu[i] > EnBuyuk)	//if yapisiyla en buyuk not hesaplaniyor
		{
			EnBuyuk = BasariNotu[i];
		}
	}
	cout << "Sinifin en yuksek notu: " << EnBuyuk << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
	system("CLS");
}
void DusukNotHesabi()
{
	system("CLS");
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle notlar karsilastirilip en kucuk not hesaplaniyor
	{
		if (BasariNotu[i] < EnKucuk)	//if yapisiyla en kucuk not hesaplaniyor
		{
			EnKucuk = BasariNotu[i];
		}
	}
	cout << "Sinifin en dusuk notu: " << EnKucuk << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void NotOrtHesabi()
{
	float NotToplami = 0;
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle basari notlari toplanip sinifin ortalamasi hesaplaniyor
	{
		NotToplami += BasariNotu[i]; 
	}
	SinifinOrtalamasi = NotToplami / Mevcut;
	system("CLS");
	cout << "Sinifin ortalamasi: " << SinifinOrtalamasi << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void StandartSapmaHesabi()
{
	system("CLS");
	float Varyans, Ortalama_Farki[Mevcut], OrtalamaFarki_Kare[Mevcut], toplamKare = 0, StandartSapma;
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle standart sapma hesaplaniyor
	{
		Ortalama_Farki[i] = SinifinOrtalamasi - BasariNotu[i];
		OrtalamaFarki_Kare[i] = pow(Ortalama_Farki[i], 2);
		toplamKare += OrtalamaFarki_Kare[i];
	}
	Varyans = toplamKare / Mevcut - 1;
	StandartSapma = sqrt(Varyans);
	cout << "Standart Sapma: " << StandartSapma << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void NotAraligiList()
{
	system("CLS");
	cout << "Hangi degerin ustunde olan notlari gormek istiyorsunuz?" << endl;
	cin >> AltSinir;
	cout << "Hangi degerin altinda olan notlari gormek istiyorsunuz?" << endl;
	cin >> UstSinir;
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < Mevcut; i++) //for dongusuyle kullanicinin girdigi deger araliginda olan notlar listeleniyor
	{
		if (AltSinir <= BasariNotu[i] && BasariNotu[i] <= UstSinir)		//if yapisiyla kullanicinin belirttigi araliga gore yazdirma islemi yapiliyor
		{
			cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNumara[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(12) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void NotAltiList()
{
	system("CLS");
	cout << "Basari notu hangi degerin altinda olan ogrencileri goruntulemek istiyorsunuz?Lutfen ust sinir girin." << endl;
	cin >> UstSinir;
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle kullanicinin girdigi degerden dusuk notlar listeleniyor
	{
		if (BasariNotu[i] <= UstSinir)		//if yapisiyla kullanicinin belirttigi araliga gore yazdirma islemi yapiliyor
		{
			cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNumara[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(12) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void NotUstuList()
{
	system("CLS");
	cout << "Basari notu hangi degerin ustunde olan ogrencileri goruntulemek istiyorsunuz?Lutfen alt sinir girin." << endl;
	cin >> AltSinir;
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < Mevcut; i++)	//for dongusuyle kullanicinin girdigi degerden yuksek notlar listeleniyor
	{
		if (BasariNotu[i] >= AltSinir)		//if yapisiyla kullanicinin belirttigi araliga gore yazdirma islemi yapiliyor
		{
			cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNumara[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(13) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void elle_ogr_atama()
{
	cout << "Kac ogrenci girmek istiyorsunuz?" << endl;
	cin >> DegiskenMevcut;	//Kullanici girilecek ogrenci sayisini belirliyor
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle kullanicinin belirttigi sayida ogrencinin bilgisi aliniyor.
	{
		cout << i + 1 << ". ogrencinin bilgilerini girin." << endl;
		cout << "Ogrencinin adi: " << endl;
		cin >> sinif[i].ad;
		cout << "Ogrencinin soyadi: " << endl;
		cin >> sinif[i].soyad;
		do	//do while ile girilen gun ve ay verilerinin dogrulugu denetleniyor
		{
			cout << "Ogrencinin dogum tarihini giriniz.Gunun 30 ve ayin en fazla 12 olmasi gerektigini unutmayiniz.(gun.ay.yil) " << endl;
			cin >> sinif[i].DogumTarihi.gun >> sinif[i].DogumTarihi.ay >> sinif[i].DogumTarihi.yil;
		} while (!(sinif[i].DogumTarihi.gun < 31 && sinif[i].DogumTarihi.gun>0 && sinif[i].DogumTarihi.ay > 0 && sinif[i].DogumTarihi.ay < 13));
		do	//do while ile girile harf numarasinin dogrulugu denetleniyor
		{
			cout << "Harf numarasini girin.(B,G)" << endl;
			cin >> HarfNo[i];
		} while (!(HarfNo[i] == 'B' || HarfNo[i] == 'G'));
		do	//do while ile girilen numaranin dogrulugu denetleniyor
		{
			cout << "Numaranin sayi kismini girin(Yerlestirme sirasina gore 1-100 arasi)" << endl;
			cin >> sinif[i].numara;
		} while (!(sinif[i].numara >= 1 && sinif[i].numara <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "Vize notu(0-100 arasi): " << endl;
			cin >> sinif[i].vize;
		} while (!(sinif[i].vize >= 0 && sinif[i].vize <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "1. Kisa Sinav notu(0-100 arasi): " << endl;
			cin >> sinif[i].kisaSinav1;
		} while (!(sinif[i].kisaSinav1 >= 0 && sinif[i].kisaSinav1 <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "2. Kisa Sinav notu(0-100 arasi): " << endl;
			cin >> sinif[i].kisaSinav2;
		} while (!(sinif[i].kisaSinav2 >= 0 && sinif[i].kisaSinav2 <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "1. Odev notu(0-100 arasi): " << endl;
			cin >> sinif[i].odev1;
		} while (!(sinif[i].odev1 >= 0 && sinif[i].odev1 <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "2. Odev notu(0-100 arasi): " << endl;
			cin >> sinif[i].odev2;;
		} while (!(sinif[i].odev2 >= 0 && sinif[i].odev2 <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "Proje notu(0-100 arasi): " << endl;
			cin >> sinif[i].proje;
		} while (!(sinif[i].proje >= 0 && sinif[i].proje <= 100));
		do	//do while ile girilen notun dogrulugu denetleniyor
		{
			cout << "Final notu(0-100 arasi): " << endl;
			cin >> sinif[i].final;
		} while (!(sinif[i].final >= 0 && sinif[i].final <= 100));
		yilİci = sinif[i].vize * 0.5 + sinif[i].kisaSinav1 * 0.07 + sinif[i].kisaSinav2 * 0.07 + sinif[i].odev1 * 0.1 + sinif[i].odev2 * 0.1 + sinif[i].proje * 0.16;	//yil ici notu hesaplaniyor
		BasariNotu[i] = yilİci * 0.55 + sinif[i].final * 0.45;	//Basari notu hesaplaniyor
		if (BasariNotu[i] >= 90)	//if-else if yapisiyla basari notuna karsilik gelen harf notu belirleniyor
		{
			HarfNotu[i] = "AA";
		}
		else if (BasariNotu[i] >= 85)
		{
			HarfNotu[i] = "BA";
		}
		else if (BasariNotu[i] >= 80)
		{
			HarfNotu[i] = "BB";
		}
		else if (BasariNotu[i] >= 70)
		{
			HarfNotu[i] = "CB";
		}
		else if (BasariNotu[i] >= 60)
		{
			HarfNotu[i] = "CC";
		}
		else if (BasariNotu[i] >= 55)
		{
			HarfNotu[i] = "DC";
		}
		else if (BasariNotu[i] >= 50)
		{
			HarfNotu[i] = "DD";
		}
		else if (BasariNotu[i] >= 40)
		{
			HarfNotu[i] = "FD";
		}
		else
		{
			HarfNotu[i] = "FF";
		}
	}
}
void elle_sinif_listesi()	
{
	system("CLS");
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle atanan degerler yazdiriliyor
	{
		cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNo[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(13) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		if (i == 19)	//if yapisiyla 20 serli listeler seklinde yazdiriliyor
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 39)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 59)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
		if (i == 79)
		{
			system("pause");
			system("CLS");
			cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
	system("CLS");
}
void ElleYuksekNotHesabi() 
{
	system("CLS");
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle elle girilen basari notlari karsilastirilip en yuksek not bulunuyor
	{
		if (BasariNotu[i] > EnBuyuk)	//if yapisiyla en buyuk not belirleniyor
		{
			EnBuyuk = BasariNotu[i];
		}
	}
	cout << "Sinifin en yuksek notu: " << EnBuyuk << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
	system("CLS");
}
void ElleDusukNotHesabi()
{
	system("CLS");
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle elle girilen basari notlari karsilastirilip en kucuk not bulunuyor ve yazdiriliyor
	{
		if (BasariNotu[i] < EnKucuk)	//if yapisiyla en buyuk not belirleniyor
		{
			EnKucuk = BasariNotu[i];
		}
	}
	cout << "Sinifin en dusuk notu: " << EnKucuk << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void ElleNotOrtHesabi()
{
	float NotToplami = 0;
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle elle girilen basari notlarinin ortalamasi aliniyor
	{
		NotToplami += BasariNotu[i];
	}
	SinifinOrtalamasi = NotToplami / DegiskenMevcut;
	system("CLS");
	cout << "Sinifin ortalamasi: " << SinifinOrtalamasi << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void ElleStandartSapmaHesabi()
{
	system("CLS");
	float Varyans, Ortalama_Farki[Mevcut], OrtalamaFarki_Kare[Mevcut], toplamKare = 0, StandartSapma;
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle standart sapma hesaplaniyor
	{
		if (DegiskenMevcut==1)
		{
			cout << "Hesaplanamaz!";
			break;
		}
		Ortalama_Farki[i] = SinifinOrtalamasi - BasariNotu[i];
		OrtalamaFarki_Kare[i] = pow(Ortalama_Farki[i], 2);
		toplamKare += OrtalamaFarki_Kare[i];
	}
	Varyans = toplamKare / DegiskenMevcut - 1;
	StandartSapma = sqrt(Varyans);
	cout << "Standart Sapma: " << StandartSapma << endl;
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}
void ElleNotAltiList()
{
	system("CLS");
	cout << "Basari notu hangi degerin altinda olan ogrencileri goruntulemek istiyorsunuz?Lutfen ust sinir girin." << endl;
	cin >> UstSinir;
	cout << left << setw(11) << "AD" << setw(13) << "SOYAD" << "DOGUM TARIHI" << "\t" << setw(15) << "NUMARASI" << "VIZE" << "\t" << "KISA SINAV1" << "\t" << "KISA SINAV2" << "\t" << "ODEV1" << "\t" << "ODEV2" << "\t" << "PROJE" << "\t" << "FINAL" << "\t" << setw(12) << "BASARI NOTU" << "HARF NOTU" << endl;
	for (int i = 0; i < DegiskenMevcut; i++)	//for dongusuyle kullanicinin girdigi degerden dusuk notlar listeleniyor
	{
		if (BasariNotu[i] <= UstSinir)		//if yapisiyla kullanicinin belirttigi araliga gore yazdirma islemi yapiliyor
		{
			cout << left << setw(11) << sinif[i].ad << setw(13) << sinif[i].soyad << sinif[i].DogumTarihi.gun << "." << sinif[i].DogumTarihi.ay << "." << sinif[i].DogumTarihi.yil << "\t" << HarfNumara[i] << "2212100" << sinif[i].numara << "\t" << setw(12) << sinif[i].vize << setw(16) << sinif[i].kisaSinav1 << setw(14) << sinif[i].kisaSinav2 << setw(8) << sinif[i].odev1 << setw(8) << sinif[i].odev2 << setw(7) << sinif[i].proje << setw(11) << sinif[i].final << setw(12) << BasariNotu[i] << HarfNotu[i] << endl << endl;
		}
	}
	cout << "Menuye donmek istiyorsaniz e'ye istemiyorsaniz herhangi bir tusa basin." << endl;
	cin >> karar;
}