package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;

public class PatchGraph {
    
    public List<Module> moduleList = new ArrayList<Module>();
    
    PatchGraph()
    {
        moduleList.add(new Out());
    }
    
    public void addModule(String moduleType)
    {
        switch (moduleType) {
            case "Delay":
                moduleList.add(new Delay());
                break;
            case "FunctionGenerator":
                moduleList.add(new FunctionGenerator());
                break;
            default:
                System.err.println("Module type \"" + moduleType +
                                   "\" not recognized");
        }
    }
    
    public void deleteModule(Module module)
    {
        if (module.getClass() != Out.class)
            moduleList.remove(module);
        else
            System.err.println("Can't remove Out from PatchGraph instance");
    }
    
    public static void main(String[] args)
    {
        PatchGraph pg1 = new PatchGraph();
        pg1.addModule("FunctionGenerator");
        pg1.deleteModule(pg1.moduleList.get(1));
        System.out.println(pg1.moduleList.size());
        pg1.addModule("Out");
    }

}
