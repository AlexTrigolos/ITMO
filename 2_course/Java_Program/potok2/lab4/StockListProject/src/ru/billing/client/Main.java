package ru.billing.client;

import ru.billing.stocklist.GenericItem;
import ru.billing.stocklist.ItemCatalog;

import java.util.Date;

public class Main {

    public static void main(String[] args) {
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
//        cat.printItems();

    }
}
