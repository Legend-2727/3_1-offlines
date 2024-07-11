package UserPackage;

import StockMarket.*;

import java.util.ArrayList;

public interface iUser {
    public void setName(String name);
    public String getName();
    public ArrayList<Stock> getStockList();
    public void addStock(Stock s);
    public void removeStock(Stock s);
}
