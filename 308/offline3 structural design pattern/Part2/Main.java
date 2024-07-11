import Container.*;
import Container.Drive;
import Container.Root;
import Files.File;
import Files.iContent;

import java.util.ArrayList;
import java.util.Scanner;
class MyComputer{
    Root root;
    Container activeContainer;
    public MyComputer(){
        root=new Root();
        activeContainer=root;
    }
    public void serve(String ...keywords){
        try {
            if (keywords[0].equals("mkdrive")) {
                if (root.find(keywords[1])) {
                    System.out.println("Sorry same drive already exists");
                } else {
                    Drive drive = new Drive(keywords[1], root);
                    activeContainer.addContent(drive);
                }
            } else if (keywords[0].equals("cd")) {
                if (keywords[1].equals("~")) {
                    activeContainer = root;
                    System.out.print(activeContainer.getPath() + "->  ");
                    return;
                }
                iContent temp = activeContainer.getChild(keywords[1]);
                if (temp instanceof File) {
                    System.out.println("Sorry you can't redirect inside a file");
                } else {
                    Container tempContainer = (Container) temp;
                    if (tempContainer == null) {
                        System.out.println("Sorry this content doesn't contain your file");
                    } else {
                        activeContainer = tempContainer;
                    }
                }
            } else if (keywords[0].equals("ls")) {
                activeContainer.showDetails(keywords[1]);
            } else if (keywords[0].equals("list")) {
                activeContainer.showAllContents();
            } else if (keywords[0].equals("delete")) {
                if (keywords[1].equals("-r")) {
                    //System.out.println("here");
                    activeContainer.recursiveDelete(keywords[2]);
                } else {
                    activeContainer.delete(keywords[1]);
                }
            } else if (keywords[0].equals("mkdir")) {
                if (activeContainer.find(keywords[1])) {
                    System.out.println("Folder with the same name cannot exist");
                } else {
                    Folder folder = new Folder(keywords[1], activeContainer);
                    activeContainer.addContent(folder);
                }
            } else if (keywords[0].equals("touch")) {
                String name = keywords[1];
                int size = Integer.parseInt(keywords[2]);
                String[] words = keywords[1].split("\\.");
                String type = words[1];
                File file = new File(name, size, type, activeContainer);
                activeContainer.addContent(file);
            } else if (keywords[0].equals("exit")) {
                System.exit(0);
            }
        }
        catch (Exception e){
            System.out.println("Invalid command.");
        }
        System.out.print(activeContainer.getPath() + "->  ");
    }
}
public class Main {
    public static void main(String[] args) {
        MyComputer myComputer=new MyComputer();
        Scanner scn=new Scanner(System.in);
        System.out.print("->  ");
        while (scn.hasNext()) {
            String command = scn.nextLine();
            String[] words = command.split(" ");
            myComputer.serve(words);
        }
    }
}
//mkdrive c
//cd C
//mkdir m
//mkdir v
//cd m
//mkdir m1
//mkdir m2
//touch 1.mp3 1
//touch 2.mp3 2
//cd m1
//touch 3.mp3 3
//cd ~
//cd c
//delete -r m