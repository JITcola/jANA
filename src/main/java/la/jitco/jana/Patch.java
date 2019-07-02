package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;

public class Patch {
    
    private List<Module> moduleList = new ArrayList<Module>();
    private ModOut outToRender;
    public int renderLength = -1;
    public SoundFileFormat format = SoundFileFormat.WAV_16_44100;
    
    Patch()
    {
        moduleList.add(new FunctionGenerator());
        outToRender = moduleList.get(0).getOut("mainOut");
    }
    
    public List<Module> getModuleList()
    {
        return moduleList;
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
    
    public void deleteModule(Module module) // TODO: allow deletion of Out
    {
        if (moduleList.contains(module)) {
            moduleList.remove(module);
            for (ModOut modOut: module.getModOutArray())
                modOut.getDestination().reset();
            for (ModIn modIn: module.getModInArray())
                modIn.getSource().reset();
        }
        else
            System.err.println("Module not in patch!");
    }
    
    public void setOut(ModOut out)
    {
        if (moduleList.contains(out.getParent()))
            outToRender = out;
        else
            System.err.printf("Patch does not contain parent module of argument to setOut");
    }
    
    public static void main(String[] args)
    {
        Patch pg1 = new Patch();
        pg1.addModule("FunctionGenerator");
        pg1.deleteModule(pg1.moduleList.get(1));
        System.out.println(pg1.moduleList.size());
        pg1.addModule("Delay");
    }

}
