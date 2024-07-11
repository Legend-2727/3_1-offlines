import java.util.ArrayList;
import java.util.Scanner;
class SpaceShip {
    ArrayList<iCrews> crewMates=new ArrayList<>();
    iCrews activeCrew = null;
    public SpaceShip(){
        crewMates=new ArrayList<>();
        activeCrew = null;
    }
    public void serve(String ...words){
        try {
            if (words[0].equalsIgnoreCase("login")) {
                if (activeCrew != null) {
                    System.out.println("Sorry one crew is still active.");
                    return;
                }
                int i = 0;
                for (i = 0; i < crewMates.size(); i++) {
                    if (crewMates.get(i).getName().equalsIgnoreCase(words[1])) {
                        crewMates.get(i).login();
                        activeCrew = crewMates.get(i);
                        break;
                    }
                }
                if (i == crewMates.size()) {
                    if (words[1].substring(0, 3).equalsIgnoreCase("imp")) {
                        ImposterDecorator imposter = new ImposterDecorator(new Crew(words[1]));
                        crewMates.add(imposter);
                        activeCrew = imposter;
                        activeCrew.login();
                    } else {
                        Crew goodCrew = new Crew(words[1]);
                        crewMates.add(goodCrew);
                        goodCrew.login();
                        activeCrew = goodCrew;
                    }
                }
            } else if (activeCrew != null) {
                if (words[0].equalsIgnoreCase("repair")) {
                    activeCrew.repair();
                } else if (words[0].equalsIgnoreCase("work")) {
                    activeCrew.work();
                } else if (words[0].equalsIgnoreCase("logout")) {
                    activeCrew.logout();
                    activeCrew = null;
                } else {
                    System.out.println("Invalid command");
                }
            } else {
                System.out.println("Invalid command");
            }
        }
        catch (Exception e){
            System.out.println("Invalid intput pattern");
        }
    }
}
public class Main {
    public static void main(String[] args) {
        SpaceShip spaceShip=new SpaceShip();
        Scanner scn=new Scanner(System.in);
        while(scn.hasNext()){
            String command= scn.nextLine();
            String[] words=command.split(" ");
            spaceShip.serve(words);
        }
    }
}
