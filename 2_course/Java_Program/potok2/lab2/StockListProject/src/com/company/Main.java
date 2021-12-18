package com.company;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        var first = new GenericItem();
        first.ID = 0;
        first.name = "first";
        first.price = 12.3f;
        var second = new GenericItem();
        second.ID = 1;
        second.name = "second";
        second.price = 45.6f;
        var third = new GenericItem();
        third.ID = 2;
        third.name = "third";
        third.price = 78.9f;
        ArrayList<GenericItem> list = new ArrayList<>();
        list.add(new FoodItem());
        list.add(new TechicalItem());
        list.add(new FoodItem());
        list.add(new TechicalItem());
        for(var item: list){
            item.printAll();
        }
        System.out.println((new FoodItem()).equals(new FoodItem()));
        FoodItem origin = new FoodItem();
        FoodItem fake = (FoodItem) origin.clone();
        System.out.println(origin.equals(fake));
    }
}
