package la.jitco.jana;

import java.io.File;
import java.nio.file.Files;
import java.util.List;
import java.util.ArrayList;
import java.nio.file.StandardCopyOption;
import java.io.IOException;
import java.io.BufferedReader;
import java.nio.charset.Charset;

public class ParallelRendererJobProcessor implements Runnable {
    
    public ParallelRenderer renderer;
    public Job job;
    public String jobDirectoryName;
    public File jobDirectory;
    public File jobFile;
    
    ParallelRendererJobProcessor(ParallelRenderer renderer, Job job)
    {
        this.renderer = renderer;
        this.job = job;
        jobDirectoryName = renderer.rendererDirectoryName + "/Job" +
                           renderer.jobDAG.jobIds.get(job);
        jobDirectory = new File(jobDirectoryName);
        jobFile = new File(jobDirectoryName + "/Job" + 
                           renderer.jobDAG.jobIds.get(job) + ".job");
    }
    
    public void run()
    {
        copyJobFile();
        gatherDependencies();
        processJob();
        exportDependencyOuts();
        deleteJobDirectory();
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
        if (renderOut) {
            renderer.render();
        } else {
            renderer.schedule();
            synchronized (renderer.currentThreads) {
                --renderer.currentThreads;
            }
            renderer.pollJobQueue();
        }
    }
    
    private void copyJobFile()
    {
        jobDirectory.mkdirs();
        String sourceFileName = renderer.rendererDirectoryName +"/Job" +
                                renderer.jobDAG.jobIds.get(job) + ".job";
        File sourceFile = new File(sourceFileName);
        String destinationFileName = jobDirectoryName + "/Job" + 
                                     renderer.jobDAG.jobIds.get(job) + ".job";
        File destinationFile = new File(destinationFileName);
        try {
            Files.copy(sourceFile.toPath(), destinationFile.toPath(),
                    StandardCopyOption.REPLACE_EXISTING);
        } catch (Exception e) {
            System.err.println("Exception thrown by method copyJobFile");
        }
    }
    
    private void gatherDependencies()
    {
        try {
            List<String> externalModOutDependencies = new ArrayList<String>();
            BufferedReader jobFileReader = Files.newBufferedReader(jobFile.toPath(), 
                                           Charset.forName("US-ASCII"));
            String currentLine = null;
            while ((currentLine = jobFileReader.readLine()) != null)
                if (currentLine.startsWith("External ModOut dependencies: "))
                    break;
            int indexOfColon = currentLine.indexOf(":");
            currentLine = currentLine.substring(indexOfColon + 1);
            currentLine = currentLine.trim();
            if (!currentLine.equals("")) {
                String[] modOutIds = currentLine.split(",");
                for (String modOutId: modOutIds) {
                    modOutId = modOutId.trim();
                    externalModOutDependencies.add(modOutId);
                }
            }
            for (String modOutId: externalModOutDependencies) {
                String sourceFileName = renderer.rendererDirectoryName +
                                        "/ModOut" + modOutId + ".dat";
                File sourceFile = new File(sourceFileName);
                String destinationFileName = jobDirectoryName + "/ModOut" +
                                         modOutId + ".dat";
                File destinationFile = new File(destinationFileName);
                Files.copy(sourceFile.toPath(), destinationFile.toPath(),
                           StandardCopyOption.REPLACE_EXISTING);
            }
        } catch (Exception e) {
            System.err.println("Exception thrown by method gatherDependencies");
        }
    }
    
    private void processJob()
    {
        try{
            List<String> externalModInDependencies = new ArrayList<String>();
            BufferedReader jobFileReader = Files.newBufferedReader(jobFile.toPath(),
                                            Charset.forName("US-ASCII"));
            String currentLine = null;
            while ((currentLine = jobFileReader.readLine()) != null)
                if (currentLine.startsWith("External ModIn dependencies: "))
                    break;
            int indexOfColon = currentLine.indexOf(":");
            currentLine = currentLine.substring(indexOfColon + 1);
            currentLine = currentLine.trim();
            if (!currentLine.equals("")) {
                String[] modOutIds = currentLine.split(",");
                for (String modOutId: modOutIds) {
                    modOutId = modOutId.trim();
                    externalModInDependencies.add(modOutId);
                }
            }
            for (String modOutId: externalModInDependencies) {
                String modOutFileName = jobDirectoryName + 
                                        "/ModOut" + modOutId + ".dat";
                File modOutFile = new File(modOutFileName);
                modOutFile.createNewFile();
            }
            job.completed = true;
        } catch (Exception e) {
            System.err.println("Exception thrown by method processJob");
        }
    }
    
    public void exportDependencyOuts()
    {
        try{
            List<String> externalModInDependencies = new ArrayList<String>();
            BufferedReader jobFileReader = Files.newBufferedReader(jobFile.toPath(),
                                            Charset.forName("US-ASCII"));
            String currentLine = null;
            while ((currentLine = jobFileReader.readLine()) != null)
                if (currentLine.startsWith("External ModIn dependencies: "))
                    break;
            int indexOfColon = currentLine.indexOf(":");
            currentLine = currentLine.substring(indexOfColon + 1);
            currentLine = currentLine.trim();
            if (!currentLine.equals("")) {
                String[] modOutIds = currentLine.split(",");
                for (String modOutId: modOutIds) {
                    modOutId = modOutId.trim();
                    externalModInDependencies.add(modOutId);
                }
            }
            for (String modOutId: externalModInDependencies) {
                String sourceFileName = jobDirectoryName + 
                                        "/ModOut" + modOutId + ".dat";
                File sourceFile = new File(sourceFileName);
                String destinationFileName = renderer.rendererDirectoryName +
                                             "/ModOut" + modOutId + ".dat";
                File destinationFile = new File(destinationFileName);
                Files.copy(sourceFile.toPath(), destinationFile.toPath(),
                        StandardCopyOption.REPLACE_EXISTING);
            }
        } catch (Exception e) {
            System.err.println("Exception thrown by method processJob");
        }
    }
    
    public void deleteJobDirectory()
    {
        for (File file: jobDirectory.listFiles())
            file.delete();
        jobDirectory.delete();        
    }

}
