package la.jitco.jana;

import java.util.Arrays;
import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

public class Playground {
    /*
    public static void main(String[] args)
    {
        int precision = 64;
        Apfloat sampleRate = new Apfloat("44100", precision);
        System.out.println(sampleRate);
        Apfloat pi = new Apfloat("3.14159265358979323851", precision);
        System.out.println(pi);
        Apfloat two = new Apfloat("2", precision);
        System.out.println(two);
        Apfloat frequency = new Apfloat("300", precision);
        System.out.println(frequency);
        Apfloat multiplier = pi.multiply(two).multiply(frequency).divide(sampleRate);
        System.out.println(multiplier);
        Apfloat[] result = new Apfloat[44100];
        //Arrays.parallelSetAll(result, i -> 
        //                      ApfloatMath.sin(multiplier.multiply(new Apfloat((double) i, precision))));
        for (int i = 0; i < 44100; ++i) {
            result[i] = new Apfloat((double)i, precision);
            result[i] = ApfloatMath.sin(multiplier.multiply(result[i]));
        }
        System.out.println(result[11000]);
        System.out.println(result[43000]);
    }
    */

}
