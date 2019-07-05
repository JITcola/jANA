package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.math.BigInteger;
import java.util.Map;
import java.util.HashMap;

public class JobDAG {
    
    List<Job> dag = new ArrayList<Job>();
    Patch patch;
    Map<Job, Integer> jobIds = new HashMap<Job, Integer>();
    
    JobDAG(ModuleGraph moduleGraph, Patch patch)
    {
        this.patch = patch;
        createJobs(moduleGraph);
        setJobAdjacenciesAndDependencies();
        filterDependencies(this.patch);
        setJobWeights();
        setJobIds();
        setJobBitDepthsAndSampleRates();
        setModIds();
        computeModuleModInDependencies();
        computeJobExternalModInDependencies();
        computeModuleDependencyOuts();
        computeJobExternalDependencyOuts();
    }
    
    public void createJobs(ModuleGraph moduleGraph)
    {
        moduleGraph.depthFirstSearch();
        Collections.sort(moduleGraph.nodeList);
        ModuleGraph moduleGraphTranspose = moduleGraph.transpose();
        moduleGraphTranspose.depthFirstSearch();
        List<ModuleGraphNode> localNodeList = 
                new ArrayList<ModuleGraphNode>(moduleGraphTranspose.nodeList);
        for (ModuleGraphNode node: moduleGraphTranspose.nodeList)
            if (node.predecessor == null) {
                localNodeList.remove(node);
                Job newJob = new Job();
                newJob.moduleList.add(node.module);
                dag.add(newJob);
            }
        for (ModuleGraphNode node: localNodeList) {
            ModuleGraphNode precedingNode = node.predecessor;
            while (precedingNode.predecessor != null)
                precedingNode = precedingNode.predecessor;
            for (Job job: dag)
                if (job.moduleList.contains(precedingNode.module))
                    job.moduleList.add(node.module);
        }
    }
    
    public void setJobWeights()
    {
        for (Job job: dag)
            for (Module module: job.moduleList)
                job.weight += module.getWeight();
    }
    
    public void setJobAdjacenciesAndDependencies()
    {
        for (Job job: dag)
            for (Module module: job.moduleList)
                for (Module adjModule: module.getModulationDestinations())
                    for (Job potentialAdjacency: dag)
                        if (potentialAdjacency != job && !job.adjacentJobs.contains(potentialAdjacency))
                            if (potentialAdjacency.moduleList.contains(adjModule)) {
                                job.adjacentJobs.add(potentialAdjacency);
                                if (!potentialAdjacency.dependencies.contains(job))
                                    potentialAdjacency.dependencies.add(job);
                            }
    }
    
    public void filterDependencies(Patch patch)
    {
        Job outJob = null;
        for (Job job: dag) {
            if (job.moduleList.contains(patch.getOut().getParent()))
                outJob = job;
        }
        if (outJob == null) {
            System.err.println("Patch does not have a designated ModOut to render!");
            return;
        }
        Map<Job, Color> jobColors = new HashMap<Job, Color>();
        for (Job job: dag)
            jobColors.put(job, Color.WHITE);
        List<Job> jobsToProcess = new ArrayList<Job>();
        jobsToProcess.add(outJob);
        while (!jobsToProcess.isEmpty()) {
            for (Job job: jobsToProcess.get(0).getDependencies())
                if (jobColors.get(job) == Color.WHITE)
                    jobsToProcess.add(job);
            jobColors.put(jobsToProcess.get(0), Color.BLACK);
            jobsToProcess.remove(0);
        }
        List<Job> jobsToRemove = new ArrayList<Job>();
        for (Job job: dag)
            if (jobColors.get(job) != Color.BLACK)
                jobsToRemove.add(job);
        for (Job job: jobsToRemove)
            dag.remove(job);
        
        for (Job job: dag) {
            List<Job> deletedAdjacencies = new ArrayList<Job>();
            for (Job adjacentJob: job.getAdjacentJobs())
                if (!dag.contains(adjacentJob))
                    deletedAdjacencies.add(adjacentJob);
            for (Job adjacentJob: deletedAdjacencies)
                job.getAdjacentJobs().remove(adjacentJob);
        }
    }
    
    public void setJobIds()
    {
        int i = 0;
        for (Job job: dag) {
            jobIds.put(job, i);
            ++i;
        }
    }
    
