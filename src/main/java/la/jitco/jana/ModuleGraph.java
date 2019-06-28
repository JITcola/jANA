package la.jitco.jana;

import java.util.List;

public class ModuleGraph {
    
    public List<ModuleGraphNode> nodeList = null;
    
    public void createPatchGraphFrom(Patch patch)
    {
        
        for (Module module: patch.moduleList)
            nodeList.add(new ModuleGraphNode(module));
        
        for (ModuleGraphNode nodeToInitialize: nodeList) {
            for (Module module: 
                 nodeToInitialize.module.getModulationDestinations()) {
                for (ModuleGraphNode node: nodeList) {
                    if (module == node.module) {
                        nodeToInitialize.adjacentNodes.add(node);
                        break;
                    }
                }
            }
        }
    }
    
    public void createTransposePatchGraphFrom(Patch patch)
    {
        for (Module module: patch.moduleList)
            nodeList.add(new ModuleGraphNode(module));
        
        for (ModuleGraphNode nodeToInitialize: nodeList) {
            for (Module module: 
                 nodeToInitialize.module.getModulationSources()) {
                for (ModuleGraphNode node: nodeList) {
                    if (module == node.module) {
                        nodeToInitialize.adjacentNodes.add(node);
                        break;
                    }
                }
            }
        }
    }

}
