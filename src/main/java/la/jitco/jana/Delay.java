package la.jitco.jana;

import java.math.BigInteger;

public class Delay extends Module {
    
    Delay()
    {
        super();
        paramArray = new Parameter[] {
                         new PositiveIntegerParameter("initTime"),
                         new NonnegativeIntegerParameter("initFeedback"),
                         new NonnegativeIntegerParameter("initLevel")};
        modInArray = new ModIn[] {new ModIn(this, "input"),
                                  new ModIn(this, "time"),
                                  new ModIn(this, "feedback"),
                                  new ModIn(this, "level")};
        modOutArray = new ModOut[] {new ModOut(this, "mainOut")};
        createMaps();
        weightTaskMultiplier = 5; // TODO: find actual value
        setWeight();
    }
    
}
