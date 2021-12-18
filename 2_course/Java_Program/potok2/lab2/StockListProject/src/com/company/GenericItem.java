package com.company;

import javax.print.attribute.standard.MediaSize;

public class GenericItem {
    public int ID;
    public String name;
    public float price;
    public GenericItem analog;
    Category category = Category.GENERAL;

    void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s \n", ID, name, price, category);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        GenericItem item = new GenericItem();
        GenericItem other = this;
        if(this.analog != null){
            other = this.analog;
        }
        item.category = other.category;
        item.analog = other.analog;
        item.ID = other.ID;
        item.name = other.name;
        item.price = other.price;
        return item;
    }

    public String toString() {
        return this.ID + " " + this.name + " " + this.price;
    }
}