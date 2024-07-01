/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI…...: 2
**				ÖĞRENCİ ADI...............: Hasan
**				ÖĞRENCİ NUMARASI.: B221210096
**				DERS GRUBU…………: A
****************************************************************************/

using namespace std;
#include<cmath>
#include<iostream>
class Karmasik
{
private:
	float reel, sanal;
public:
	Karmasik() :reel(0), sanal(0)
	{ }
	void VeriGirisi()
	{
		cout << "Lutfen sayinin sirasiyla reel ve sanal kisimlarini girin\n";
		cin >> reel >> sanal;
	}
	Karmasik operator +(Karmasik k2)
	{
		Karmasik temp;
		temp.reel = reel + k2.reel;
		temp.sanal = sanal + k2.sanal;
		return temp;
	}
	Karmasik operator -(Karmasik k2)
	{
		Karmasik temp;
		temp.reel = reel - k2.reel;
		temp.sanal = sanal - k2.sanal;
		return temp;
	}
	Karmasik operator *(Karmasik k2)
	{
		Karmasik temp;
		temp.reel = reel * k2.reel - sanal * k2.sanal;
		temp.sanal = reel * k2.sanal + sanal * k2.reel;
		return temp;
	}
	Karmasik operator/(Karmasik k2)
	{
		Karmasik temp;
		temp.reel = (reel * k2.reel + sanal * k2.sanal) / (pow(k2.reel, 2) + pow(k2.sanal, 2));
		temp.sanal = (sanal * k2.reel - reel * k2.sanal) / (pow(k2.reel, 2) + pow(k2.sanal, 2));
		return temp;
	}
	void yazdir()
	{
		if (sanal<0)
		{
			cout << "Yazdirilan karmasik sayi: " << reel << sanal << "i";
		}
		else if (sanal==0)
		{
			cout << "Yazdirilan karmasik sayi: " << reel;
		}
		else
		{
			cout << "Yazdirilan karmasik sayi: " << reel << "+" << sanal << "i";
		}
	}
	void yazdirKutupsal()
	{
		float r;
		r=sqrt(pow(reel, 2) + pow(sanal, 2));

		if (acos(reel / r) * 180 / 3.1416 < 90 && asin(sanal / r) * 180 / 3.1416 < 90)
			cout << r << " * (cos" << (acos(reel / r) * 180 / 3.1416) << " + " << "sin" << (asin(sanal / r) * 180 / 3.1416) << "i)" << endl;
		else if (acos(reel / r) * 180 / 3.1416 < 90 && asin(sanal / r) * 180 / 3.1416 > 90 && asin(sanal / r) * 180 / 3.1416 < 180)
			cout << r << " * (cos" << (acos(reel / r) * 180 / 3.1416) << " + " << "sin" << (asin(sanal / r) * 180 / 3.1416) - 90 << "i)" << endl;
		else if (acos(reel / r) * 180 / 3.1416 > 90 && acos(reel / r) * 180 / 3.1416 < 180 && asin(sanal / r) * 180 / 3.1416 < 90)
			cout << r << " * (cos" << (acos(reel / r) * 180 / 3.1416) - 90 << " + " << "sin" << (asin(sanal / r) * 180 / 3.1416) << "i)" << endl;
		else if (acos(reel / r) * 180 / 3.1416 > 180 && asin(sanal / r) * 180 / 3.1416 > 180)
		{
			int tamdegercos, tamdegersin;
			tamdegercos = ((acos(reel / r) * 180 / 3.1416) / 90);
			tamdegersin = ((asin(sanal / r) * 180 / 3.1416) / 90);
			cout << r << " * (cos" << (acos(reel / r) * 180 / 3.1416) - (90 * tamdegercos) << " + " << "sin" << (asin(sanal / r) * 180 / 3.1416) - (90 * tamdegersin) << "i)" << endl;
		}
	}
};
int main()
{
	Karmasik k1, k2, sonuc;
	char karar;
	cout << "Ilk karmasik sayiyi girin\n";
	k1.VeriGirisi();
	cout << "Hangi islemi uygulamak istiyorsunuz?(+,-,*,/) veya Kutupsal Gosterim(k,K)";
	cin >> karar;
	if (karar=='+'||karar=='-'||karar=='*'||karar=='/')
	{
		cout << "Ikinci karmasik sayiyi girin\n";
		k2.VeriGirisi();
	}
	if (karar=='+')
	{
		sonuc = k1 + k2;
		sonuc.yazdir();
	}
	else if (karar=='-')
	{
		sonuc = k1 - k2;
		sonuc.yazdir();
	}
	else if (karar=='*')
	{
		sonuc= k1 * k2;
		sonuc.yazdir();
	}
	else if (karar=='/')
	{
		sonuc = k1 / k2;
		sonuc.yazdir();
	}
	else if(karar=='k'||karar=='K')
	{
		sonuc = k1;
		sonuc.yazdirKutupsal();
	}
}

