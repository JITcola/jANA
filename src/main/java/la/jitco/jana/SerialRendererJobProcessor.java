package la.jitco.jana;

public class SerialRendererJobProcessor implements Runnable {
    
    public SerialRenderer renderer;
    public Job job;
    
    SerialRendererJobProcessor(SerialRenderer renderer, Job job)
    {
        this.renderer = renderer;
        this.job = job;
    }
    
    public void run()
    {
        try {
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " begun!");
            Thread.sleep(5000);
            job.completed = true;
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " complete!");
            boolean allJobsComplete = true;
            for (Job jobListJob: renderer.getJobList()) {
                if (jobListJob.completed == false) {
                    allJobsComplete = false;
                    break;
                }
            }
            if (allJobsComplete) {
                renderer.jobsProcessed = true;
                render();
            }
        } catch (InterruptedException e) {
            System.err.println("InterruptedException thrown!");
        }
    }
    
    public void render()
    {
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            System.err.println("InterruptedException thrown!");
        }
        System.out.println("Mock render completed!");
    }

}
