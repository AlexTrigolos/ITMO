package ru.billing.stocklist;

public class GenericItem {
    private int ID;
    private String name;
    private float price;
    private GenericItem analog;
    private Category category = Category.GENERAL;
    private static int currentID = 0;

    public int getId() {
        return this.ID;
    }

    public void setId(int id) {
        this.ID = id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getPrice() {
        return this.price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public GenericItem getAnalog() {
        return this.analog;
    }

    public void setAnalog(GenericItem analog) {
        this.analog = analog;
    }

    public Category getCategory() {
        return this.category;
    }

    public void setCategory(Category category) {
        this.category = category;
    }

    public int getCurrentID() {
        return currentID;
    }

    public void setCurrentID(int currentId) {
        currentID = currentId;
    }

    public GenericItem(String name, float price, Category category) {
        this();
        this.name = name;
        this.price = price;
        this.category = category;
    }

    public GenericItem(String name, float price, GenericItem analog) {
        this();
        this.name = name;
        this.price = price;
        this.analog = analog;
    }

    public GenericItem() {
        this.ID = GenericItem.currentID++;
    }

    public void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s \n", ID, name, price, category);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        GenericItem item = new GenericItem();
        GenericItem other = this;
        if (this.analog != null) {
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