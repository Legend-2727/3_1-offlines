package Builder;

import Add_ons.Add_ons;
import Ingredients.Ingredients;

public interface Builder {
    void setPrice(Integer price);
    Integer getPrice();
    void makeLactoseFree();

    void addAddOns(Add_ons addOns);

    void removeIngredient(Ingredients ingredient);
    void addIngredient(Ingredients ingredient);
}
