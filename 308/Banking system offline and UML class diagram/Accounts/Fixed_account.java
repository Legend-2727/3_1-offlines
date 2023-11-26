package Accounts;

public class Fixed_account extends Accounts{
    Integer time_period;
    public Fixed_account(String n, double b,Integer t,Integer period) {
        super(n,b,t);
        interest_rate=15;
        yearly_charge=500;
        time_period=period;
    }

    @Override
    public void deposit(double x) {
        if(x<50000){
            System.out.println("Sorry, for fixed account minimum deposit is 50000$");
            return;
        }
        balance+=x;
        System.out.println(x+"$ deposited. Current Balance "+balance+"$ ");
    }

    @Override
    public boolean withdraw(double x,Integer t) {
        if(time-t<time_period){
            System.out.println("Sorry you can't withdraw until "+time_period+" has passed.");
            return false;
        }
        else{
            balance-=x;
            return true;
        }
    }
    //    public static void setInterest_rate(Integer interest_rate) {
//        Fixed_account.interest_rate = interest_rate;
//    }
}
