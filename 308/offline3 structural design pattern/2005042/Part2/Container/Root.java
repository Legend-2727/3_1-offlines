package Container;

import Files.iContent;

public class Root extends Container{

    public Root() {
        super("root");
        parent=null;
        setPath("");
        type="Root Folder";
    }

    @Override
    public void setPath(String path) {
        directory=path;
    }

    @Override
    public void addContent(iContent content) {
        if(content instanceof Drive) {
            contents.add(content);
        }
        else{
            System.out.println("Sorry root should only contain drives.");
        }

    }
}
