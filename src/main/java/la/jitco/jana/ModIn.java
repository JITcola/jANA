package la.jitco.jana;

public class ModIn {
    ModOut source;
    
    ModIn()
    {
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
