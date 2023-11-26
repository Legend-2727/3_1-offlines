import Bank.Bank;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Bank newBank= new Bank();
        Scanner take_requests=new Scanner(System.in);
        while (take_requests.hasNext()){
            String request=take_requests.nextLine();
            newBank.serve(request);
        }
    }
}
