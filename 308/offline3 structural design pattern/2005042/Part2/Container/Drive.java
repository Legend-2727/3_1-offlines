package Container;

import Files.File;
import Files.iContent;

public class Drive extends Container{
    public Drive(String name,Container container) {
        super(name);
        setPath(name);
        type="Driver";
        setParent(container);
    }

    @Override
    public void addContent(iContent content) {
        if(content instanceof File || content instanceof Folder){
            contents.add(content);
            incrementSize(content.getSize());
        }
        else {
            System.out.println("Sorry drive may only contain folders and files.");
        }
    }
    @Override
    public void setPath(String path) {
        directory=path.toUpperCase()+":";
    }
}
