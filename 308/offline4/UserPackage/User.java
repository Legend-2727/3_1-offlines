package UserPackage;

import StockMarket.Stock;

import java.util.ArrayList;

public class User implements iUser{
    private String name;
    private ArrayList<Stock> stockList;
    @Override
    public void setName(String name) {
        this.name=name;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public ArrayList<Stock> getStockList() {
        return stockList;
    }

    @Override
    public void addStock(Stock s) {
        stockList.add(s);
    }

    @Override
    public void removeStock(Stock s) {
        stockList.remove(s);
    }
}
