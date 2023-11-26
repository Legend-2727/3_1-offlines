package Bank;

import Accounts.Accounts;

public interface User_interference {
    public void serve(String req);
    public void approvePendingRequests();

    public void deductCharge();
    public void doBalanceIncrement();

    public void doLoanDecrement();

    public void addToLoanRequests(double cash);

    public Accounts openNewAccount(String client_name, String type, double balance);
}
