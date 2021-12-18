package ru.billing.client;

import ru.billing.stocklist.ItemCatalog;
import ru.itmo.exceptions.CatalogLoadException;
import ru.itmo.exceptions.ItemAlreadyExistsException;

public interface CatalogLoader {
    public void load(ItemCatalog cat) throws CatalogLoadException;
}
