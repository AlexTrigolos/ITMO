package com.company;

public class TechicalItem extends GenericItem {
    short warrantyTime;

    @Override
    void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s , warrantyTime: %d \n", ID, name, price, category, warrantyTime);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        TechicalItem item = new TechicalItem();
        item.category = this.category;
        item.analog = this.analog;
        item.ID = this.ID;
        item.name = this.name;
        item.price = this.price;
        item.warrantyTime = this.warrantyTime;
        return item;
    }

    public String toString() {
        return this.ID + " " + this.name + " " + this.price + " " + this.warrantyTime;
    }
}
