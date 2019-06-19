package la.jitco.jana;

public class FunctionGenerator extends Module {
    
    FunctionGenerator()
    {
        super();
        modInArray = new ModIn[] {new ModIn("frequency"),
                                  new ModIn("phase"),
                                  new ModIn("level")};
        modOutArray = new ModOut[] {new ModOut("mainOut"),
                                    new ModOut("auxOut1"),
                                    new ModOut("auxOut2"),
                                    new ModOut("auxOut3")};
        createModMaps();
        }

}
