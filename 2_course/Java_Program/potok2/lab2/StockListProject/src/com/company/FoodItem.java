package com.company;

import java.util.Date;

public class FoodItem extends GenericItem {
    Date dateOfIncome;
    short expires;

    @Override
    void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s , dateOfIncome: %s , expires: %d \n", ID, name, price, category, dateOfIncome, expires);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        FoodItem item = new FoodItem();
        item.category = this.category;
        item.analog = this.analog;
        item.ID = this.ID;
        item.name = this.name;
        item.price = this.price;
        item.dateOfIncome = this.dateOfIncome;
        item.expires = this.expires;
        return item;
    }

    public String toString() {
        return this.ID + " " + this.name + " " + this.price + " " + this.dateOfIncome + " " + this.expires;
    }
}
