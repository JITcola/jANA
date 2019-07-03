// TODO: finish this

package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.io.File;
import java.math.BigInteger;

public class SerialRenderer {
    
    private Patch patch;
    private JobDAG jobDAG;
    
    private List<Job> jobList;
    private List<Job> jobQueue = new ArrayList<Job>();    
    private List<Job> unscheduledJobs;
    public Boolean jobsProcessed = false;
    private File result;

    
    SerialRenderer(Patch patch)
    {
        this.patch = patch;
        ModuleGraph moduleGraph = new ModuleGraph(this.patch);
        this.jobDAG = new JobDAG(moduleGraph);
        
        jobList = jobDAG.dag;
        unscheduledJobs = new ArrayList<Job>(jobList);
        
    }
    
    // TODO: write these functions and make sure that they work
    
    public void schedule()
    {
        List<Job> jobsToSchedule = new ArrayList<Job>();
        for(Job job: unscheduledJobs) {
            boolean schedule = true;
            for (Job dependency: job.getDependencies()) {
                if (dependency.completed == false) {
                    schedule = false;
                    break;
                }
            }
            if (schedule)
                jobsToSchedule.add(job);
        }
        for (Job job: jobsToSchedule) {
            jobQueue.add(job);
            unscheduledJobs.remove(job);
        }
    }
    
    public void pollJobQueue()
    {
        SerialRendererJobProcessor processor = 
                new SerialRendererJobProcessor(this, jobQueue.get(0));
        jobQueue.remove(0);
        processor.run();
    }
    
    public void processJobs()
    {
        schedule();
        while (!jobsProcessed) {
            pollJobQueue();
            schedule();
        }
    }
    
    public List<Job> getJobList()
    {
        return jobList;
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
        
        SerialRenderer renderer = new SerialRenderer(patch);
        renderer.processJobs();
        
    }
    
}