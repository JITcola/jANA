package la.jitco.jana;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class FloatingPointParameter extends Parameter {
    
    static private Pattern re1 = Pattern.compile("-\\d+");
    static private Pattern re2 = Pattern.compile("-\\d+\\.\\d*");
    static private Pattern re3 = Pattern.compile("-\\.\\d+");
    static private Pattern re4 = Pattern.compile("\\d+");
    static private Pattern re5 = Pattern.compile("\\d+\\.\\d*");
    static private Pattern re6 = Pattern.compile("\\.\\d+");
    
    FloatingPointParameter(String name)
    {
        super(name, new String[] {});
        value = "0.0";
    }
    
    public boolean isValid(String input)
    {
        Matcher match1 = re1.matcher(input);
        Matcher match2 = re2.matcher(input);
        Matcher match3 = re3.matcher(input);
        Matcher match4 = re4.matcher(input);
        Matcher match5 = re5.matcher(input);
        Matcher match6 = re6.matcher(input);
        if (match1.matches() == true ||
            match2.matches() == true ||
            match3.matches() == true ||
            match4.matches() == true ||
            match5.matches() == true ||
            match6.matches() == true)
            return true;
        return false;
    }
    
    public static void main(String[] args)
    {
        FloatingPointParameter testParam = new FloatingPointParameter("test");
        System.out.println(testParam.isValid("-.314"));
        System.out.println(testParam.isValid(".314"));
        System.out.println(testParam.isValid("-0.314"));
        System.out.println(testParam.isValid("0.314"));
        System.out.println(testParam.isValid("-"));
        System.out.println(testParam.isValid("-3.14"));
        System.out.println(testParam.isValid("3.14"));
    }

}
