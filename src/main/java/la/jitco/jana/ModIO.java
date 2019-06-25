package la.jitco.jana;

abstract public class ModIO {
    
    private final Module parent;
    protected final String name;
    
    ModIO(Module parent, String name)
    {
        this.parent = parent;
        this.name = name;
    }
    
    public int getParentId()
    {
        return parent.getId();
    }
    
    public String getName()
    {
        return name;
    }
    
}
