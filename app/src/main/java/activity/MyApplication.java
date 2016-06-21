package activity;

import com.hitek.serialJNI.serialJNI;

/**
 * Created by shuang.xiang on 2016/4/27.
 */
public class MyApplication extends android.app.Application {
    private static serialJNI serial = null;

    public static serialJNI getInstance() {
        if (serial == null) {
            synchronized (MyApplication.class) {
                if (serial == null) {
                    serial = new serialJNI();
                }
            }
        }
        return serial;
    }

    public MyApplication() {
    }



    @Override
    public void onCreate() {
        super.onCreate();
        getInstance().init();
        new Thread(new Runnable() {

            @Override
            public void run() {
               getInstance().mainloop();

            }
        }).start();

    }
}
