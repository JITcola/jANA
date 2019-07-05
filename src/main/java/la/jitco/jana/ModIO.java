package la.jitco.jana;

abstract public class ModIO {
    
    private final Module parent;
    protected final String name;
    public Integer id = -1;
    
    ModIO(Module parent, String name)
    {
        this.parent = parent;
        this.name = name;
    }
    
    public int getParentId()
    {
        return parent.getId();
    }
    
    public Module getParent()
    {
        return parent;
    }
    
    public String getName()
    {
        return name;
    }
    
    public void setId(int id)
    {
        this.id = id;
    }
    
    public Integer getId()
    {
        return id;
    }
    
}
