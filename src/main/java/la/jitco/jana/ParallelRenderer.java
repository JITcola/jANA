// TODO: finish this

package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;

public class ParallelRenderer {
    
    public Patch patch;
    public JobDAG jobDAG;
    public Queue<Job> jobSchedule;
    
    public void createJobDAG()
    {
        ModuleGraph moduleGraph = new ModuleGraph(patch);
        ModuleGraph moduleGraphTranspose = moduleGraph.transpose();
        JobDAG result = new JobDAG();
        
        result.createJobs(moduleGraph, moduleGraphTranspose);
        result.setJobWeights();
        result.setJobAdjacencies();
    }
    
}