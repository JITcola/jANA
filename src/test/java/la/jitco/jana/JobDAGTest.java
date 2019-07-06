package la.jitco.jana;

import java.math.BigInteger;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class JobDAGTest {
    
    static Patch testPatch1;
    static Patch testPatch2;
    static JobDAG jobDAG1;
    static JobDAG jobDAG2;
    static Job component_jobDAG1_0 = null;
    static Job component_jobDAG1_1 = null;
    static Job component_jobDAG1_2 = null;
    static Job component_jobDAG1_3 = null;
    static Job component_jobDAG1_5 = null;
    static Job component_jobDAG1_6 = null;
    static Job component_jobDAG1_12 = null;
    static Job component_jobDAG1_13 = null;
    static Job component_jobDAG1_15 = null;
    static Job component_jobDAG2_0 = null;
    static Job component_jobDAG2_6 = null;
    static Job component_jobDAG2_10 = null;
    
    static {
        
        testPatch1 = new Patch();
        testPatch2 = new Patch();
        
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("Delay");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.addModule("FunctionGenerator");
        testPatch1.getModuleList().get(3).setSampleRate(new BigInteger("96000"));
        testPatch1.getModuleList().get(3).setBitDepth(Precision.MULTIPRECISION, "512");
        testPatch1.getModuleList().get(8).setSampleRate(new BigInteger("192000"));
        testPatch1.getModuleList().get(8).setBitDepth(Precision.MULTIPRECISION, "1024");
        testPatch1.getModuleList().get(14).setSampleRate(new BigInteger("384000"));
        testPatch1.getModuleList().get(14).setBitDepth(Precision.MULTIPRECISION, "128");
        testPatch1.getModuleList().get(1).getOut("mainOut").modulate(testPatch1.getModuleList().get(2).getIn("frequency"));
        testPatch1.getModuleList().get(2).getOut("mainOut").modulate(testPatch1.getModuleList().get(3).getIn("frequency"));
        testPatch1.getModuleList().get(2).getOut("auxOut1").modulate(testPatch1.getModuleList().get(4).getIn("frequency"));
        testPatch1.getModuleList().get(3).getOut("mainOut").modulate(testPatch1.getModuleList().get(4).getIn("phase"));
        testPatch1.getModuleList().get(3).getOut("auxOut1").modulate(testPatch1.getModuleList().get(5).getIn("frequency"));
        testPatch1.getModuleList().get(4).getOut("mainOut").modulate(testPatch1.getModuleList().get(3).getIn("phase"));
        testPatch1.getModuleList().get(4).getOut("auxOut1").modulate(testPatch1.getModuleList().get(5).getIn("phase"));
        testPatch1.getModuleList().get(6).getOut("mainOut").modulate(testPatch1.getModuleList().get(7).getIn("frequency"));
        testPatch1.getModuleList().get(7).getOut("mainOut").modulate(testPatch1.getModuleList().get(8).getIn("frequency"));
        testPatch1.getModuleList().get(8).getOut("mainOut").modulate(testPatch1.getModuleList().get(9).getIn("input"));
        testPatch1.getModuleList().get(9).getOut("mainOut").modulate(testPatch1.getModuleList().get(10).getIn("frequency"));
        testPatch1.getModuleList().get(10).getOut("mainOut").modulate(testPatch1.getModuleList().get(11).getIn("frequency"));
        testPatch1.getModuleList().get(11).getOut("mainOut").modulate(testPatch1.getModuleList().get(6).getIn("frequency"));
        testPatch1.getModuleList().get(11).getOut("auxOut1").modulate(testPatch1.getModuleList().get(9).getIn("time"));
        testPatch1.getModuleList().get(12).getOut("mainOut").modulate(testPatch1.getModuleList().get(13).getIn("frequency"));
        testPatch1.getModuleList().get(13).getOut("mainOut").modulate(testPatch1.getModuleList().get(14).getIn("frequency"));
        testPatch1.getModuleList().get(14).getOut("mainOut").modulate(testPatch1.getModuleList().get(13).getIn("phase"));
        testPatch1.getModuleList().get(5).getOut("mainOut").modulate(testPatch1.getModuleList().get(15).getIn("frequency"));
        testPatch1.getModuleList().get(8).getOut("auxOut1").modulate(testPatch1.getModuleList().get(15).getIn("phase"));
        testPatch1.getModuleList().get(14).getOut("auxOut1").modulate(testPatch1.getModuleList().get(15).getIn("level"));
        testPatch1.getModuleList().get(15).getOut("mainOut").modulate(testPatch1.getModuleList().get(0).getIn("frequency"));
        testPatch1.setOut(testPatch1.getModuleList().get(0).getOut("mainOut"));
        
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("Delay");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("FunctionGenerator");
        testPatch2.addModule("Delay");
        testPatch2.getModuleList().get(1).setSampleRate(new BigInteger("768000"));
        testPatch2.getModuleList().get(1).setBitDepth(Precision.MULTIPRECISION, "1024");
        testPatch2.getModuleList().get(7).setSampleRate(new BigInteger("96000"));
        testPatch2.getModuleList().get(7).setBitDepth(Precision.MULTIPRECISION, "512");
        testPatch2.getModuleList().get(0).getOut("mainOut").modulate(testPatch2.getModuleList().get(1).getIn("frequency"));
        testPatch2.getModuleList().get(0).getOut("auxOut1").modulate(testPatch2.getModuleList().get(2).getIn("phase"));
        testPatch2.getModuleList().get(1).getOut("mainOut").modulate(testPatch2.getModuleList().get(2).getIn("frequency"));
        testPatch2.getModuleList().get(1).getOut("auxOut1").modulate(testPatch2.getModuleList().get(3).getIn("phase"));
        testPatch2.getModuleList().get(2).getOut("mainOut").modulate(testPatch2.getModuleList().get(3).getIn("frequency"));
        testPatch2.getModuleList().get(2).getOut("auxOut1").modulate(testPatch2.getModuleList().get(4).getIn("phase"));
        testPatch2.getModuleList().get(3).getOut("mainOut").modulate(testPatch2.getModuleList().get(4).getIn("frequency"));
        testPatch2.getModuleList().get(3).getOut("auxOut1").modulate(testPatch2.getModuleList().get(5).getIn("phase"));
        testPatch2.getModuleList().get(4).getOut("mainOut").modulate(testPatch2.getModuleList().get(5).getIn("frequency"));
        testPatch2.getModuleList().get(4).getOut("auxOut1").modulate(testPatch2.getModuleList().get(0).getIn("phase"));
        testPatch2.getModuleList().get(5).getOut("mainOut").modulate(testPatch2.getModuleList().get(0).getIn("frequency"));
        testPatch2.getModuleList().get(5).getOut("auxOut1").modulate(testPatch2.getModuleList().get(1).getIn("phase"));
        testPatch2.getModuleList().get(3).getOut("auxOut2").modulate(testPatch2.getModuleList().get(10).getIn("input"));
        testPatch2.getModuleList().get(6).getOut("mainOut").modulate(testPatch2.getModuleList().get(7).getIn("frequency"));
        testPatch2.getModuleList().get(7).getOut("mainOut").modulate(testPatch2.getModuleList().get(8).getIn("frequency"));
        testPatch2.getModuleList().get(7).getOut("auxOut1").modulate(testPatch2.getModuleList().get(6).getIn("input"));
        testPatch2.getModuleList().get(8).getOut("mainOut").modulate(testPatch2.getModuleList().get(9).getIn("frequency"));
        testPatch2.getModuleList().get(8).getOut("auxOut1").modulate(testPatch2.getModuleList().get(7).getIn("phase"));
        testPatch2.getModuleList().get(9).getOut("mainOut").modulate(testPatch2.getModuleList().get(10).getIn("time"));
        testPatch2.getModuleList().get(9).getOut("auxOut1").modulate(testPatch2.getModuleList().get(8).getIn("phase"));
        testPatch2.setOut(testPatch2.getModuleList().get(10).getOut("mainOut"));

        jobDAG1 = new JobDAG(new ModuleGraph(testPatch1), testPatch1);
        jobDAG2 = new JobDAG(new ModuleGraph(testPatch2), testPatch2);
        
        
        
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(0))) {
                component_jobDAG1_0 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(1))) {
                component_jobDAG1_1 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(2))) {
                component_jobDAG1_2 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(3))) {
                component_jobDAG1_3 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(5))) {
                component_jobDAG1_5 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(6))) {
                component_jobDAG1_6 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(12))) {
                component_jobDAG1_12 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(13))) {
                component_jobDAG1_13 = job;
                break;
            }
        for (Job job: jobDAG1.dag)
            if (job.moduleList.contains(testPatch1.getModuleList().get(15))) {
                component_jobDAG1_15 = job;
                break;
            }
        
        for (Job job: jobDAG2.dag)
            if (job.moduleList.contains(testPatch2.getModuleList().get(0))) {
                component_jobDAG2_0 = job;
                break;
            }
        for (Job job: jobDAG2.dag)
            if (job.moduleList.contains(testPatch2.getModuleList().get(6))) {
                component_jobDAG2_6 = job;
                break;
            }
        for (Job job: jobDAG2.dag)
            if (job.moduleList.contains(testPatch2.getModuleList().get(10))) {
                component_jobDAG2_10 = job;
                break;
            }
    }

    @org.junit.jupiter.api.Test
    public void testCreateJobs() {
        
        assertEquals(9, jobDAG1.dag.size());
        assertEquals(3, jobDAG2.dag.size());
        
        assertEquals(1, component_jobDAG1_0.moduleList.size());
        assertEquals(1, component_jobDAG1_1.moduleList.size());
        assertEquals(1, component_jobDAG1_2.moduleList.size());
        assertEquals(2, component_jobDAG1_3.moduleList.size());
        assertEquals(1, component_jobDAG1_5.moduleList.size());
        assertEquals(6, component_jobDAG1_6.moduleList.size());
        assertEquals(1, component_jobDAG1_12.moduleList.size());
        assertEquals(2, component_jobDAG1_13.moduleList.size());
        assertEquals(1, component_jobDAG1_15.moduleList.size());
        
        assertEquals(6, component_jobDAG2_0.moduleList.size());
        assertEquals(4, component_jobDAG2_6.moduleList.size());
        assertEquals(1, component_jobDAG2_10.moduleList.size());
        
        assertTrue(component_jobDAG1_3.moduleList.contains(testPatch1.getModuleList().get(4)));
        assertTrue(component_jobDAG1_6.moduleList.contains(testPatch1.getModuleList().get(11)));
        assertTrue(component_jobDAG1_13.moduleList.contains(testPatch1.getModuleList().get(14)));
        
        assertTrue(component_jobDAG2_0.moduleList.contains(testPatch2.getModuleList().get(5)));
        assertTrue(component_jobDAG2_6.moduleList.contains(testPatch2.getModuleList().get(9)));
        
    }

    @org.junit.jupiter.api.Test
    public void testSetJobAdjacenciesAndDependencies() {
        
        assertTrue(component_jobDAG1_0.dependencies.contains(component_jobDAG1_15));
        assertTrue(component_jobDAG1_0.adjacentJobs.isEmpty());
        assertTrue(component_jobDAG1_1.dependencies.isEmpty());
        assertTrue(component_jobDAG1_1.adjacentJobs.contains(component_jobDAG1_2));
        assertTrue(component_jobDAG1_2.dependencies.contains(component_jobDAG1_1));
        assertTrue(component_jobDAG1_2.adjacentJobs.contains(component_jobDAG1_3));
        assertTrue(component_jobDAG1_3.dependencies.contains(component_jobDAG1_2));
        assertTrue(component_jobDAG1_3.adjacentJobs.contains(component_jobDAG1_5));
        assertTrue(component_jobDAG1_5.dependencies.contains(component_jobDAG1_3));
        assertTrue(component_jobDAG1_5.adjacentJobs.contains(component_jobDAG1_15));
        assertTrue(component_jobDAG1_6.dependencies.isEmpty());
        assertTrue(component_jobDAG1_6.adjacentJobs.contains(component_jobDAG1_15));
        assertTrue(component_jobDAG1_12.dependencies.isEmpty());
        assertTrue(component_jobDAG1_12.adjacentJobs.contains(component_jobDAG1_13));
        assertTrue(component_jobDAG1_13.dependencies.contains(component_jobDAG1_12));
        assertTrue(component_jobDAG1_13.adjacentJobs.contains(component_jobDAG1_15));
        assertTrue(component_jobDAG1_15.dependencies.contains(component_jobDAG1_5) &&
                   component_jobDAG1_15.dependencies.contains(component_jobDAG1_6) &&
                   component_jobDAG1_15.dependencies.contains(component_jobDAG1_13));
        assertTrue(component_jobDAG1_15.adjacentJobs.contains(component_jobDAG1_0));
        
        assertTrue(component_jobDAG2_0.dependencies.isEmpty());
        assertTrue(component_jobDAG2_0.adjacentJobs.contains(component_jobDAG2_10));
        assertTrue(component_jobDAG2_6.dependencies.isEmpty());
        assertTrue(component_jobDAG2_6.adjacentJobs.contains(component_jobDAG2_10));
        assertTrue(component_jobDAG2_10.dependencies.contains(component_jobDAG2_0) &&
                   component_jobDAG2_10.dependencies.contains(component_jobDAG2_6));
        assertTrue(component_jobDAG2_10.adjacentJobs.isEmpty());
        
    }

    @org.junit.jupiter.api.Test
    public void testFilterDependencies() {
        
        testPatch1.setOut(testPatch1.getModuleList().get(5).getOut("mainOut"));
        testPatch2.setOut(testPatch2.getModuleList().get(3).getOut("mainOut"));
        
        JobDAG testDAG1 = new JobDAG(new ModuleGraph(testPatch1), testPatch1);
        JobDAG testDAG2 = new JobDAG(new ModuleGraph(testPatch2), testPatch2);
        
        assertEquals(4, testDAG1.dag.size());
        assertEquals(1, testDAG2.dag.size());
        
        testPatch1.setOut(testPatch1.getModuleList().get(15).getOut("mainOut"));
        testPatch2.setOut(testPatch2.getModuleList().get(8).getOut("mainOut"));
        
        JobDAG testDAG3 = new JobDAG(new ModuleGraph(testPatch1), testPatch1);
        JobDAG testDAG4 = new JobDAG(new ModuleGraph(testPatch2), testPatch2);
        
        assertEquals(8, testDAG3.dag.size());
        assertEquals(1, testDAG4.dag.size());
        
        testPatch1.setOut(testPatch1.getModuleList().get(0).getOut("mainOut"));
        testPatch2.setOut(testPatch2.getModuleList().get(10).getOut("mainOut"));
        
    }

    @org.junit.jupiter.api.Test
    public void testSetJobBitDepthsAndSampleRates() {
         
        assertTrue(component_jobDAG1_0.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_0.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_0.getSampleRate().equals(new BigInteger("44100")));
        assertTrue(component_jobDAG1_1.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_1.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_1.getSampleRate().equals(new BigInteger("44100")));
        assertTrue(component_jobDAG1_2.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_2.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_2.getSampleRate().equals(new BigInteger("44100")));
        assertTrue(component_jobDAG1_3.getBitDepth() == Precision.MULTIPRECISION &&
                   component_jobDAG1_3.getMpfrBits().equals(new BigInteger("512")) &&
                   component_jobDAG1_3.getSampleRate().equals(new BigInteger("96000")));
        assertTrue(component_jobDAG1_5.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_5.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_5.getSampleRate().equals(new BigInteger("44100")));
        assertTrue(component_jobDAG1_6.getBitDepth() == Precision.MULTIPRECISION &&
                   component_jobDAG1_6.getMpfrBits().equals(new BigInteger("1024")) &&
                   component_jobDAG1_6.getSampleRate().equals(new BigInteger("192000")));
        assertTrue(component_jobDAG1_12.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_12.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_12.getSampleRate().equals(new BigInteger("44100")));
        assertTrue(component_jobDAG1_13.getBitDepth() == Precision.MULTIPRECISION &&
                   component_jobDAG1_13.getMpfrBits().equals(new BigInteger("128")) &&
                   component_jobDAG1_13.getSampleRate().equals(new BigInteger("384000")));
        assertTrue(component_jobDAG1_15.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG1_15.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG1_15.getSampleRate().equals(new BigInteger("44100")));
        
        assertTrue(component_jobDAG2_0.getBitDepth() == Precision.MULTIPRECISION &&
                   component_jobDAG2_0.getMpfrBits().equals(new BigInteger("1024")) &&
                   component_jobDAG2_0.getSampleRate().equals(new BigInteger("768000")));
        assertTrue(component_jobDAG2_6.getBitDepth() == Precision.MULTIPRECISION &&
                   component_jobDAG2_6.getMpfrBits().equals(new BigInteger("512")) &&
                   component_jobDAG2_6.getSampleRate().equals(new BigInteger("96000")));
        assertTrue(component_jobDAG2_10.getBitDepth() == Precision.DOUBLE &&
                   component_jobDAG2_10.getMpfrBits().equals(new BigInteger("64")) &&
                   component_jobDAG2_10.getSampleRate().equals(new BigInteger("44100")));
        
    }
    
}
