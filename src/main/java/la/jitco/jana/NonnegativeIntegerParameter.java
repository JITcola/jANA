package la.jitco.jana;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class NonnegativeIntegerParameter extends Parameter {
    
    static private Pattern re1 = Pattern.compile("\\d+");
    
    NonnegativeIntegerParameter(String name)
    {
        super(name, new String[] {});
        value = "0";
    }
    
    public boolean isValid(String input)
    {
        Matcher match1 = re1.matcher(input);
        if (match1.matches())
                return true;
        return false;
    }

}
