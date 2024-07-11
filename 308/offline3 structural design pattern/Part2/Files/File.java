package Files;

import java.time.Instant;
import java.time.ZonedDateTime;
import java.util.ArrayList;

public class File implements iContent {
    private String name;
    private int size;
    private String type;
    private String directory;
    private ZonedDateTime creationTime;
    private iContent parent;
    public File(String name,int size,String type,iContent parent){
        setName(name);
        this.size=size;
        this.type=type;
        setParent(parent);
        setPath(parent.getPath());
        creationTime=ZonedDateTime.now();
    }
    @Override
    public void setName(String name) {
        this.name=name;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public int getSize() {
        return size;
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
    public void setPath(String parentPath) {
        this.directory=parentPath+"\\"+name;
    }
    public iContent getParent() {
        return parent;
    }
    public void setParent(iContent parent) {
        this.parent=parent;
    }
    @Override
    public int getComponentCount() {
        return 0;
    }

    @Override
    public ZonedDateTime getCreationTime() {
        return creationTime;
    }
    @Override
    public void showDetails(String name) {
        System.out.println("Name: "+this.name);
        System.out.println("Type: "+type);
        System.out.println("Size: "+size);
        System.out.println("Directory: "+directory);
        System.out.println("Component Count: "+getComponentCount());
        System.out.println("Creation time: "+creationTime);
    }

    @Override
    public void deleteAll() {
        System.out.println("This file contain nothing");
    }
}
