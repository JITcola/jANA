package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.math.BigInteger;

public class Module {
    
    public int id;
    private Precision bitDepth;
    private BigInteger sampleRate;
    private BigInteger mpfrBits;
    
    ModuleType type;
    // private ParameterList params; // static parameters, NOT modulation targets
    // private String[] modIns;
    // private String[] modOuts;
    // private ModuleList modTargets;
    // private ModuleList modSources;
    
    private static int nextId = 0;
    private static List<Integer> deletedIds = new ArrayList<Integer>();
    
    Module(ModuleType moduleType)
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
        
        type = moduleType;        
    }

}
