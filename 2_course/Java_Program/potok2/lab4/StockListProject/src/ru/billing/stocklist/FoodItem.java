package ru.billing.stocklist;

import java.util.Date;

public class FoodItem extends GenericItem {
    private Date dateOfIncome;
    private short expires;

    public Date getDate() {
        return this.dateOfIncome;
    }

    public void setDate(Date date) {
        this.dateOfIncome = date;
    }

    public short getExpires() {
        return this.expires;
    }

    public void setExpires(short expires) {
        this.expires = expires;
    }

    public FoodItem(String name, float price, FoodItem analog, Date date, short expires){
        this(name, price, expires);
        this.setAnalog(analog);
        this.dateOfIncome = date;
    }

    public FoodItem(String name, float price, short expires){
        this(name);
        this.setPrice(price);
        this.expires = expires;
    }

    public FoodItem(String name){
        super();
        this.setName(name);
    }

    @Override
    void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s , dateOfIncome: %s , expires: %d \n",
                this.getId(), this.getName(), this.getPrice(), this.getCategory(), this.dateOfIncome, this.expires);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        FoodItem item = new FoodItem(this.getName());
        item.setCategory(this.getCategory());
        item.setAnalog(this.getAnalog());
        item.setId(this.getId());
        item.setPrice(this.getPrice());
        item.dateOfIncome = this.dateOfIncome;
        item.expires = this.expires;
        return item;
    }

    public String toString() {
        return this.getId() + " " + this.getName() + " " + this.getPrice() + " " + this.dateOfIncome + " " + this.expires;
    }
}
