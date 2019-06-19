package la.jitco.jana;

public class Delay extends Module {
    
    public ModIn time;
    public ModIn feedback;
    public ModIn level;
    
    public ModOut mainOut;
    
    Delay()
    {
        super(ModuleType.DELAY);
    }
}
