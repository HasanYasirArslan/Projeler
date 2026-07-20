/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Gezegen bilgileri ve özellikleri bu sınıfta yer alır. 
* </p> 
*/ 

package paket;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class Gezegen {
    private String adi;
    private Zaman zaman;
    private List<Kisi> populasyon = new ArrayList<>();

    private LocalDate baslangicTarih;

    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("d.M.yyyy");

    public Gezegen(String adi, int gunSaatSayisi, String baslangicTarihStr) {
        this.adi = adi;
        this.baslangicTarih = LocalDate.parse(baslangicTarihStr, FMT);
        this.zaman = new Zaman(baslangicTarihStr, gunSaatSayisi);
    }

    public String getAdi() { return adi; }
    public Zaman getZaman() { return zaman; }
    public int getPopulasyon() { return populasyon.size(); }

    public void kisiEkle(Kisi k) {
        if (!k.olduMu()) populasyon.add(k);
    }

    public void kisiCikar(Kisi k) {
        populasyon.remove(k);
    }

    public void guncelleSaat() {
        zaman.saatArttir();

        Iterator<Kisi> it = populasyon.iterator();
        while (it.hasNext()) {
            Kisi k = it.next();
            k.yasamSaatiAzalt();
            if (k.olduMu()) {
                it.remove();
            }
        }
    }

    public LocalDate getBaslangicTarih() {
        return baslangicTarih;
    }
    @Override
    public String toString() {
        return String.format("%s %s  Pop=%d",
                             adi,
                             zaman.toString(),
                             getPopulasyon());
    }
}
