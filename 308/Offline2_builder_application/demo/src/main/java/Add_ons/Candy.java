package Add_ons;

public class Candy extends Add_ons{
    private final String type="Candy";
    public Candy(){
        incrementPrice=50;
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
