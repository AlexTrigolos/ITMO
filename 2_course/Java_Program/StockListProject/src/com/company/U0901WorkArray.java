package com.company;

public class U0901WorkArray<T extends Number> {
    T[] arrNums;

    U0901WorkArray(T[] numP) {
        this.arrNums = numP;
    }

    double sum() {
        double doubleWork = 0.0;
        for (T item : arrNums) doubleWork += item.doubleValue();
        return doubleWork;
    }
}
