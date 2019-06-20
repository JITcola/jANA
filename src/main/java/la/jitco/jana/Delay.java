package la.jitco.jana;

public class Delay extends Module {
    
    Delay()
    {
        super();
        paramArray = new Parameter[] {
                         new PositiveIntegerParameter("initTime"),
                         new NonnegativeIntegerParameter("initFeedback"),
                         new NonnegativeIntegerParameter("initLevel")};
        modInArray = new ModIn[] {new ModIn("input"),
                                  new ModIn("time"),
                                  new ModIn("feedback"),
                                  new ModIn("level")};
        modOutArray = new ModOut[] {new ModOut("mainOut")};
        createMaps();
    }
    
}
