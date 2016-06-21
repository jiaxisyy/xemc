package SQL;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import bean.AlarmRecordData;
import bean.HistoryData;
import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/2.
 */
public class SqlManager extends DataBaseHelper {

    private SQLiteDatabase db;
    public SqlManager(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
        db = getWritableDatabase();
    }

    /**
     * 存储历史记录
     */
    public void insertHistory(){
        ContentValues values = new ContentValues();
        int str[]={212,264,228,244};
        String[]num = ReadAndWrite.ReadJni(Constants.Define.OP_REAL_D,str);
        SimpleDateFormat df1 = new SimpleDateFormat("yyyy-MM-dd");
        SimpleDateFormat df2 = new SimpleDateFormat("HH:mm:ss");
        values.put("date", df1.format(new Date()));
        values.put("time", df2.format(new Date()));
        values.put("pressure",num[0]);
        values.put("concentration",num[3]);
        values.put("flow",num[2]);
        values.put("totalflow",num[1]);
        db.insert("history",null,values);
    }
    /**
     * 删除历史记录
     */
    public void deleteHistory(){
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
//        db.execSQL("DELETE FROM history WHERE date<"+df.format(new Date()));
        db.delete("history","date<?",new String[]{"Select CONVERT(varchar(100), dateadd(day,-30,GETDATE()), 24)"});
//        System.out.println("delete");
    }

    /**
     * 查询历史记录
     */
    public List<HistoryData> searchHistory(){
        Cursor cursor =  db.query("history",null,null,null,null,null,"historyID desc");
        List<HistoryData> list = new ArrayList<>();
        if(cursor.moveToFirst()){
            do{
                HistoryData historyData = new HistoryData();
               //ID
                historyData.setKeyId(cursor.getInt(0));
                //日期
                historyData.setDate(cursor.getString(1));
               //时间
                historyData.setTime(cursor.getString(2));
               //压力
                historyData.setPressure(cursor.getString(3));
               //浓度
                historyData.setConcentration(cursor.getString(4));
              //流量
                historyData.setFlow(cursor.getString(5));
              //总流量
                historyData.setTotalflow(cursor.getString(6));
                list.add(historyData);
            }while (cursor.moveToNext());
        }
        return list;
    }
    public List<AlarmRecordData> searchAlarmRecord(){
        Cursor cursor =  db.query("alarm",null,null,null,null,null,"alarmID desc");
        List<AlarmRecordData> list = new ArrayList<>();
        if(cursor.moveToFirst()){
            do{
                AlarmRecordData alarmRecordData = new AlarmRecordData();
                //ID
                alarmRecordData.setKeyId(cursor.getInt(0));
                //日期
                alarmRecordData.setDate(cursor.getString(1));
                //时间
                alarmRecordData.setTime(cursor.getString(2));
                //类型
                alarmRecordData.setType(cursor.getString(3));
                //报警值
                alarmRecordData.setData(cursor.getString(4));
                //报警说明
                alarmRecordData.setExplain(cursor.getString(5));
                //消报时间
                alarmRecordData.setCancel(cursor.getString(6));
                list.add(alarmRecordData);
            }while (cursor.moveToNext());
        }
        return list;
    }
    /**
     * 存储报警记录
     */
    public int insertAlarmRecord(String type,String data,String explain ){
        ContentValues values = new ContentValues();
        String[] datatime =ReadAndWrite.ReadJni(Constants.Define.OP_WORD_D,new int[]{610,611,612,613,614,615});
//        try {
//            Date  dmy = new SimpleDateFormat("yyyy-MM-dd").parse(datatime[0]+"-"+datatime[1]+"-"+datatime[2]);
//            Date  hms = new SimpleDateFormat("hh:mm:ss").parse(datatime[3]+":"+datatime[4]+":"+datatime[5]);
//        } catch (ParseException e) {
//            e.printStackTrace();
//        }
        values.put("date", datatime[0]+"-"+datatime[1]+"-"+datatime[2]);
        values.put("time", datatime[3]+":"+datatime[4]+":"+datatime[5]);
        values.put("type",type);
        values.put("data",data);
        values.put("explain",explain);
        db.insert("alarm",null,values);
        Cursor cursor =  db.query("alarm",new String[]{"alarmID"},null,null,null,null,"alarmID desc","1");
        if (cursor.moveToFirst()){
            return cursor.getInt(0);
        }
        return -1;
    }
    public void upDateAlarmRecord(int ID){
        ContentValues values = new ContentValues();
        String[] datatime =ReadAndWrite.ReadJni(Constants.Define.OP_WORD_D,new int[]{610,611,612,613,614,615});
        values.put("cancel",datatime[0]+"-"+datatime[1]+"-"+datatime[2]+"\n"+datatime[3]+":"+datatime[4]+":"+datatime[5]);
        db.update("alarm",values,"alarmID =?",new String[]{String.valueOf(ID)});
    }
}
