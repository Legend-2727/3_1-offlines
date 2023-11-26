package Employee;

import Accounts.*;
import Bank.*;

public class Managing_director extends Employee{
    public Managing_director(String name){
        super(name);
    }
    public void approveLoan(Accounts client,double amount){
        if((client.getAccountType().equalsIgnoreCase("savings_account") && amount>10000)
            ||(client.getAccountType().equalsIgnoreCase("student_account") && amount>1000)
            ||(client.getAccountType().equalsIgnoreCase("fixed_account") && amount>100000))
        {
            System.out.println("Sorry the maximum allowed loan for this account exceeded.");
            return;
        }
        client.addLoan(amount);
        System.out.println("Loan for "+client.getName()+" approved");
    }
    public void change_interest_rate(String type,double rate){
        if(type.equalsIgnoreCase("savings")){
            Savings_account.setInterest_rate(rate);
        }
        else if(type.equalsIgnoreCase("student")){
            Student_account.setInterest_rate(rate);
        }
        else if(type.equalsIgnoreCase("fixed")){
            Fixed_account.setInterest_rate(rate);
        }
        else{
            Accounts.setLoan_interest(rate);
        }
        System.out.println("Interest rate for "+type+" is changed to"+rate);
    }
    public void getInternalFund(){
        System.out.println("Total fund of this bank is :"+Bank.getInternal_fund()+"$.");
    }
}
