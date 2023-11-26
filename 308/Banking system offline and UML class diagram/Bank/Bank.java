package Bank;

import Accounts.*;
import Employee.*;

import java.util.ArrayList;

public class Bank implements User_interference{
    private static ArrayList<Accounts> all_clients;
    private ArrayList<Employee> all_employees;
    private Accounts active_client;
    private Employee active_employee;
    private static double internal_fund;
    private Integer current_time;
    private ArrayList<LoanData> loan_requests;

    public Bank(){
        all_clients=new ArrayList<>();
        all_employees= new ArrayList<>();
        loan_requests=new ArrayList<>();
        current_time=0;
        internal_fund=1000000;
        System.out.println("Bank.Bank Created");
        all_employees.add(new Managing_director("MD"));
        all_employees.add(new Officer("S1"));
        all_employees.add(new Officer("S2"));
        all_employees.add(new Cashier("C1"));
        all_employees.add(new Cashier("C2"));
        all_employees.add(new Cashier("C3"));
        all_employees.add(new Cashier("C4"));
        all_employees.add(new Cashier("C5"));
    }
    public void serve(String request){
        String[] tokens=request.split(" ");
        try {
            if(tokens[0].equalsIgnoreCase("create")){
                double initial_deposit=Double.parseDouble(tokens[3]);
                if(tokens[2].equalsIgnoreCase("fixed") && initial_deposit<100000){
                    System.out.println("Sorry a fixed account initially must deposit minimum 100000$.");
                    return;
                }
                Accounts temp=openNewAccount(tokens[1],tokens[2],Double.parseDouble(tokens[3]));
                active_client=temp;
            }
            else if (tokens[0].equalsIgnoreCase("deposit")) {
                active_client.deposit(Double.parseDouble(tokens[1]));
            }
            else if (tokens[0].equalsIgnoreCase("withdraw")) {
                withdrawMoney(Double.parseDouble(tokens[1]),current_time);
            }
            else if (tokens[0].equalsIgnoreCase("query")) {
                active_client.query();
            }
            else if (tokens[0].equalsIgnoreCase("request")) {
                addToLoanRequests(Double.parseDouble(tokens[1]));
                System.out.println("Loan request successful, sent for approval.");
            }
            else if (tokens[0].equalsIgnoreCase("close")) {
                if(active_client!=null){
                    System.out.println("Transaction closed for "+active_client.getName());
                    closeClient();
                }
                else if(active_employee!=null){
                    System.out.println("Operations closed for "+active_employee.getName());
                    closeEmployee();
                }
                else{
                    System.out.println("Sorry no account is active to be closed");
                }
            }
            else if (tokens[0].equalsIgnoreCase("open")) {
                if(active_client!=null || active_employee!=null){
                    System.out.println("Invalid command");
                    return;
                }
                for (Employee temp_employee:all_employees){
                    if(temp_employee.getName().equalsIgnoreCase(tokens[1])){
                        activeEmployee(temp_employee);
                        return;
                    }
                }
                activeAccount(tokens[1]);
            }
            else if (tokens[0].equalsIgnoreCase("INC")) {
                current_time+=1;
                System.out.println("1 year has passed.");
                doBalanceIncrement();
                doLoanDecrement();
                deductCharge();
            }
            else if (tokens[0].equalsIgnoreCase("Approve")) {
                if(active_employee!=null){
                    approvePendingRequests();
                }
            }
            else if (tokens[0].equalsIgnoreCase("change")) {
                if(active_employee!=null){
                    active_employee.change_interest_rate(tokens[1],Double.parseDouble(tokens[2]));
                }
            }
            else if (tokens[0].equalsIgnoreCase("lookup")) {
                if(active_employee!=null){
                    active_employee.lookup(tokens[1]);
                }
            }
            else if (tokens[0].equalsIgnoreCase("see")) {
                if(active_employee!=null){
                    active_employee.getInternalFund();
                }
                else {
                    System.out.println("Invalid command");
                }
            }
        }
        catch (Exception e){
            System.out.println("Invalid command");
        }
    }

    private void withdrawMoney(double v, Integer currentTime) {
        if(active_client.withdraw(v,current_time)){
            internal_fund-=v;
        }
    }
    public void approvePendingRequests() {
        if(active_employee==null){
            System.out.println("Invalid command");
            return;
        }
        for(LoanData temp:loan_requests){
            active_employee.approveLoan(temp.getClient(),temp.getLoan_asked());
        }
    }

    public void deductCharge() {
        for(Accounts temp_client:all_clients){
            temp_client.decrementServiceCharge();
        }
    }
    public void doBalanceIncrement() {
        for(Accounts temp_client:all_clients){
            temp_client.applyInterestOnDeposit();
        }
    }

    public void doLoanDecrement() {
        for(Accounts temp_client:all_clients){
            temp_client.applyInterestOnLoan();
        }
    }

    public void activeEmployee(Employee employee) {
        active_employee=employee;
        System.out.println(active_employee.getName()+" active.");
        if(!loan_requests.isEmpty()){
            System.out.println("There are loan approvals pending");
        }
    }
    public void closeEmployee(){
        active_employee=null;
    }
    public void closeClient() {
        active_client=null;
    }

    public void addToLoanRequests(double cash) {
        if(active_client==null){
            System.out.println("Invalid command");
            return;
        }
        LoanData loanData=new LoanData(active_client,cash);
        loan_requests.add(loanData);
    }


    public void activeAccount(String current_client_name) {
        for (Accounts temp_client:all_clients){
            if(temp_client.getName().equalsIgnoreCase(current_client_name)){
                active_client=temp_client;
                System.out.println("Welcome back, "+temp_client.getName());
                return;
            }
        }
    }

    public Accounts openNewAccount(String client_name, String type,double balance) {
        Accounts temp;
        if(type.equalsIgnoreCase("student")){
            temp=new Student_account(client_name,balance,current_time);
        }
        else if(type.equalsIgnoreCase("saving")){
            temp=new Savings_account(client_name,balance,current_time);
        }
        else{
            temp=new Fixed_account(client_name,balance,current_time,1);
        }
        all_clients.add(temp);
        internal_fund+=temp.getBalance();
        return temp;
    }

    public static ArrayList<Accounts> getAll_clients() {
        return all_clients;
    }

    public static double getInternal_fund() {
        return internal_fund;
    }
}
