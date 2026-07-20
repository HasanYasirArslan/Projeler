/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Dosyadan txt verilerinin okunmasını bu sınıf sağlar. 
* </p> 
*/ 

package paket;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class DosyaOkuma {

    public static List<Gezegen> gezegenleriOku(String yol) throws IOException {
        List<Gezegen> liste = new ArrayList<>();
        for (String satir : Files.readAllLines(Paths.get(yol))) {
            if (satir.isBlank()) continue;
            String[] p = satir.split("#");
            liste.add(new Gezegen(p[0], Integer.parseInt(p[1]), p[2]));
        }
        return liste;
    }

    public static List<UzayAraci> araclariOku(String yol) throws IOException {
        List<UzayAraci> liste = new ArrayList<>();
        for (String satir : Files.readAllLines(Paths.get(yol))) {
            if (satir.isBlank()) continue;
            liste.add(new UzayAraci(satir));
        }
        return liste;
    }
}
