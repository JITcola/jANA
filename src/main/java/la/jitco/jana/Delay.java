package la.jitco.jana;

public class Delay extends Module {
    
    Delay(int id)
    {
        super(id);
        type = ModuleType.DELAY;
        name = "Delay " + id;
        paramArray = new Parameter[] {
                         new PositiveFloatingPointParameter("initTime"),
                         new NonnegativeFloatingPointParameter("initFeedback"),
                         new NonnegativeFloatingPointParameter("initLevel")};
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
