package la.jitco.jana;

public class ModOut extends ModIO {
    
    ModIn destination;
    
    ModOut(Module parent, String name)
    {
        super(parent, name);
        destination = null;
    }
    
    ModIn getDestination()
    {
        return destination;
    }
    
    public void modulate(ModIn destination)
    {
        this.destination = destination;
        destination.setModulator(this);
    }
    
    public void reset()
    {
        this.destination = null;
    }
    
}
