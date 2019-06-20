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
                         new ModIn("frequency"),
                         new ModIn("phase"),
                         new ModIn("level")};
        modOutArray = new ModOut[] {
                         new ModOut("mainOut"),
                         new ModOut("auxOut1"),
                         new ModOut("auxOut2"),
                         new ModOut("auxOut3")};
        createMaps();
        }

}
