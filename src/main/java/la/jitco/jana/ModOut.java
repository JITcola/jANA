package la.jitco.jana;

public class ModOut extends ModIO {
    ModIn destination;
    
    ModOut(String name)
    {
        super(name);
        destination = null;
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
