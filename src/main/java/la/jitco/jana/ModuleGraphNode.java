package la.jitco.jana;

import java.util.List;

public class ModuleGraphNode {
    
    public Module module;
    public List<ModuleGraphNode> adjacentNodes;
    
    ModuleGraphNode(Module module)
    {
        this.module = module;
    }

}
