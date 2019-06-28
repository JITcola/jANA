package la.jitco.jana;

import java.util.List;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.Map;
import java.util.HashMap;

public class Module {
    
    public int id;
    private String name = "Module " + id;
    private Precision bitDepth = Precision.DOUBLE;
    private BigInteger sampleRate = new BigInteger("44100");
    private BigInteger mpfrBits = new BigInteger("64");
    
    protected Parameter[] paramArray; // static parameters, NOT modulation targets
    protected ModIn[] modInArray;
    protected ModOut[] modOutArray;
    public Map<String, Parameter> paramMap;
    public Map<String, ModIn> inModMap;
    public Map<String, ModOut> outModMap;
    
    protected double weightTaskMultiplier = 0;
    protected double weightBitDepthMultiplier = 1;
    protected double weightSampleRateMultiplier = 44100;
    private double weight;
    
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
        
        paramMap = new HashMap<String, Parameter>();
        inModMap = new HashMap<String, ModIn>();
        outModMap = new HashMap<String, ModOut>();
        
        setWeight();        
    }
    
    public void setBitDepth(Precision precision)
    {
        if (precision == Precision.DOUBLE) {
            bitDepth = precision;
            mpfrBits = new BigInteger("64");
            weightBitDepthMultiplier = 1.8;
        } else {
            System.err.printf("Bad precision argument passed to ");
            System.err.printf("setBitDepth method of class Module.%n");
        }
        setWeight();
    }
    
    public void setBitDepth(Precision precision, String bits)
    {
        if (precision == Precision.MULTIPRECISION &&
            ((new BigInteger(bits)).compareTo(new BigInteger("64")) >= 0)) {
            bitDepth = precision;
            mpfrBits = new BigInteger(bits);
            weightBitDepthMultiplier = Double.parseDouble(bits) *
                    0.4602678571428571 +
                    68.54285714285715;
        } else {
            System.err.printf("Bad precision argument passed to ");
            System.err.printf("setBitDepth method of class Module.%n");
        }
        setWeight();
    }
    
    public void setSampleRate(BigInteger sampleRate)
    {
        this.sampleRate = sampleRate;
        weightSampleRateMultiplier = sampleRate.doubleValue();
        setWeight();
    }
    
    public void setWeight()
    {
        weight = weightTaskMultiplier * weightBitDepthMultiplier *
                 weightSampleRateMultiplier;
    }
    
    protected void createMaps()
    {
        for (int i = 0; i < paramArray.length; ++i) {
            paramMap.put(paramArray[i].name, paramArray[i]);
        }
        for (int i = 0; i < modInArray.length; ++i) {
            inModMap.put(modInArray[i].name, modInArray[i]);
        }
        for (int i = 0; i < modOutArray.length; ++i) {
            outModMap.put(modOutArray[i].name, modOutArray[i]);
        }
    }
    
    int getId()
    {
        return id;
    }
    
    String getName()
    {
        return name;
    }
    
    Parameter getParam(String paramName)
    {
        return paramMap.get(paramName);
    }
    
    List<String> getParams()
    {
        List<String> paramList = new ArrayList<String>();
        for (Parameter param: paramArray)
            paramList.add(param.getName());
        return paramList;
    }
    
    ModIn getIn(String modName)
    {
        return inModMap.get(modName);
    }
    
    List<String> getIns()
    {
        List<String> inList = new ArrayList<String>();
        for (ModIn in: modInArray)
            inList.add(in.getName());
        return inList;
    }
    
    ModOut getOut(String modName)
    {
        return outModMap.get(modName);
    }
    
    List<String> getOuts()
    {
        List<String> outList = new ArrayList<String>();
        for (ModOut out: modOutArray)
            outList.add(out.getName());
        return outList;
    }
    
    List<Module> getModulationSources()
    {
        List<Module> modSourceList = new ArrayList<Module>();
        for (ModIn in: modInArray)
            modSourceList.add(in.getSource().getParent());
        return modSourceList;
    }
    
    List<Module> getModulationDestinations()
    {
        List<Module> modDestinationList = new ArrayList<Module>();
        for (ModOut out: modOutArray)
            modDestinationList.add(out.getDestination().getParent());
        return modDestinationList;
    }
    
    public double getWeight()
    {
        return weight;
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
        System.out.printf(fg1.getOut("mainOut").destination.getName() + "%n" +
                          fg2.getOut("auxOut1").destination.getName() + "%n");
        fg1.setBitDepth(Precision.MULTIPRECISION, "99");
        d1.setSampleRate(new BigInteger("384000"));
        System.out.println(fg1.getWeight());
        System.out.println(d1.getWeight());
    }
    
}
