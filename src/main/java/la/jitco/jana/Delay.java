package la.jitco.jana;

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
        weightTaskMultiplier = 5;
    }
    
}
