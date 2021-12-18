package com.company;

public class U0901Main {
    public static void main(String[] args) {
        Integer intArr[]={10,20,15};
        Float floatArr[] = new Float[5];
        for (int i = 0; i < 5; i++){
            floatArr[i] = i * 1.235f;
        }
        U0901WorkArray<Integer> insWorkArrayInt = new U0901WorkArray<>(intArr);
        U0901WorkArray<Float> insWorkArrayFloat = new U0901WorkArray<>(floatArr);
        System.out.println(insWorkArrayInt.sum());
        System.out.println(insWorkArrayFloat.sum());
//        String strArr[]={"abc", "verandas", "d"};
//        U0901WorkArray<String> insWorkArrayString = new U0901WorkArray<>(strArr); // mistake in <String> not extends Number //
    }
}
