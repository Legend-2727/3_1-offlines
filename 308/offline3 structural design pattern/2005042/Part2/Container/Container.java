package Container;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Iterator;

import Files.*;
public abstract class Container implements iContent {
    ArrayList<iContent> contents=new ArrayList<>();
    protected Container parent;
    protected String name;
    protected int size;
    protected String type;
    protected String directory;
    protected ZonedDateTime creationTime;
    protected int contentCount;

    public Container (String name){
        setName(name);
        this.size=0;
        creationTime=ZonedDateTime.now();
        Instant currentInstant = Instant.now();
        contentCount=0;
    }
    public abstract void addContent(iContent content);
    @Override
    public abstract void setPath(String path);
    public boolean find(String name){
        for(iContent cont:contents){
            if(cont.getName().equalsIgnoreCase(name)){
                return true;
            }
        }
        return false;
    }
    public iContent getChild(String name) {
        for(iContent content:contents){
            if(content.getName().equalsIgnoreCase(name)){
                return content;
            }
        }
        return null;
    }

    public void removeContent(iContent content){
        contents.remove(content);
    }
    @Override
    public void setName(String name) {
        this.name=name;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getSize() {
        return size;
    }
    public void incrementSize(int x){
        size+=x;
        if(getParent()!=null){
            getParent().incrementSize(x);
        }
    }
    public void decrementSize(int x){
        size-=x;
        if(getParent()!=null){
            getParent().decrementSize(x);
        }
    }
    @Override
    public String getType() {
        return type;
    }
    @Override
    public String getPath() {
        return directory;
    }
    @Override
    public int getComponentCount() {
        return contents.size();
    }
    public void setContentCount(int count){
        this.contentCount=count;
    }
    @Override
    public ZonedDateTime getCreationTime() {
        return creationTime;
    }
    public Container getParent() {
        return parent;
    }
    public void setParent(Container parent) {
        this.parent = parent;
    }
    public void showDetails(String name){
        for(iContent content:contents) {
            if(content.getName().equalsIgnoreCase(name)) {
                //LocalDateTime localDateTime = LocalDateTime.ofInstant(content.getCreationTime(), ZoneOffset.UTC);
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd 'th' MMMM, yyyy h:mm a");
                String formattedDateTime = creationTime.format(formatter);
                System.out.println("Name: " + content.getName());
                System.out.println("Type: " + content.getType());
                System.out.println("Size: " + content.getSize()+"KB");
                System.out.println("Directory: " + content.getPath());
                System.out.println("Component Count: " + content.getComponentCount());
                System.out.println("Creation time: " + formattedDateTime);
                return;
            }
        }
        System.out.println("Sorry item not found");
    }
    public void delete(String name) {
        for(iContent content:contents){
            if(content.getName().equalsIgnoreCase(name)){
                if(content.getComponentCount()==0){
                    contents.remove(content);
                    return;
                }
                else {
                    System.out.println("Sorry this folder contains other files too.");
                    return;
                }
            }
        }
        System.out.println("Sorry item not found.");
    }
    public void showAllContents() {
        if(contents.isEmpty()){
            System.out.println("Empty folder");
            return;
        }
        for(iContent content:contents){
            System.out.println("--"+content.getName());
        }
    }
    public void deleteAll(){
        ArrayList<iContent> toRemove=new ArrayList<>();
        for (iContent content : contents) {
            if (content.getComponentCount() == 0) {
                toRemove.add(content);
            } else {
                content.deleteAll();
            }
        }
        contents.removeAll(toRemove);
    }
    public void recursiveDelete(String name) {
        //System.out.println(name);
        int deletedSize=0;
        for(iContent content:contents){
            if(content.getName().equalsIgnoreCase(name)){
                if(content instanceof File){
                    System.out.println("This file contain nothing inside to be deleted");
                    System.out.println(content.getName()+" deleted");
                    contents.remove(content);
                    deletedSize+=content.getSize();
                    break;
                }
                else if(content instanceof Container){
                    content.deleteAll();
                    contents.remove(content);
                    deletedSize+=content.getSize();
                    break;
                }
            }
        }
        decrementSize(deletedSize);
    }
}

