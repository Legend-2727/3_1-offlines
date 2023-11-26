package Employee;

import Accounts.Accounts;

public class Officer extends Employee{

    public Officer(String name) {
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
}
