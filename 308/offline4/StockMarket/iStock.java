package StockMarket;

import UserPackage.User;

public interface iStock {
    public void setStockName(String name);
    public String getName();
    public void addSubscriber(User u);
    public void removeSubscriber(User u);
    public void increaseStockPrice(Double d);
    public double getStockPrice();
    public void decreasePrice(Double d);
    public int getStockCount();
    public void changeStockCount(int i);
}
