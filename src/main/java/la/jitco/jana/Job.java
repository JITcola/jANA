// TODO: finish this

package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.Map;
import java.util.HashMap;

public class Job {
    
    public List<Module> moduleList = new ArrayList<Module>();
    public List<Job> adjacentJobs = new ArrayList<Job>();
    public List<Job> dependencies = new ArrayList<Job>();
    public double weight = 0;
    public boolean completed = false;
    public Precision bitDepth;
    public int mpfrBits;
    public int sampleRate;
    public Map<Module, List<ModulationPair>> modInDependencies = 
            new HashMap<Module, List<ModulationPair>>();
    public List<ModOut> jobExternalModInDependencies = new ArrayList<ModOut>();
    public Map<Module, List<ModulationPair>> moduleDependencyOuts = 
            new HashMap<Module, List<ModulationPair>>();
    public List<ModOut> jobExternalDependencyOuts = new ArrayList<ModOut>();
    
    public List<Job> getDependencies()
    {
        return dependencies;
    }
    
    public List<Job> getAdjacentJobs()
    {
        return adjacentJobs;
    }
    
    public List<Module> getModuleList()
    {
        return moduleList;
    }
    
    public Map<Module, List<ModulationPair>> getModInDependencies()
    {
        return modInDependencies;
    }
    
    public List<ModOut> getJobExternalModInDependencies()
    {
        return jobExternalModInDependencies;
    }
    
    public Map<Module, List<ModulationPair>> getModuleDependencyOuts()
    {
        return moduleDependencyOuts;
    }
    
    public List<ModOut> getJobExternalDependencyOuts()
    {
        return jobExternalDependencyOuts;
    }
    
    public Precision getBitDepth()
    {
        return bitDepth;
    }
    
    public int getMpfrBits()
    {
        return mpfrBits;
    }
    
    public int getSampleRate()
    {
        return sampleRate;
    }

}
