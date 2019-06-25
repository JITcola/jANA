package la.jitco.jana;

public class FunctionGenerator extends Module {
    
    FunctionGenerator()
    {
        super();
        paramArray = new Parameter[] {
                         new FloatingPointParameter("baseFrequency"),
                         new OptionParameter("function",
                             new String[] {"Sine", "Saw"}),
                         new FloatingPointParameter("initPhase"),
                         new FloatingPointParameter("initLevel")};
        modInArray = new ModIn[] {
                         new ModIn(this, "frequency"),
                         new ModIn(this, "phase"),
                         new ModIn(this, "level")};
        modOutArray = new ModOut[] {
                         new ModOut(this, "mainOut"),
                         new ModOut(this, "auxOut1"),
                         new ModOut(this, "auxOut2"),
                         new ModOut(this, "auxOut3")};
        createMaps();
        weightTaskMultiplier = 10;
        }

}
