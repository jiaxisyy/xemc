package SQL;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by zuheng.lv on 2016/6/1.
 */
public class DataBaseHelper extends SQLiteOpenHelper{


    public DataBaseHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        //历史记录的数据库
        db.execSQL("Create TABLE history (historyID integer primary key autoincrement ," +
                "date DATETIME,"+
                "time DATETIME,"+
                "pressure number(10) default null,"+
                "concentration number(10) default null,"+
                "flow number(10) default null,"+
                "totalflow number(10) default null"+
                ")");
        //报警记录的数据库
        db.execSQL("Create TABLE alarm (alarmID integer primary key autoincrement ," +
                "date  varchar(20) default null,"+
                "time  varchar(20) default null,"+
                "type varchar(20),"+
                "data varchar(20),"+
                "explain varchar(20),"+
                "cancel varchar(20)"+
                ")");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
