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
        JobDAG result = new JobDAG();
        
        result.createJobs(moduleGraph);
        result.setJobWeights();
        result.setJobAdjacencies();
    }
    
}