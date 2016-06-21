package service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.support.annotation.Nullable;

import SQL.SqlManager;

/**
 * Created by zuheng.lv on 2016/6/2.
 */
public class Services extends Service{

    private SqlManager sqlManager;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        sqlManager = new SqlManager(getApplicationContext(),"history.db",null,1);
        ClassThread thread = new ClassThread(sqlManager);
        thread.historySave();
        thread.saveAlarmRecord();

//        thread.historyDelete();
//        UpDateCloud upDateCloud = new UpDateCloud("");
//        upDateCloud.upDateData();
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                while (true){
//                    List<HistoryData> list = sqlManager.searchHistory();
//                    for(int i =0;i<list.size();i++){
//                        System.out.println("kkkkkbbbbb"+","+list.get(i).getTime());
//                    }
//                    try {
//                        Thread.sleep(1000);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }
//        }).start();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return super.onStartCommand(intent, flags, startId);
    }
}
