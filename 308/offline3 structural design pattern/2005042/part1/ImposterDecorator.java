public class ImposterDecorator implements iCrews{
    private Crew crew;
    private String red = "\u001B[31m";
    private String reset = "\u001B[0m";
    public ImposterDecorator(Crew crew){
        this.crew=crew;
    }
    public String getName(){
        return crew.getName();
    }
    @Override
    public void repair() {
        crew.repair();
        doDamage();
    }

    @Override
    public void work() {
        crew.work();
        killCrewMate();
    }

    @Override
    public void login() {
        crew.login();
        imposterLogin();
    }

    @Override
    public void logout() {
        crew.logout();
        imposterLogout();
    }
    private void imposterLogin(){
        System.out.println(red+"We won't tell anyone; you are an imposter."+reset);
    }
    private void doDamage(){
        System.out.println(red+"Damaging the spaceship"+reset);
    }
    private void killCrewMate(){
        System.out.println(red+"Trying to kill a crewmate."+reset);
        System.out.println(red+"Succefully killed a crewmate."+reset);
    }
    private void imposterLogout(){
        System.out.println(red+"See you again Comrade Imposter"+reset);
    }
}
