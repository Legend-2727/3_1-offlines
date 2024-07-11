package StockMarket;

import UserPackage.User;

import java.util.ArrayList;

public class Stock implements iStock{
    private int stockCount;
    private Double stockPrice;
    private String stockName;
    ArrayList<User> subscriberList;

    @Override
    public void setStockName(String name) {
        this.stockName=name;
    }

    @Override
    public String getName() {
        return stockName;
    }

    @Override
    public void addSubscriber(User u) {
        subscriberList.add(u);
    }

    @Override
    public void removeSubscriber(User u) {
        subscriberList.remove(u);
    }

    @Override
    public void increaseStockPrice(Double d) {
        stockPrice+=d;
    }

    @Override
    public double getStockPrice() {
        return stockPrice;
    }

    @Override
    public void decreasePrice(Double d) {
        stockPrice-=d;
    }

    @Override
    public int getStockCount() {
        return stockCount;
    }

    @Override
    public void changeStockCount(int i) {
        if(i<0){
            System.out.println("Sorry count cannot be negative");
        }
        else{
            stockCount=i;
        }
    }
}
