package Builder;

import Add_ons.Add_ons;
import Ingredients.Ingredients;
import Shakes.ShakeType;

import java.util.ArrayList;

public class Director {
    public void makeChocolateShake(ShakeMaker shakeMaker, ArrayList<Add_ons> addOns,boolean isLactoseFree){
        shakeMaker.setShakeType(ShakeType.CHOCOLATE);
        shakeMaker.addIngredient(Ingredients.CHOCOLATE_ICECREAM);
        shakeMaker.addIngredient(Ingredients.CHOCOLATE_SYRUP);
        shakeMaker.addIngredient(Ingredients.SUGAR);
        shakeMaker.setPrice(230);
        if (isLactoseFree){
            shakeMaker.makeLactoseFree();
        }
        for(Add_ons ad:addOns){
            shakeMaker.addAddOns(ad);
        }
        shakeMaker.addShake();
    }
    public void makeCoffeShake(ShakeMaker shakeMaker, ArrayList<Add_ons> addOns,boolean isLactoseFree){
        shakeMaker.setShakeType(ShakeType.COFFEE);
        shakeMaker.addIngredient(Ingredients.COFFEE);
        shakeMaker.addIngredient(Ingredients.JELLO);
        shakeMaker.addIngredient(Ingredients.SUGAR);
        shakeMaker.setPrice(250);
        if (isLactoseFree){
            shakeMaker.makeLactoseFree();
        }
        for(Add_ons ad:addOns){
            shakeMaker.addAddOns(ad);
        }
        shakeMaker.addShake();
    }
    public void makeStrawberryShake(ShakeMaker shakeMaker, ArrayList<Add_ons> addOns,boolean isLactoseFree){
        shakeMaker.setShakeType(ShakeType.STRAWBERRY);
        shakeMaker.addIngredient(Ingredients.STRAWBERRY_ICECREAM);
        shakeMaker.addIngredient(Ingredients.STRAWBERRY_SYRUP);
        shakeMaker.addIngredient(Ingredients.SUGAR);
        shakeMaker.setPrice(200);
        if (isLactoseFree){
            shakeMaker.makeLactoseFree();
        }
        for(Add_ons ad:addOns){
            shakeMaker.addAddOns(ad);
        }
        shakeMaker.addShake();
    }
    public void makeVanillaShake(ShakeMaker shakeMaker, ArrayList<Add_ons> addOns,boolean isLactoseFree){
        shakeMaker.setShakeType(ShakeType.VANILLA);
        shakeMaker.addIngredient(Ingredients.VANILLA);
        shakeMaker.addIngredient(Ingredients.JELLO);
        shakeMaker.addIngredient(Ingredients.SUGAR);
        shakeMaker.setPrice(190);
        if (isLactoseFree){
            shakeMaker.makeLactoseFree();
        }
        for(Add_ons ad:addOns){
            shakeMaker.addAddOns(ad);
        }
        shakeMaker.addShake();
    }
    public void makeZeroShake(ShakeMaker shakeMaker, ArrayList<Add_ons> addOns,boolean isLactoseFree){
        shakeMaker.setShakeType(ShakeType.ZERO);
        shakeMaker.addIngredient(Ingredients.VANILLA);
        shakeMaker.addIngredient(Ingredients.SUGAR_FREE_JELLO);
        shakeMaker.addIngredient(Ingredients.SWEETENER);
        shakeMaker.setPrice(240);
        if (isLactoseFree){
            shakeMaker.makeLactoseFree();
        }
        for(Add_ons ad:addOns){
            shakeMaker.addAddOns(ad);
        }
        shakeMaker.addShake();
    }

}
