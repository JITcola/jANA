// TODO: finish this

package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.io.File;

public class ParallelRenderer {
    
    private Patch patch;
    private JobDAG jobDAG;
    
    private List<Job> jobList = jobDAG.dag;
    private List<Job> jobQueue = new ArrayList<Job>();    
    private Integer maxThreads = Runtime.getRuntime().availableProcessors();
    private Integer currentThreads = 0;
    private List<Job> unscheduledJobs = new ArrayList<Job>(jobList);
    private Boolean jobsProcessed = false;
    private File result;

    
    ParallelRenderer(Patch patch)
    {
        this.patch = patch;
        ModuleGraph moduleGraph = new ModuleGraph(this.patch);
        this.jobDAG = new JobDAG(moduleGraph);
        
    }
    
    // TODO: write these functions and make sure that they work
    
    private void schedule()
    {
        synchronized (jobQueue) {
            synchronized (unscheduledJobs) {
                for(Job job: unscheduledJobs) {
                    boolean schedule = true;
                    for (Job dependency: job.getDependencies()) {
                        if (dependency.completed == false) {
                            schedule = false;
                            break;
                        }
                    }
                    if (schedule) {
                        jobQueue.add(job);
                        unscheduledJobs.remove(job);
                    }
                }
            }
        }
    }
    
    private void pollJobQueue()
    {
        
    }
    
    public void processJobs()
    {
        
    }
    
    private void render()
    {
        
    }
    
    private void process()
    {
        
    }
    
}