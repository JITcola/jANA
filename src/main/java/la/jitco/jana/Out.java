package la.jitco.jana;

import java.math.BigInteger;

public class Out extends Module {
    
Out()
    {
        super();
        name = "Out " + id;
        paramArray = new Parameter[] {};
        modInArray = new ModIn[] {new ModIn(this, "mainIn")};
        modOutArray = new ModOut[] {new ModOut(this, "mainOut")};
        createMaps();
        weightTaskMultiplier = 1; // TODO: find actual value
        setWeight();
        }
    
}
