package la.jitco.jana;

public class PrecisionClass {
    
    private final Precision precision;
    
    PrecisionClass(Precision precision)
    {
        this.precision = precision;
    }
    
    public String toString()
    {
        if (precision == Precision.DOUBLE)
            return "double";
        else if (precision == Precision.MULTIPRECISION)
            return "multiprecision";
        else {
            System.err.println("Precision in PrecisionClass invalid!");
            return "INVALID";
        }
    }

}
