package sync;

public class U1901Thread extends Thread {
    U1901Bank bankWork;
    int intTrans;
    long lngSleep;
    U1901Thread(U1901Bank uBank, int trans, long sleep){
        this.bankWork = uBank;
        this.lngSleep = sleep;
        this.intTrans = trans;
    }

    @Override
    public void run() {
        this.bankWork.calc(this.intTrans, this.lngSleep);
    }
}
