package la.jitco.jana;

public class ModIn extends ModIO{
    
    ModOut source;
    
    ModIn(Module parent, String name)
    {
        super(parent, name);
        source = null;
    }
    
    ModOut getSource()
    {
        return source;
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
