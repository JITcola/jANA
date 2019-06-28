package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;

public class ModuleGraphNode {
    
    public Module module;
    
    public Color color = Color.WHITE;
    public Module predecessor = null;
    public int discovered = -1;
    public int finished = -1;
    
    ModuleGraphNode(Module module)
    {
        this.module = module;
    }

}
