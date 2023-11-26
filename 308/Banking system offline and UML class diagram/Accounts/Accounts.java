package Accounts;

public abstract class Accounts {
    String name;
    double balance;
    double loan;
    Integer time;
    protected static double interest_rate;
    protected static double loan_interest;
    double yearly_charge;
    public Accounts(String n,double b,Integer t){
        name=n;
        balance=b;
        loan=0;
        time=t;
        loan_interest=10;
        System.out.println(getAccountType()+" for "+name+" created. Initial balance "+balance+"$.");
    }

    public static void setLoan_interest(double rate) {
        loan_interest=rate;
    }

    public void deposit(double x){
        balance+=x;
        System.out.println(x+"$ deposited. Current Balance "+balance+"$ ");
    }
    public boolean withdraw(double x,Integer t){
        balance-=x;
        return true;
    }
    public void addLoan(double x){
        loan+=x;
        balance+=x;
    }
    public void query(){
        System.out.println("Current Balance : "+balance+", Loan : "+loan);
    }
    public String getAccountType()
    {
        return this.getClass().getSimpleName();
    }
    public String getName(){
        return  name;
    }
    public double getBalance() {
        return balance;
    }
    public void applyInterestOnLoan(){
        balance-=loan_interest*loan/100;
    }
    public void applyInterestOnDeposit(){
        balance+=interest_rate*balance/100;
    }
    public static void setInterest_rate(double rate) {
        interest_rate = rate;
    }

    public void decrementServiceCharge() {
        balance-=yearly_charge;
    }

}

