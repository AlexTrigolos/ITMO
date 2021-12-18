package ru.billing.client;

import ru.billing.stocklist.FoodItem;
import ru.billing.stocklist.GenericItem;
import ru.billing.stocklist.ItemCatalog;
import ru.itmo.client.CatalogFileLoader;
import ru.itmo.exceptions.CatalogLoadException;
import ru.itmo.exceptions.ItemAlreadyExistsException;

import java.util.Date;


public class Main {

    public static void main(String[] args) throws CatalogLoadException, ItemAlreadyExistsException {
        ItemCatalog cat = new ItemCatalog();
        for (int i = 0; i < 20; i++) cat.addItem(new GenericItem());
        long begin = new Date().getTime();
        for (int i = 0; i < 10000000; i++)
            cat.findItemByID(15);
        long end = new Date().getTime();
        System.out.println("In HashMap: " + (end - begin));
        begin = new Date().getTime();
        for (int i = 0; i < 10000000; i++)
            cat.findItemByIDAL(15);
        end = new Date().getTime();
        System.out.println("In ArrayList: " + (end - begin));
        CatalogLoader loader = new CatalogStubLoader();
        loader.load(cat);
        FoodItem food = new FoodItem("abc");
        cat.addItem(food);
        try {
            cat.addItem(food);
        } catch (ItemAlreadyExistsException e) {
            System.out.println(e.getMessage());
        }
        try {
            loader.load(cat);
        } catch (CatalogLoadException e) {
            System.out.println(e.getMessage());
        }
        CatalogFileLoader catalogFileLoader = new CatalogFileLoader("items.lst");
        ItemCatalog catalog = new ItemCatalog();
        catalogFileLoader.load(catalog);
        catalog.printItems();
    }
}