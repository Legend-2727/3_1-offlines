package Accounts;

import Accounts.Accounts;

public class Student_account extends Accounts {

    public Student_account(String n, double b,Integer t) {
        super(n, b,t);
        interest_rate=5;
        yearly_charge=0;
    }

    @Override
    public boolean withdraw(double x,Integer t) {
        if(x>=10000){
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
//        Student_account.interest_rate = interest_rate;
//    }
}
