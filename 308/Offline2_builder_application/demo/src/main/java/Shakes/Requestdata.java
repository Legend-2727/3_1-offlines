package Shakes;

import Add_ons.Add_ons;
import Ingredients.Ingredients;

import java.util.ArrayList;

public class Requestdata {
    private ShakeType shakeType;
    private ArrayList<Add_ons> addOns=new ArrayList<>();
    private boolean lactosefree=false;

    public boolean isLactosefree() {
        return lactosefree;
    }

    public void setLactosefree(boolean lactosefree) {
        this.lactosefree = lactosefree;
    }

    public void setShakeType(ShakeType shakeType) {
        this.shakeType = shakeType;
    }

    public ShakeType getShakeType() {
        return shakeType;
    }

    public ArrayList<Add_ons> getAddOns() {
        return addOns;
    }

    public void addAddOns(Add_ons addOn) {
        this.addOns.add(addOn);
    }
}
