package Builder;

import Add_ons.*;
import Ingredients.Ingredients;
import Shakes.Shake;
import Shakes.ShakeType;

import java.util.ArrayList;

import static Ingredients.Ingredients.MILK;

public class ShakeMaker implements Builder{
    private Integer price=0;
    private Integer totalPrice=0;
    private ArrayList<Shake> shakes=new ArrayList<>();
    private ShakeType shakeType;
    private ArrayList<Ingredients> ingredients=new ArrayList<>();
    private ArrayList<Add_ons> addOns=new ArrayList<>();
    @Override
    public void setPrice(Integer price) {
        this.price=price;
    }

    @Override
    public Integer getPrice() {
        return price;
    }

    public ShakeType getShakeType() {
        return shakeType;
    }

    public void setShakeType(ShakeType shakeType) {
        this.shakeType = shakeType;
    }

    @Override
    public void makeLactoseFree() {
        removeIngredient(MILK);
        Add_ons tempAddon=new AlmondMilk();
        addOns.add(tempAddon);
        int cost= tempAddon.getIncrementPrice()+price;
        setPrice(cost);
    }

    @Override
    public void addAddOns(Add_ons addOns) {
        this.addOns.add(addOns);
        int newPrice=addOns.getIncrementPrice()+this.price;
        setPrice(newPrice);
    }
    @Override
    public void removeIngredient(Ingredients ingredient){
        this.ingredients.remove(ingredient);
    }
    @Override
    public void addIngredient(Ingredients ingredient){
        this.ingredients.add(ingredient);
    }
    public void addShake(){
        shakes.add(new Shake(shakeType,ingredients,addOns,price));
        totalPrice+=price;
        price=0;
        ingredients.clear();
        addOns.clear();
    }
    public void getShakes(){
        System.out.println("Here is your item(s) and. Have a nice day!!");
        for (Shake shake:
             shakes) {
            shake.print();
        }
        System.out.println("Total cost : "+totalPrice);
        reset();
    }
    public void reset(){
        shakes.clear();
        ingredients.clear();
        addOns.clear();
        shakeType=null;
        totalPrice=0;
        price=0;
    }
}
