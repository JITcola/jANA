package la.jitco.jana;

public class ModOut {
    ModIn destination;
    
    ModOut()
    {
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
