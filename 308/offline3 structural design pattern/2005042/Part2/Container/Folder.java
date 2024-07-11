package Container;

import Files.*;

import java.nio.file.Files;

public class Folder extends Container{
    public Folder(String name, Container parent) {
        super(name);
        setParent(parent);
        setPath(parent.getPath());
        type="Folder";
    }

    @Override
    public void addContent(iContent content) {
        if(content instanceof File || content instanceof Folder){
            contents.add(content);
            incrementSize(content.getSize());
        }
        else {
            System.out.println("Sorry Folder may only contain folders and files.");
        }
    }
    @Override
    public void setPath(String path) {
        directory=path+"\\"+name;
    }
}
