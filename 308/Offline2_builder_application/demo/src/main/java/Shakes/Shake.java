package Shakes;

import Add_ons.Add_ons;
import Ingredients.Ingredients;

import java.util.ArrayList;
import java.util.HashMap;

public class Shake {
    private final ShakeType shakeType;
    private final ArrayList<Ingredients> ingredients=new ArrayList<>();
    private final HashMap<String,Integer> addOns=new HashMap<String, Integer>();
    private final Integer cost;
    public Shake(ShakeType shakeType, ArrayList<Ingredients> ingredients, ArrayList<Add_ons> addOns, Integer cost) {
        this.shakeType = shakeType;
        this.ingredients.addAll(ingredients);
        for(Add_ons ad:addOns){
            if(this.addOns.containsKey(ad.getType())){
                this.addOns.put(ad.getType(),this.addOns.get(ad.getType())+1);
            }
            else{
                this.addOns.put(ad.getType(),1);
            }
        }
        this.cost = cost;
    }
    public void print(){
        System.out.println("Your "+shakeType+" shake. ");
        if(!ingredients.isEmpty()){
            System.out.print("With ");
            for(Ingredients e:ingredients) {
                System.out.print(e + ", ");
            }
            System.out.println();
        }
        if (!addOns.isEmpty()) {
            System.out.print("Adding ");
            for (String temp : addOns.keySet()) {
                System.out.print(addOns.get(temp)+"* "+ temp+", ");
            }
            System.out.println();
        }
        System.out.println("Price: "+cost);
    }
}
