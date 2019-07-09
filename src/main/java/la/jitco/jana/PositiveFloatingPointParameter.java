package la.jitco.jana;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class PositiveFloatingPointParameter extends Parameter {
    
    static private Pattern re1 = Pattern.compile("\\d+");
    static private Pattern re2 = Pattern.compile("\\d+\\.\\d*");
    static private Pattern re3 = Pattern.compile("\\.\\d+");
    
    static private Pattern re4 = Pattern.compile("0+");
    static private Pattern re5 = Pattern.compile("0+\\.");
    static private Pattern re6 = Pattern.compile("\\.");
    static private Pattern re7 = Pattern.compile("\\.0+");
    static private Pattern re8 = Pattern.compile("0+\\.0+");
    
    PositiveFloatingPointParameter(String name)
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
        Matcher match7 = re7.matcher(input);
        Matcher match8 = re8.matcher(input);
        if ((match1.matches() == true ||
            match2.matches() == true ||
            match3.matches() == true) &&
            (match4.matches() == false &&
            match5.matches() == false &&
            match6.matches() == false &&
            match7.matches() == false &&
            match8.matches() == false))
            return true;
        return false;
    }

    public static void main(String[] args)
    {
        PositiveFloatingPointParameter testParam = 
            new PositiveFloatingPointParameter("test");
        System.out.println(testParam.isValid("0"));
        System.out.println(testParam.isValid("-0"));
        System.out.println(testParam.isValid("."));
        System.out.println(testParam.isValid("00."));
        System.out.println(testParam.isValid(".000"));
    }
}
