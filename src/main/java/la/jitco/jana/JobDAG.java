package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.math.BigInteger;

public class JobDAG {
    
    List<Job> dag = new ArrayList<Job>();
    
    JobDAG(ModuleGraph moduleGraph)
    {
        createJobs(moduleGraph);
        setJobWeights();
        setJobAdjacenciesAndDependencies();
    }
    
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
        for (Job job: dag)
            for (Module module: job.moduleList)
                job.weight += module.getWeight();
    }
    
    public void setJobAdjacenciesAndDependencies()
    {
        for (Job job: dag)
            for (Module module: job.moduleList)
                for (Module adjModule: module.getModulationDestinations())
                    for (Job potentialAdjacency: dag)
                        if (potentialAdjacency != job && !job.adjacentJobs.contains(potentialAdjacency))
                            if (potentialAdjacency.moduleList.contains(adjModule)) {
                                job.adjacentJobs.add(potentialAdjacency);
                                if (!potentialAdjacency.dependencies.contains(job))
                                    potentialAdjacency.dependencies.add(job);
                            }
    }
    
    public static void main(String[] args)
    {
        Patch patch = new Patch();
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("Delay");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        patch.addModule("FunctionGenerator");
        
        patch.getModuleList().get(14).setSampleRate(new BigInteger("384000"));
        patch.getModuleList().get(14).setBitDepth(Precision.MULTIPRECISION, "128");
        
        patch.getModuleList().get(1).getOut("mainOut").modulate(patch.getModuleList().get(2).getIn("frequency"));
        patch.getModuleList().get(2).getOut("mainOut").modulate(patch.getModuleList().get(3).getIn("frequency"));
        patch.getModuleList().get(2).getOut("auxOut1").modulate(patch.getModuleList().get(4).getIn("frequency"));
        patch.getModuleList().get(3).getOut("mainOut").modulate(patch.getModuleList().get(4).getIn("phase"));
        patch.getModuleList().get(3).getOut("auxOut1").modulate(patch.getModuleList().get(5).getIn("frequency"));
        patch.getModuleList().get(4).getOut("mainOut").modulate(patch.getModuleList().get(3).getIn("phase"));
        patch.getModuleList().get(4).getOut("auxOut1").modulate(patch.getModuleList().get(5).getIn("phase"));
        
        patch.getModuleList().get(6).getOut("mainOut").modulate(patch.getModuleList().get(7).getIn("frequency"));
        patch.getModuleList().get(7).getOut("mainOut").modulate(patch.getModuleList().get(8).getIn("frequency"));
        patch.getModuleList().get(8).getOut("mainOut").modulate(patch.getModuleList().get(9).getIn("input"));
        patch.getModuleList().get(9).getOut("mainOut").modulate(patch.getModuleList().get(10).getIn("frequency"));
        patch.getModuleList().get(10).getOut("mainOut").modulate(patch.getModuleList().get(11).getIn("frequency"));
        patch.getModuleList().get(11).getOut("mainOut").modulate(patch.getModuleList().get(6).getIn("frequency"));
        patch.getModuleList().get(11).getOut("auxOut1").modulate(patch.getModuleList().get(9).getIn("time"));

        patch.getModuleList().get(12).getOut("mainOut").modulate(patch.getModuleList().get(13).getIn("frequency"));
        patch.getModuleList().get(13).getOut("mainOut").modulate(patch.getModuleList().get(14).getIn("frequency"));
        patch.getModuleList().get(14).getOut("mainOut").modulate(patch.getModuleList().get(13).getIn("phase"));
        patch.getModuleList().get(5).getOut("mainOut").modulate(patch.getModuleList().get(15).getIn("frequency"));
        patch.getModuleList().get(8).getOut("auxOut1").modulate(patch.getModuleList().get(15).getIn("phase"));
        patch.getModuleList().get(14).getOut("auxOut1").modulate(patch.getModuleList().get(15).getIn("level"));
        patch.getModuleList().get(15).getOut("mainOut").modulate(patch.getModuleList().get(0).getIn("frequency"));
        
        ModuleGraph mg = new ModuleGraph(patch);
        JobDAG jobDAG = new JobDAG(mg);
        for (Job job: jobDAG.dag) {
            for (Module module: job.moduleList)
                System.out.printf("%d ", module.getId());
            System.out.printf("%n");
        }
        for (Job job: jobDAG.dag)
            System.out.println(job.weight);
        System.out.printf("***%n");
        for (Job job: jobDAG.dag) {
            System.out.println(job.moduleList.get(0).getId());
            for (Job adjJob: job.adjacentJobs)
                System.out.println(adjJob.moduleList.get(0).getId());
            System.out.printf("---%n");
        }
        System.out.println(jobDAG.dag.size());
        System.out.println("---");
        for (Job job: jobDAG.dag) {
            if (job.moduleList.contains(patch.getModuleList().get(15))) {
                for (Job dependencyJob: job.dependencies)
                    System.out.println(dependencyJob.moduleList.get(0).getId());
            }
        }
    }

}
