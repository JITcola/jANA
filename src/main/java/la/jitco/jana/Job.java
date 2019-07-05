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
    public BigInteger mpfrBits;
    public BigInteger sampleRate;
    public Map<Module, List<ModulationPair>> modInDependencies = 
            new HashMap<Module, List<ModulationPair>>();
    public List<ModIO> jobExternalModInDependencies = new ArrayList<ModIO>();
    public Map<Module, List<ModOut>> moduleDependencyOuts = 
            new HashMap<Module, List<ModOut>>();
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
    
    public List<ModIO> getJobExternalModInDependencies()
    {
        return jobExternalModInDependencies;
    }
    
    public Map<Module, List<ModOut>> getModuleDependencyOuts()
    {
        return moduleDependencyOuts;
    }
    
    public List<ModOut> getJobExternalDependencyOuts()
    {
        return jobExternalDependencyOuts;
    }

}
