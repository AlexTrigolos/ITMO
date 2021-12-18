package com.company;

public class Main {

    public static void main(String[] args) {
        String line = "Конфеты ’Маска’;45;120";
        String[] item_fld = line.split(";");
        FoodItem new_food = new FoodItem(item_fld[0], Float.parseFloat(item_fld[1]), Short.parseShort(item_fld[2]));
    }
}
