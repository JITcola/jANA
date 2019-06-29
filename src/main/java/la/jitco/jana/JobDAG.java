package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
public class JobDAG {
    
    List<Job> dag = new ArrayList<Job>();
    
    public void createJobs(ModuleGraph moduleGraph)
    {
        moduleGraph.depthFirstSearch();
        Collections.sort(moduleGraph.nodeList);
        ModuleGraph moduleGraphTranspose = moduleGraph.transpose();
        moduleGraphTranspose.depthFirstSearch();
        List<ModuleGraphNode> localNodeList = 
                new ArrayList<ModuleGraphNode>(moduleGraphTranspose.nodeList);
        for (ModuleGraphNode node: moduleGraphTranspose.nodeList)
            if (node.predecessor == null) {
                localNodeList.remove(node);
                Job newJob = new Job();
                newJob.moduleList.add(node.module);
                dag.add(newJob);
            }
        for (ModuleGraphNode node: localNodeList) {
            ModuleGraphNode precedingNode = node.predecessor;
            while (precedingNode.predecessor != null)
                precedingNode = precedingNode.predecessor;
            for (Job job: dag)
                if (job.moduleList.contains(precedingNode.module))
                    job.moduleList.add(node.module);
        }
    }
    
    public void setJobWeights()
    {
        // TODO: implement this
    }
    
    public void setJobAdjacencies()
    {
        // TODO: implement this
    }
    
    public static void main(String[] args)
    {
        Patch patch = new Patch();
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        
        patch.getModuleList().get(1).getOut("mainOut").modulate(patch.getModuleList().get(2).getIn("frequency"));
        patch.getModuleList().get(3).getOut("mainOut").modulate(patch.getModuleList().get(4).getIn("frequency"));
        patch.getModuleList().get(4).getOut("mainOut").modulate(patch.getModuleList().get(5).getIn("frequency"));
        patch.getModuleList().get(5).getOut("mainOut").modulate(patch.getModuleList().get(4).getIn("frequency"));
                
        ModuleGraph mg = new ModuleGraph(patch);
        JobDAG jobDAG = new JobDAG();
        jobDAG.createJobs(mg);
        for (Job job: jobDAG.dag)
            for (Module module: job.moduleList)
                System.out.printf("%d ", module.getId());
            System.out.println();
    }

}
