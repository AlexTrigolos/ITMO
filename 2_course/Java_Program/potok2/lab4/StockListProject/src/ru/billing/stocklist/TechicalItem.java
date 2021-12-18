package ru.billing.stocklist;

public class TechicalItem extends GenericItem {
    private short warrantyTime;

    public short getTime() {
        return this.warrantyTime;
    }

    public void setTime(short time) {
        this.warrantyTime = time;
    }

    @Override
    void printAll() {
        System.out.printf("ID: %d , Name: %-20s , price:%5.2f , category: %s , warrantyTime: %d \n",
                this.getId(), this.getName(), this.getPrice(), this.getCategory(), this.warrantyTime);
    }

    public boolean equals(Object o) {
        return this == o;
    }

    public Object clone() {
        TechicalItem item = new TechicalItem();
        item.setCategory(this.getCategory());
        item.setAnalog(this.getAnalog());
        item.setId(this.getId());
        item.setName(this.getName());
        item.setPrice(this.getPrice());
        item.warrantyTime = this.warrantyTime;
        return item;
    }

    public String toString() {
        return this.getId() + " " + this.getName() + " " + this.getPrice() + " " + this.warrantyTime;
    }
}
