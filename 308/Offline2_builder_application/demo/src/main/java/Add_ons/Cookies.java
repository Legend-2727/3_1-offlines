package Add_ons;

public class Cookies extends Add_ons{
    private final String type="Cookies";
    public Cookies(){
        incrementPrice=40;
    }
    @Override
    public Integer getIncrementPrice() {
        return incrementPrice;
    }

    @Override
    public String getType() {
        return type;
    }
}
