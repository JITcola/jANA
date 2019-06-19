package la.jitco.jana;

public class FunctionGenerator extends Module {
    
    public ModIn frequency;
    public ModIn phase;
    public ModIn level;
    
    public ModOut mainOut;
    public ModOut auxOut1;
    public ModOut auxOut2;
    public ModOut auxOut3;
    
    FunctionGenerator()
    {
        super(ModuleType.FUNCTION_GENERATOR);
    }

}
