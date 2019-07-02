// TODO: finish this

package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;

public class Job {
    
    public List<Module> moduleList = new ArrayList<Module>();
    public List<Job> adjacentJobs = new ArrayList<Job>();
    public List<Job> dependencies = new ArrayList<Job>();
    public double weight = 0;
    public boolean completed = false;
    
    public List<Job> getDependencies()
    {
        return dependencies;
    }
    
    public List<Job> getAdjacentJobs()
    {
        return adjacentJobs;
    }

}
