package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.Map;
import java.util.HashMap;

public class Module {
    
    public int id;
    private Precision bitDepth;
    private BigInteger sampleRate;
    private BigInteger mpfrBits;
    
    // private ParameterList params; // static parameters, NOT modulation targets
    public ModIn[] modInArray;
    protected ModOut[] modOutArray;
    public Map<String, ModIn> inModMap;
    public Map<String, ModOut> outModMap;

    // private ModuleList modTargets;
    // private ModuleList modSources;
    
    private static int nextId = 0;
    private static List<Integer> deletedIds = new ArrayList<Integer>();
    
    Module()
    {
        if (deletedIds.isEmpty()) {
            id = nextId;
            ++nextId;
        } else {
            id = deletedIds.remove(0);            
        }
        
        bitDepth = Precision.FLOAT_64;
        sampleRate = new BigInteger("44100");
        mpfrBits = new BigInteger("256");
        
        inModMap = new HashMap<String, ModIn>();
        outModMap = new HashMap<String, ModOut>();
               
    }
    
    protected void createModMaps()
    {
        for (int i = 0; i < modInArray.length; ++i) {
            inModMap.put(modInArray[i].name, modInArray[i]);
        }
        for (int i = 0; i < modOutArray.length; ++i)
            outModMap.put(modOutArray[i].name, modOutArray[i]);
    }
    
    int getId()
    {
        return id;
    }
    
    ModIn getIn(String modName)
    {
        return inModMap.get(modName);
    }
    
    ModOut getOut(String modName)
    {
        return outModMap.get(modName);
    }
    
    public static void main(String[] args)
    {
        Module fg1 = new FunctionGenerator();
        Module fg2 = new FunctionGenerator();
        Module d1 = new Delay();
        Module d2 = new Delay();
        
        System.out.printf(fg1.getId() + "%n" + fg2.getId() +
                          "%n" + d1.getId() + "%n" + d2.getId() + "%n");
        fg1.getOut("mainOut").modulate(fg2.getIn("frequency"));
        fg2.getOut("auxOut1").modulate(d1.getIn("time"));
        System.out.printf(fg1.getOut("mainOut").destination.name + "%n" +
                          fg2.getOut("auxOut1").destination.name + "%n");
    }
}
