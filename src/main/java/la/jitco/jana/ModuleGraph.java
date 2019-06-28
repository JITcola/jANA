package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class ModuleGraph {
    
    public List<ModuleGraphNode> nodeList = new ArrayList<ModuleGraphNode>();
    public Map<ModuleGraphNode, List<ModuleGraphNode>> nodesAdjacentTo = 
            new HashMap<ModuleGraphNode, List<ModuleGraphNode>>();
    
    ModuleGraph()
    {
    }
    
    ModuleGraph(Patch patch)
    {
        for (Module module: patch.getModuleList()) {
            nodeList.add(new ModuleGraphNode(module));
        }
        
        for (ModuleGraphNode nodeToInitialize: nodeList) {
            nodesAdjacentTo.put(nodeToInitialize, 
                    new ArrayList<ModuleGraphNode>());
            for (Module module: 
                 nodeToInitialize.module.getModulationDestinations()) {
                for (ModuleGraphNode node: nodeList) {
                    if (module == node.module) {
                        nodesAdjacentTo.get(nodeToInitialize).add(node);
                        break;
                    }
                }
            }
        }
    }
    
    public ModuleGraph transpose()
    {
        ModuleGraph result = new ModuleGraph();
        result.nodeList = nodeList;
        for (ModuleGraphNode nodeToInitialize: nodeList) {
            result.nodesAdjacentTo.put(nodeToInitialize, 
                    new ArrayList<ModuleGraphNode>());
            for (Module module: 
                 nodeToInitialize.module.getModulationSources()) {
                for (ModuleGraphNode node: result.nodeList) {
                    if (module == node.module) {
                        result.nodesAdjacentTo.get(nodeToInitialize).add(node);
                        break;
                    }
                }
            }
        }
        return result;
    }

    public void depthFirstSearch()
    {
        // TODO: implement DFS
    }
}
