package la.jitco.jana;

public class ParallelRendererJobProcessor implements Runnable {
    
    public ParallelRenderer renderer;
    public Job job;
    
    ParallelRendererJobProcessor(ParallelRenderer renderer, Job job)
    {
        this.renderer = renderer;
        this.job = job;
    }
    
    public void run()
    {
        try {
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " begun!");
            Thread.sleep(10000);
            job.completed = true;
            boolean renderOut = false;
            boolean allJobsComplete = true;
            for (Job jobListJob: renderer.getJobList()) {
                if (jobListJob.completed == false) {
                    allJobsComplete = false;
                    break;
                }
            }
            if (allJobsComplete) {
                synchronized (renderer.jobsProcessed) {
                    if (!renderer.jobsProcessed) {
                        renderer.jobsProcessed = true;
                        renderOut = true;
                    }
                }
            }
            if (renderOut)
                render();
            else {
                renderer.schedule();
                synchronized (renderer.currentThreads) {
                    --renderer.currentThreads;
                }
                renderer.pollJobQueue();
            }
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " complete!");
        } catch (InterruptedException e) {
            System.err.println("InterruptedException thrown!");
        }
    }
    
    public void render()
    {
        System.out.println("Mock render completed!");
    }

}
