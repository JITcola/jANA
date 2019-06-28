package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;

public class ParallelRenderer {
    
    public Patch patch;
    public List<Job> jobDAG;
    public Queue<Job> jobSchedule;
    
    public void createJobDAG()
    {
        createJobs(); // creates all Jobs, populating their moduleLists
        findAdjacentJobs(); // Finds and sets the adjacentJobs list of each Job
        findWeights(); // Finds and sets the weight of each job
        
    }
    
    public void createJobSchedule()
    {
        
    }
    
    public void createJobs()
    {
        
    }
    
    public void findAdjacentJobs()
    {
        
    }
    
    public void findWeights()
    {
        
    }
}