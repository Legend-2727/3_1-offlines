import Add_ons.*;
import Builder.Director;
import Builder.ShakeMaker;
import Ingredients.Ingredients;
import Shakes.Requestdata;
import Shakes.Shake;
import Shakes.ShakeType;

import java.util.ArrayList;
import java.util.Scanner;

class JuiceCorner{
    Director director=new Director();
    ShakeMaker shakeMaker=new ShakeMaker();
    Requestdata requestdata=new Requestdata();

    public JuiceCorner(){
        System.out.println("Welcome to BUET Juice Corner");
        System.out.println("Press 'o' to open an order 'e' to exit");
    }
    public void serve(String request){
        if(request.equalsIgnoreCase("o")){
            showMenu();
        }
        else {
            System.out.println("Invalid command");
        }
    }

    public void showMenu() {
        System.out.println("Which type of shake you want to order?");
        System.out.println("1. Chocolate Shake");
        System.out.println("2. Coffee Shake");
        System.out.println("3. Strawberry Shake");
        System.out.println("4. Vanilla Shake");
        System.out.println("5. Zero Shake");
        System.out.println("Please enter corresponding no.");
        receiveOrder();
    }

    private void receiveOrder() {
        Scanner scn1=new Scanner(System.in);
        String type= scn1.next();
        if(type.equalsIgnoreCase("e")){
            close();
            return;
        }
        if(type.equals("1")){
            requestdata.setShakeType(ShakeType.CHOCOLATE);
        }
        else if(type.equals("2")){
            requestdata.setShakeType(ShakeType.COFFEE);
        } else if (type.equals("3")) {
            requestdata.setShakeType(ShakeType.STRAWBERRY);
        } else if (type.equals("4")) {
            requestdata.setShakeType(ShakeType.VANILLA);
        } else if (type.equals("5")) {
            requestdata.setShakeType(ShakeType.ZERO);
        }
        else{
            System.out.println("Invalid command");
            showMenu();
            return;
        }
        milkOrAlmond();
    }

    private void milkOrAlmond() {
        System.out.println("Do you want to add milk or else you can have almond milk.");
        System.out.println("Press 1 for milk 2 for almond milk.");
        Scanner scn1=new Scanner(System.in);
        String type= scn1.next();
        if(type.equalsIgnoreCase("e")){
            close();
            return;
        }
        if(type.equals("1")){
            requestdata.setLactosefree(false);
        } else if (type.equals("2")) {
            requestdata.setLactosefree(true);
        }
        else {
            System.out.println("Invalid command");
            milkOrAlmond();
            return;
        }
        System.out.println("Any add-ons you would like?");

        showAddOnMenu();
    }

    private void showAddOnMenu() {
        System.out.println("1. Candy");
        System.out.println("2. Cookies");
        System.out.println("0. Nothing");
        Scanner scn1=new Scanner(System.in);
        String type= scn1.next();
        if(type.equalsIgnoreCase("e")){
            close();
            return;
        }
        if(type.equals("1")){
            requestdata.addAddOns(new Candy());
        } else if (type.equals("2")) {
            requestdata.addAddOns(new Cookies());
        } else if (type.equals("0")) {
            makeShake();
            return;
        } else {
            System.out.println("Invalid command");
            showAddOnMenu();
            return;
        }
        System.out.println("Any more add-ons you would like to add? (y/n)");
        String yn=scn1.next();
        if(yn.equalsIgnoreCase("y")){
            showAddOnMenu();
        }
        else{
            makeShake();
        }
    }

    private void makeShake() {
        if(requestdata.getShakeType()==ShakeType.CHOCOLATE){
            director.makeChocolateShake(shakeMaker,requestdata.getAddOns(), requestdata.isLactosefree());
        } else if (requestdata.getShakeType()==ShakeType.COFFEE) {
            director.makeCoffeShake(shakeMaker,requestdata.getAddOns(), requestdata.isLactosefree());
        } else if (requestdata.getShakeType()==ShakeType.STRAWBERRY) {
            director.makeStrawberryShake(shakeMaker,requestdata.getAddOns(), requestdata.isLactosefree());
        } else if (requestdata.getShakeType()==ShakeType.VANILLA) {
            director.makeVanillaShake(shakeMaker,requestdata.getAddOns(), requestdata.isLactosefree());
        }
        else {
            director.makeZeroShake(shakeMaker,requestdata.getAddOns(), requestdata.isLactosefree());
        }
        System.out.println("Do you want to order another shake? (y/n)");
        Scanner scn1=new Scanner(System.in);
        String yn=scn1.next();
        if(yn.equalsIgnoreCase("y")){
            requestdata=null;
            requestdata=new Requestdata();
            showMenu();
        }
        else {
            shakeMaker.getShakes();
            close();
        }
    }
    public void close(){
        requestdata=null;
        requestdata=new Requestdata();
        System.out.println("Your order has been closed. Hope to see you soon!!");
    }
}
public class Main {

    public static void main(String[] args) {
        JuiceCorner juiceCorner=new JuiceCorner();
        Scanner scn=new Scanner(System.in);

        while(scn.hasNext()){
            String request=scn.nextLine();
            juiceCorner.serve(request);
            System.out.println("Press 'o' to open an order 'e' to exit");
        }
    }
}
