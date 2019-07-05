package la.jitco.jana;

import java.io.File;
import java.nio.file.Files;
import java.util.List;
import java.util.ArrayList;
import java.nio.file.StandardCopyOption;
import java.io.IOException;

public class ParallelRendererJobProcessor implements Runnable {
    
    public ParallelRenderer renderer;
    public Job job;
    public String jobDirectoryName = renderer.rendererDirectoryName + "/job" + 
                                 renderer.jobDAG.jobIds.get(job);
    public File jobDirectory = new File(jobDirectoryName);
    
    ParallelRendererJobProcessor(ParallelRenderer renderer, Job job)
    {
        this.renderer = renderer;
        this.job = job;
    }
    
    public void run()
    {
        gatherDependencies();
        copyJobFile();
        processJob();
        deleteTemporaryFiles();
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
    }
    
    private void gatherDependencies()
    {
        jobDirectory.mkdirs();
        /*
        List<Integer> modOutDependencyIds = new ArrayList<Integer>();
        for (ModIO modOut: job.getExternalModOutDependencies())
            modOutDependencyIds.add(modOut.getId());
        for (Integer modOutId: modOutDependencyIds) {
            String sourceFileName = renderer.rendererDirectoryName + "/ModOut" + 
                                    modOutId + ".dat";
            File sourceFile = new File(sourceFileName);
            String destinationFileName = jobDirectoryName + "/ModOut" + 
                                         modOutId + ".dat";
            File destinationFile = new File(destinationFileName);
            try {
                Files.copy(sourceFile.toPath(), destinationFile.toPath(), 
                       StandardCopyOption.REPLACE_EXISTING);
            } catch (IOException e) {
                System.err.println("IOException thrown by gatherDependencies");
            }
        }
        */
    }
    
    private void copyJobFile()
    {
        String sourceFileName = renderer.rendererDirectoryName +"/Job" +
                                renderer.jobDAG.jobIds.get(job) + ".job";
        File sourceFile = new File(sourceFileName);
        String destinationFileName = jobDirectoryName + "/Job" + 
                                     renderer.jobDAG.jobIds.get(job) + ".job";
        File destinationFile = new File(destinationFileName);
        try {
            Files.copy(sourceFile.toPath(), destinationFile.toPath(),
                    StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            System.err.println("IOException thrown by copyJobFile");
        }
    }
    
    private void processJob()
    {
        try {
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " begun!");
            Thread.sleep(5000);
            job.completed = true;
            System.out.println("Job with module " + 
                               job.moduleList.get(0).getName() + " complete!");
        } catch (InterruptedException e) {
            System.err.println("InterruptedException thrown!");
        }
    }
    
    public void render()
    {
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            System.err.println("InterruptedException thrown!");
        }
        System.out.println("Mock render completed!");
    }
    
    public void deleteTemporaryFiles()
    {
        for (File file: jobDirectory.listFiles())
            file.delete();
        jobDirectory.delete();        
    }

}
