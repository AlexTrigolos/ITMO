package ru.itmo.exceptions;

import java.io.FileNotFoundException;
import java.nio.file.FileAlreadyExistsException;

public class CatalogLoadException extends Exception {
    public CatalogLoadException(ItemAlreadyExistsException e) {
        super(e);
    }
    public CatalogLoadException(FileNotFoundException e) {
        super(e);
    }
}
