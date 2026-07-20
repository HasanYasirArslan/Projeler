/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Zaman yönetimi bu sınıfta yapılır. 
* </p> 
*/ 

package paket;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Zaman {
    private LocalDate tarih;
    private int saat;              
    private int gunSaatSayisi;     
    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("d.M.yyyy");

    public Zaman(String baslangicTarihStr, int gunSaatSayisi) {
        this.tarih = LocalDate.parse(baslangicTarihStr, FMT);
        this.saat = 0;
        this.gunSaatSayisi = gunSaatSayisi;
    }

    public void saatArttir() {
        saat++;
        if (saat >= gunSaatSayisi) {
            saat = 0;
            tarih = tarih.plusDays(1);
        }
    }

    public LocalDate getTarih() {
        return tarih;
    }

    public String getTarihStr() {
        return tarih.format(FMT);
    }

    public int getSaat() {
        return saat;
    }

    public int getGunSaatSayisi() {
        return gunSaatSayisi;
    }

    @Override
    public String toString() {
        return String.format("%s %02d:00", getTarihStr(), saat);
    }
}
