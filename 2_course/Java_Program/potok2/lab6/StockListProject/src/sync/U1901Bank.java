package sync;

public class U1901Bank {
    int intTo;
    int intFrom = 220;

    synchronized void calc(int intTransaction, long lngTimeout) {
        System.out.println("Before::: To: " + intTo + ", From: " + intFrom + ", ThreadName: " + Thread.currentThread().getName());
        intFrom -= intTransaction;
        try {
            Thread.sleep(lngTimeout);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        intTo += intTransaction;
        System.out.println("After ::: To: " + intTo + ", From: " + intFrom + ", ThreadName: " + Thread.currentThread().getName());
    }
}
