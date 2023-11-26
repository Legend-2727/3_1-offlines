package Accounts;

public class Savings_account extends Accounts {
    public Savings_account(String n, double b,Integer t) {
        super(n, b,t);
        interest_rate=10;
        yearly_charge=500;
    }

    @Override
    public boolean withdraw(double x,Integer t) {
        if(balance-x<1000){
            System.out.println("Invalid transaction. Current Balance :"+balance);
            return false;
        }
        else {
            balance-=x;
            System.out.println("Successfully withdrawn. Current Balance :"+balance);
            return true;
        }
    }
//    public static void setInterest_rate(Integer interest_rate) {
//        Savings_account.interest_rate = interest_rate;
//    }
}
