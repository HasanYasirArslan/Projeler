/** 
* 
* @author Hasan Yasir ARSLAN yasir.arslan@ogr.sakarya.edu.tr 
* @since 25.04.2025 
* <p> 
*  Kişi bilgileri bu sınıf sayesinde yönetilir. 
* </p> 
*/ 

package paket;

public class Kisi {
    private String isim;
    private int yas;
    private long kalanOmurSaat;

    public Kisi(String isim, int yas, long kalanOmurSaat) {
        this.isim = isim;
        this.yas = yas;
        this.kalanOmurSaat = kalanOmurSaat;
    }

    /** 1 saatlik ömrü tüketir */
    public void yasamSaatiAzalt() {
        if (kalanOmurSaat > 0) kalanOmurSaat--;
    }

    /** Ömrü tükendiyse true döner */
    public boolean olduMu() {
        return kalanOmurSaat <= 0;
    }

    public String getIsim() {
        return isim;
    }
}
