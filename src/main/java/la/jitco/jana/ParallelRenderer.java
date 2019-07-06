package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.io.File;
import java.math.BigInteger;
import java.io.IOException;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.BufferedWriter;

public class ParallelRenderer {
    
    private Patch patch;
    public JobDAG jobDAG;
    
    private final List<Job> jobList;
    public List<Job> jobQueue = new ArrayList<Job>();    
    private Integer maxThreads = Runtime.getRuntime().availableProcessors();
    public Integer currentThreads = 0;
    private List<Job> unscheduledJobs;
    public Boolean jobsProcessed = false;
    public final String userHome = System.getProperty("user.home");
    public final String rendererDirectoryName = userHome + "/jANA_data";
    public final File rendererDirectory = new File(rendererDirectoryName);
    public final String renderDirectoryName = userHome + "/render";
    public final File renderDirectory = new File(renderDirectoryName);
    public final File result = new File(renderDirectoryName + "/render.wav");

    
    ParallelRenderer(Patch patch)
    {
        this.patch = patch;
        ModuleGraph moduleGraph = new ModuleGraph(this.patch);
        this.jobDAG = new JobDAG(moduleGraph, this.patch);
        
        jobList = jobDAG.dag;
        unscheduledJobs = new ArrayList<Job>(jobList);
        
    }
    
    public void createJobFiles()
    {
        for (Job job: jobList) {
            try {
                PrintWriter jobFileWriter = new PrintWriter(new BufferedWriter(new 
                                      FileWriter(rendererDirectoryName + "/Job" + 
                                      jobDAG.jobIds.get(job) + ".job")));
                jobFileWriter.write("Job ID: " + jobDAG.jobIds.get(job) + "\n");
                jobFileWriter.write("Precision: " + 
                              (new PrecisionClass(job.getBitDepth())).toString() + 
                              "\n");
                jobFileWriter.write("Multiprecision bits: " + 
                              job.getMpfrBits().toString() + "\n");
                jobFileWriter.write("Sample rate: " + job.getSampleRate().toString() +
                              "\n");
                jobFileWriter.write("External ModOut dependencies: ");
                switch (job.getJobExternalModInDependencies().size()) {
                    case 0:
                            jobFileWriter.write("\n");
                            break;
                    case 1:
                            jobFileWriter.write(job.getJobExternalModInDependencies().get(0).getId() +
                                          "\n");
                            break;
                    default:
                            for (ModOut modOut: job.getJobExternalModInDependencies()) {
                                if (modOut !=
                                    job.getJobExternalModInDependencies().get(
                                    job.getJobExternalModInDependencies().size()-1))
                                    jobFileWriter.write(modOut.getId() + ", ");
                                else
                                    jobFileWriter.write(modOut.getId() + "\n");
                            }
                            break;
                }
                jobFileWriter.write("External ModIn dependencies: ");
                switch(job.getJobExternalDependencyOuts().size()) {
                    case 0:
                            jobFileWriter.write("\n");
                            break;
                    case 1:
                            jobFileWriter.write(job.getJobExternalDependencyOuts().get(0).getId() +
                                          "\n");
                            break;
                    default:
                             for (ModOut modOut: job.getJobExternalDependencyOuts()) {
                                 if (modOut !=
                                     job.getJobExternalDependencyOuts().get(
                                     job.getJobExternalDependencyOuts().size() - 1))
                                     jobFileWriter.write(modOut.getId() + ", ");
                                 else
                                     jobFileWriter.write(modOut.getId() + "\n");
                             }
                             break;
                }
                for (Module module: job.getModuleList()) {
                    jobFileWriter.write("Module:\n");
                    jobFileWriter.write("Module type: " + module.getType() + "\n");
                    jobFileWriter.write("Parameters:\n");
                    for (Parameter param: module.getParameterArray())
                        jobFileWriter.write(param.getName() + ": " + param.getValue() +
                                      "\n");
                    jobFileWriter.write("Dependent ModIns:\n");
                    for (ModulationPair modulationPair: job.getModInDependencies().get(module)) {
                        jobFileWriter.write(modulationPair.getIn().getName() + ": " +
                                      modulationPair.getIn().getId() + "; " +
                                      modulationPair.getOut().getId() + "\n");
                    }
                    jobFileWriter.write("Dependency ModOuts:\n");
                    for (ModulationPair modulationPair: job.getModuleDependencyOuts().get(module)) {
                        if (modulationPair.getOut() != patch.getOut())
                            jobFileWriter.write(modulationPair.getOut().getName() + ": " + 
                                                modulationPair.getOut().getId() + "; " +
                                                modulationPair.getIn().getId() + "\n");
                    }
                }
                jobFileWriter.close();
            } catch (Exception e) {
                System.err.println("Exception thrown by createJobFiles");
            }
        }
    }
    
    public void schedule()
    {
        synchronized (jobQueue) {
            synchronized (unscheduledJobs) {
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
        }
    }
    
    public void pollJobQueue()
    {
        synchronized (jobQueue) {
            synchronized (currentThreads) {
                int unusedThreads = maxThreads - currentThreads;
                int numNewThreads = Math.min(unusedThreads, jobQueue.size());
                List<Thread> newThreads = new ArrayList<Thread>();
                for (int i = 0; i < numNewThreads; ++i) {
                    ParallelRendererJobProcessor processor = 
                            new ParallelRendererJobProcessor(this, jobQueue.get(0));
                    jobQueue.remove(0);
                    Thread newThread = new Thread(processor);
                    newThreads.add(newThread);
                }
                for (Thread thread: newThreads)
                    thread.start();
                currentThreads += newThreads.size();
            }
        }
    }
    
    public void processJobs()
    {
        deleteRenderDirectory();
        rendererDirectory.mkdirs();
        createJobFiles();
        schedule();
        pollJobQueue();
    }
    
    public void deleteRendererDirectory()
    {
        for (File file: rendererDirectory.listFiles())
            file.delete();
        rendererDirectory.delete();
    }
    
    public void deleteRenderDirectory()
    {
        if (renderDirectory.exists()) {
            for (File file: renderDirectory.listFiles())
                file.delete();
            renderDirectory.delete();
        }
    }
    
    public List<Job> getJobList()
    {
        return jobList;
    }
    
    public void render()
    {
        try {
            renderDirectory.mkdirs();
            result.createNewFile();
            deleteRendererDirectory();
        } catch (IOException e) {
            System.err.println(e.getMessage());
        } catch (SecurityException e) {
            System.err.println("SecurityException thrown by method render");
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
        
        patch.setOut(patch.getModuleList().get(0).getOut("mainOut"));
        
        ParallelRenderer renderer = new ParallelRenderer(patch);
        renderer.processJobs();
        
    }
    
}