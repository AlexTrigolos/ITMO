import java.math.BigDecimal;

public class MainClass2 {
    public static void main(String[] args) {
//        String string = "string";
//        System.out.println(string instanceof Integer); //Error
        BigDecimal BigD1 = new BigDecimal(15);
        BigDecimal BigD2 = new BigDecimal(15);
        System.out.println(BigD1.equals(BigD2));
        System.out.println(BigD1 == BigD2);
        BigD1 = BigD1.add(BigD2);
        System.out.println(BigD1);
        BigD1 = BigD1.divide(BigD2);
        System.out.println(BigD1);
        BigD1 = BigD1.multiply(BigD2);
        System.out.println(BigD1);
        /*
        // Error
        BigD1 = BigD1 + BigD2;
        System.out.println(BigD1);
        BigD1 = BigD1 / BigD2;
        System.out.println(BigD1);
        BigD1 = BigD1 * BigD2;
        System.out.println(BigD1);
        */
    }
}
