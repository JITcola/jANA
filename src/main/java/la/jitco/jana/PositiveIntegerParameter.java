package la.jitco.jana;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class PositiveIntegerParameter extends Parameter {
    
    static private Pattern re1 = Pattern.compile("\\d+");
    static private Pattern re2 = Pattern.compile("0+");
    
    PositiveIntegerParameter(String name)
    {
        super(name, new String[] {});
        value = "1";
    }
    
    public boolean isValid(String input)
    {
        Matcher match1 = re1.matcher(input);
        Matcher match2 = re2.matcher(input);
        if (match1.matches() && (!match2.matches()))
                return true;
        return false;
    }

}
