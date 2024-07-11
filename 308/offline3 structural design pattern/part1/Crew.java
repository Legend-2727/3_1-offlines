public class Crew implements iCrews{
    private String name;
    public Crew(String name){
        this.name=name;
    }
    public String getName(){
        return this.name;
    }
    @Override
    public void repair() {
        System.out.println("Repairing the spaceship.");
    }

    @Override
    public void work() {
        System.out.println("Doing research");
    }

    @Override
    public void login() {
        System.out.println("Welcome Crewmate!");
    }

    @Override
    public void logout() {
        System.out.println("Bye bye crewmate.");
    }
}
