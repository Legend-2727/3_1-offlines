package Files;

import java.time.Instant;
import java.time.ZonedDateTime;
import java.util.ArrayList;

public interface iContent {
    public String getName();
    public void setName(String name);
    public int getSize();
    public String getType();
    public String getPath();
    public void setPath(String parentPath);
    public int getComponentCount();
    public ZonedDateTime getCreationTime();
    public default void showDetails(){
        showDetails(this.getName());
    }
    public void showDetails(String name);
    public void deleteAll();
}
