package la.jitco.jana;

public class OptionParameter extends Parameter {
    
    OptionParameter(String name, String[] options)
    {
        super(name, options);
        assert options.length != 0;
        value = options[0];
    }
    
    private boolean contains(String[] stringArray, String string)
    {
        for (String value: stringArray)
            if (value.equals(string))
                return true;
        return false;
    }
    
    public boolean isValid(String input)
    {
        return contains(this.options, input);
    }
    
}
