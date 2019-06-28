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
        FunctionGenerator fg1 = new FunctionGenerator();
        FunctionGenerator fg2 = new FunctionGenerator();
        FunctionGenerator fg3 = new FunctionGenerator();
        FunctionGenerator fg4 = new FunctionGenerator();
        FunctionGenerator fg5 = new FunctionGenerator();
        
        fg1.getOut("mainOut").modulate(fg2.getIn("frequency"));
        fg3.getOut("mainOut").modulate(fg4.getIn("frequency"));
        fg4.getOut("mainOut").modulate(fg5.getIn("frequency"));
        fg5.getOut("mainOut").modulate(fg4.getIn("frequency"));
        // fg2.getOut("mainOut").modulate(patch.getModuleList().get(0).getIn("mainIn"));
        
        ModuleGraph mg = new ModuleGraph(patch);
        JobDAG jobDAG = new JobDAG();
        jobDAG.createJobs(mg);
        for (Job job: jobDAG.dag)
            for (Module module: job.moduleList)
                System.out.printf("%d ", module.getId());
            System.out.println();
    }

}
