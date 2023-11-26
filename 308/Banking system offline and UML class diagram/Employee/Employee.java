package Employee;

import Accounts.*;
import Bank.*;

public abstract class Employee {
    private String name;
    public Employee(String name){
        this.name=name;
        System.out.print(name+" created, ");
    }
    public void lookup(String client_name){
        for(Accounts temp_client:Bank.getAll_clients()){
            if(temp_client.getName().equalsIgnoreCase(client_name)){
                temp_client.query();
                return;
            }
        }
    }
    public void approveLoan(Accounts client,double amount){
        System.out.println("You don't have permission to do this.");
    }
    public void change_interest_rate(String type,double rate){
        System.out.println("You don't have permission to do this.");
    }
    public void getInternalFund(){
        System.out.println("You don't have permission to do this.");
    }
    public String getName() {
        return name;
    }
}
