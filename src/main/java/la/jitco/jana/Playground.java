package la.jitco.jana;

import java.util.Arrays;
import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

public class Playground {
    
    public static void main(String[] args)
    {
        int precision = 256;
        Apfloat sampleRate = new Apfloat("44100", precision);
        Apfloat pi = ApfloatMath.pi(precision);
        Apfloat two = new Apfloat("2", precision);
        Apfloat frequency = new Apfloat("300", precision);
        Apfloat multiplier = pi.multiply(two).multiply(frequency).divide(sampleRate);
        Apfloat[] result = new Apfloat[44100];
        Arrays.parallelSetAll(result, i -> 
                              ApfloatMath.sin(multiplier.multiply(new Apfloat((double) i, precision))));
    }

}
