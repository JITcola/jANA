package la.jitco.jana;

public class ModIn extends ModIO{
    
    ModOut source;
    
    ModIn(String name)
    {
        super(name);
        source = null;
    }
    
    public void setModulator(ModOut source)
    {
        this.source = source;
    }
    
    public void reset()
    {
        this.source = null;
    }
    
}
