package la.jitco.jana;

import java.math.BigInteger;

public class Out extends Module {
    
Out()
    {
        super();
        paramArray = new Parameter[] {};
        modInArray = new ModIn[] {new ModIn(this, "mainIn")};
        modOutArray = new ModOut[] {};
        createMaps();
        weightTaskMultiplier = new BigInteger("1"); // TODO: find actual value
        setWeight();
        }
    
}
