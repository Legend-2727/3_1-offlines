package Add_ons;

public class AlmondMilk extends Add_ons{
    private final String type="Almond Milk";
    public AlmondMilk(){
        incrementPrice=60;
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
