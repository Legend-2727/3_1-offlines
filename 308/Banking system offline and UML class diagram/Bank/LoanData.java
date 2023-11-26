package Bank;

import Accounts.Accounts;

public class LoanData {
    private Accounts client;
    private Double loan_asked;

    public LoanData(Accounts cl, Double cash) {
        client = cl;
        loan_asked = cash;
    }

    public Accounts getClient() {
        return client;
    }

    public double getLoan_asked() {
        return loan_asked;
    }
}
