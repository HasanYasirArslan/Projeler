/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Simulasyonun gerçeklendiği yer bu sınıftır. 
* </p> 
*/ 

package paket;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class Simulasyon {
    private List<Gezegen> gezegenler;
    private List<UzayAraci> araclar;
    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("dd.MM.yyyy");

    public Simulasyon() throws IOException {
        gezegenler = DosyaOkuma.gezegenleriOku("dist/Gezegenler.txt");
        araclar    = DosyaOkuma.araclariOku   ("dist/Araclar.txt");

        Map<String, UzayAraci> mapA = new HashMap<>();
        for (UzayAraci a : araclar) {
            mapA.put(a.getAdi(), a);
        }

        for (String satir : Files.readAllLines(Paths.get("dist/Kisiler.txt"))) {
            if (satir.isBlank()) continue;
            String[] p = satir.split("#");
            Kisi k = new Kisi(p[0],
                              Integer.parseInt(p[1]),
                              Long.parseLong(p[2]));
            UzayAraci arac = mapA.get(p[3]);
            if (arac != null) {
                arac.kisiEkle(k);
                Gezegen origin = findGezegen(arac.getCikisGezegeni());
                origin.kisiEkle(k);
            }
        }
    }

    public void calistir() {
        while (true) {
            for (Gezegen g : gezegenler) {
                g.guncelleSaat();
            }

            for (UzayAraci a : araclar) {
                Gezegen origin = findGezegen(a.getCikisGezegeni());
                LocalDate now   = origin.getZaman().getTarih();

                if (!a.isYolda() && !a.isImha()) {
                	Iterator<Kisi> it = a.getYolcular().iterator();
                    while (it.hasNext()) {
                        Kisi k = it.next();
                        if (k.olduMu()) {
                            it.remove();
                        }
                    }
                    a.checkPreLaunch();
                }

                boolean departing = !a.isYolda()
                                 && !a.isImha()
                                 && now.isEqual(a.getCikisTarih());
                a.kalkisiBaslat(now);
                if (departing && a.isYolda()) {
                    for (Kisi k : a.getYolcular()) {
                        origin.kisiCikar(k);
                    }
                }

                a.saatGecir();

                if (a.varisYaptiMi() && !a.getYolcular().isEmpty()) {
                    Gezegen hedef = findGezegen(a.getVarisGezegeni());
                    for (Kisi k : a.getYolcular()) {
                        hedef.kisiEkle(k);
                    }
                    a.getYolcular().clear();
                }
            }

            clearConsole();
            yazdir();

            boolean tamam = araclar.stream()
                                   .allMatch(ar -> ar.isImha() || ar.varisYaptiMi());
            if (tamam) break;

            sleep(100);
        }
        yazdir();
    }

    private Gezegen findGezegen(String adi) {
        return gezegenler.stream()
                         .filter(g -> g.getAdi().equals(adi))
                         .findFirst()
                         .orElseThrow(() ->
                             new IllegalArgumentException("Gezegen bulunamadı: " + adi));
    }

    private void yazdir() {
        System.out.println("Gezegenler:");
        System.out.print("          ");
        for (Gezegen g : gezegenler) {
            System.out.printf("          --- %s ---", g.getAdi());
        }
        System.out.println();

        System.out.print("Tarih               ");
        for (Gezegen g : gezegenler) {
            System.out.printf("%-19s", g.getZaman().getTarihStr());
        }
        System.out.println();

        System.out.print("Nüfus                  ");
        for (Gezegen g : gezegenler) {
            System.out.printf("%-19d", g.getPopulasyon());
        }
        System.out.println("\n");

        System.out.println("Uzay Araçları:");
        System.out.printf("%-20s %-15s %-11s %-18s %-33s %s%n",
                          "Araç Adı", "Durum", "Çıkış", "Varış",
                          "Hedefe Kalan Saat", "Hedefe Varacağı Tarih");
        for (UzayAraci a : araclar) {
            String durum = a.isImha()      ? "İmha"
                         : a.varisYaptiMi()? "Vardı"
                         : a.isYolda()     ? "Yolda"
                         : "Bekliyor";

            String ks = a.isImha() ? "--" : String.valueOf(a.getKalanSaat());

            String vt;
            if (a.isImha()) {
                vt = "--";
            } else {
                Gezegen dep   = findGezegen(a.getCikisGezegeni());
                Gezegen varis = findGezegen(a.getVarisGezegeni());
                vt = a.getVarisTarihi(dep, varis).format(FMT);
            }

            System.out.printf("%-20s %-15s %-11s %-18s %-33s %s%n",
                              a.getAdi(),
                              durum,
                              a.getCikisGezegeni(),
                              a.getVarisGezegeni(),
                              ks,
                              vt);
        }
    }

    private void clearConsole() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private void sleep(int ms) {
        try { Thread.sleep(ms); }
        catch (InterruptedException ignored) {}
    }
}
