package la.jitco.jana;

public class FunctionGenerator extends Module {
    
    FunctionGenerator(int id)
    {
        super(id);
        type = ModuleType.FUNCTION_GENERATOR;
        name = "FunctionGenerator " + id;
        paramArray = new Parameter[] {
                         new NonnegativeFloatingPointParameter("baseFrequency"),
                         new OptionParameter("function",
                             new String[] {"Sine", "Saw", "Square"}),
                         new NonnegativeFloatingPointParameter("initPhase"),
                         new NonnegativeFloatingPointParameter("initLevel")};
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
        weightTaskMultiplier = 10; // TODO: find actual value
        setWeight();
        
        paramArray[3].setValue("1.0");
        }

}
