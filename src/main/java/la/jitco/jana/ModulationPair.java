package la.jitco.jana;

public class ModulationPair {
    
    private final ModIn modIn;
    private final ModOut modOut;
    
    ModulationPair (ModIn modIn, ModOut modOut)
    {
        this.modIn = modIn;
        this.modOut = modOut;
    }
    
    public ModIn getIn()
    {
        return modIn;
    }
    
    public ModOut getOut()
    {
        return modOut;
    }    

}
