/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Uzay Araçları ile ilgili bilgilerin tanımlandığı yer bu sınıftır. 
* </p> 
*/ 

package paket;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.time.temporal.ChronoUnit;

public class UzayAraci {
    private String adi;
    private String cikisGezegeni;
    private String varisGezegeni;
    private LocalDate cikisTarih;
    private long mesafeSaat;
    private long kalanSaat;
    private boolean yolda = false;
    private boolean imha  = false;
    private List<Kisi> yolcular = new ArrayList<>();

    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("d.M.yyyy");

    public UzayAraci(String satir) {
        String[] p = satir.split("#");
        this.adi           = p[0];
        this.cikisGezegeni = p[1];
        this.varisGezegeni = p[2];
        this.cikisTarih    = LocalDate.parse(p[3], FMT);
        this.mesafeSaat    = Long.parseLong(p[4]);
        this.kalanSaat     = mesafeSaat;
    }

    public String getAdi()              { return adi; }
    public String getCikisGezegeni()    { return cikisGezegeni; }
    public String getVarisGezegeni()    { return varisGezegeni; }
    public boolean isYolda()            { return yolda; }
    public boolean isImha()             { return imha; }
    public long getKalanSaat()          { return imha ? -1 : kalanSaat; }
    public LocalDate getCikisTarih()    { return cikisTarih; }
    public List<Kisi> getYolcular()     { return yolcular; }

    public void kisiEkle(Kisi k) {
        yolcular.add(k);
    }

    public void kalkisiBaslat(LocalDate gezegenTarihi) {
        if (!yolda && !imha && gezegenTarihi.isEqual(cikisTarih)) {
            yolda = true;
        }
    }

    public void saatGecir() {
        if (yolda && !imha && kalanSaat > 0) {
            kalanSaat--;
            yolcular.forEach(Kisi::yasamSaatiAzalt);
            yolcular.removeIf(Kisi::olduMu);
            if (yolcular.isEmpty()) imha = true;
        }
    }

    public boolean varisYaptiMi() {
        return yolda && !imha && kalanSaat == 0;
    }

    public LocalDate getVarisTarihi(Gezegen departure, Gezegen varisPlanet) {
        long daysToDep = ChronoUnit.DAYS.between(
            departure.getBaslangicTarih(),
            this.cikisTarih
        );
        int depDayHours = departure.getZaman().getGunSaatSayisi();
        long hoursToDep = daysToDep * depDayHours;

        long totalHours = hoursToDep + mesafeSaat;

        int destDayHours = varisPlanet.getZaman().getGunSaatSayisi();
        long daysOnDest = totalHours / destDayHours;

        return varisPlanet.getBaslangicTarih().plusDays(daysOnDest);
    }
    
    public void checkPreLaunch() {
        if (!yolda && !imha && yolcular.isEmpty()) {
            imha = true;
        }
    }
}
