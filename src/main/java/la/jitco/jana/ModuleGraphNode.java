package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;

public class ModuleGraphNode implements Comparable<ModuleGraphNode> {
    
    public Module module;
    
    public Color color = Color.WHITE;
    public ModuleGraphNode predecessor = null;
    public int discovered = -1;
    public int finished = -1;
    
    ModuleGraphNode(Module module)
    {
        this.module = module;
    }
    
    public int compareTo(ModuleGraphNode node) // NOTE THAT THIS SORTS IN
                                               // DECREASING ORDER!
    {
        if (this.finished < node.finished)
            return 1;
        else if (this.finished == node.finished)
            return 0;
        else
            return -1;
    }

}