    public void setJobBitDepthsAndSampleRates()
    {
        for (Job job: dag) {
            Precision jobBitDepth = job.getModuleList().get(0).getBitDepth();
            BigInteger jobMpfrBits = job.getModuleList().get(0).getMpfrBits();
            BigInteger jobSampleRate = job.getModuleList().get(0).getSampleRate();
            for (Module module: job.getModuleList()) {
                if (jobBitDepth == Precision.DOUBLE && 
                    module.getBitDepth() == Precision.DOUBLE)
                    ;
                if (jobBitDepth == Precision.DOUBLE &&
                    module.getBitDepth() == Precision.MULTIPRECISION) {
                    jobBitDepth = module.getBitDepth();
                    jobMpfrBits = module.getMpfrBits();
                }
                if (jobBitDepth == Precision.MULTIPRECISION &&
                    module.getBitDepth() == Precision.DOUBLE)
                    ;
                if (jobBitDepth == Precision.MULTIPRECISION &&
                    module.getBitDepth() == Precision.MULTIPRECISION) {
                    if (jobMpfrBits.compareTo(module.getMpfrBits()) < 0)
                        jobMpfrBits = module.getMpfrBits();
                }
                if (jobSampleRate.compareTo(module.getSampleRate()) < 0)
                    jobSampleRate = module.getSampleRate();
            }
            job.bitDepth = jobBitDepth;
            job.mpfrBits = jobMpfrBits;
            job.sampleRate = jobSampleRate;
        }
    }
    
    public void setModIds()
    {
        int nextId = 0;
        for (Job job: dag) {
            for (Module module: job.getModuleList()) {
                for (ModIn modIn: module.getModInArray()) {
                    if (modIn.getSource() != null) {
                        modIn.setId(nextId);
                        ++nextId;
                    } else
                        modIn.setId(-1);
                }
                for (ModOut modOut: module.getModOutArray()) {
                    if (modOut.getDestination() != null ||
                            modOut == patch.getOut()) {
                        modOut.setId(nextId);
                        ++nextId;
                    } else
                        modOut.setId(-1);
                }
            }
        }
    }
    
    public void computeModuleModInDependencies()
    {
        for (Job job: dag) {
            for (Module module: job.getModuleList()) {
                job.getModInDependencies().put(module, new ArrayList<ModulationPair>());
                for (ModIn modIn: module.getModInArray()) {
                    if (modIn.getId() != -1) {
                        job.getModInDependencies().get(module).add(new 
                            ModulationPair(modIn, modIn.getSource()));
                    }
                }
            }
        }
    }
    
    public void computeJobExternalModInDependencies()
    {
        for (Job job: dag) {
            for (Module module: job.getModuleList()) {
                for (ModulationPair modulationPair: job.getModInDependencies().get(module)) {
                    if (!job.getModuleList().contains(modulationPair.getOut().getParent())) {
                        job.getJobExternalModInDependencies().add(modulationPair.getOut());
                    }
                }
            }
        }
    }
    
    public void computeModuleDependencyOuts()
    {
        for (Job job: dag) {
            for (Module module: job.getModuleList()) {
                job.getModuleDependencyOuts().put(module, new ArrayList<ModulationPair>());
                for (ModOut modOut: module.getModOutArray()) {
                    if (modOut.getId() != -1)
                        job.getModuleDependencyOuts().get(module).add(new 
                            ModulationPair(modOut.getDestination(), modOut));
                }
            }
        }
    }
    
    public void computeJobExternalDependencyOuts()
    {
        for (Job job: dag) {
            for (Module module: job.getModuleList()) {
                for (ModulationPair modulationPair: job.getModuleDependencyOuts().get(module)) {
                    if (modulationPair.getOut() == patch.getOut() || 
                        !job.getModuleList().contains(modulationPair.getOut().getDestination().getParent())) {
                        job.getJobExternalDependencyOuts().add(modulationPair.getOut());
                    }
                }
            }
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
        
        ModuleGraph mg = new ModuleGraph(patch);
        JobDAG jobDAG = new JobDAG(mg, patch);
        for (Job job: jobDAG.dag) {
            for (Module module: job.moduleList)
                System.out.printf("%d ", module.getId());
            System.out.printf("%n");
        }
        for (Job job: jobDAG.dag) {
            System.out.println(job.getModuleList().get(0).getId());
            System.out.println(job.bitDepth);
            System.out.println(job.mpfrBits);
            System.out.println(job.sampleRate);
        }
    }

}
