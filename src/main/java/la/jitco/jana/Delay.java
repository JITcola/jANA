package la.jitco.jana;

public class Delay extends Module {
    
    Delay()
    {
        super();
        modInArray = new ModIn[] {new ModIn("time"),
                                  new ModIn("feedback"),
                                  new ModIn("level")};
        modOutArray = new ModOut[] {new ModOut("mainOut")};
        createModMaps();
    }
}
