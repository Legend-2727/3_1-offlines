package Server;

import java.io.Serializable;

public class Notification implements Serializable {
    String message;
    public Notification(String msg){
        this.message=msg;
    }
    public String getMessage(){
        return message;
    }
    public void setMessage(String message) {
        this.message = message;
    }
}
