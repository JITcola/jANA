package la.jitco.jana;

abstract public class Parameter {
    
    protected final String name;
    protected final String[] options;
    protected String value;
        
    Parameter(String name, String[] options)
    {
        this.name = name;
        this.options = options;
        this.value = null;
    }
    
    abstract protected boolean isValid(String input);
    
    public String getName()
    {
        return name;
    }
    
    public String[] getOptions()
    {
        return options;
    }
    
    public String getValue()
    {
        return value;
    }
    
    public void setValue(String value)
    {
        assert isValid(value);
        this.value = value;
    };

}
