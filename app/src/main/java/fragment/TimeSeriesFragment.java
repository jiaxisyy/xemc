package fragment;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import android.support.v4.app.Fragment;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AnticipateOvershootInterpolator;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

import activity.MyApplication;
import popupwindow.PopupForTime;
import popupwindow.PopupForWeek;
import popupwindow.Pupwindow;
import utils.CacheUtils;
import utils.Constants;
import utils.ReadAndWrite;
import wheel.StrericWheelAdapter;
import wheel.WheelView;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class TimeSeriesFragment extends Fragment implements  View.OnTouchListener, View.OnClickListener {

    private Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what){
                case 1:
                    /**����дUI���º���*/

                    if(String.valueOf(msg.getData().getStringArray("data")[0]) !=null &&!String.valueOf(msg.getData().getStringArray("data")[0] ).equals("")){
                        setting1.setText(String.valueOf(msg.getData().getStringArray("data")[0]));
                    }
                    if(String.valueOf(msg.getData().getStringArray("data")[1]) !=null &&!String.valueOf(msg.getData().getStringArray("data")[1] ).equals("")){
                        setting2.setText(String.valueOf(msg.getData().getStringArray("data")[1]));
                    }
                    if(String.valueOf(msg.getData().getStringArray("data")[2]) !=null &&!String.valueOf(msg.getData().getStringArray("data")[2] ).equals("")){
                        setting3.setText(String.valueOf(msg.getData().getStringArray("data")[2]));
                    }

                    break;
                case 2:

                    break;

            }
        }
    };

    private Button setting_btn1,setting_btn2,setting_btn3,setting_btn4;
    private TextView setting1,setting2,setting3;
    private boolean flag = true;
    private View view;
    private Pupwindow pupwindow;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_special_controls,container,false);
        initView();
        initData();
        setData();
        getData();
        pupwindow = new Pupwindow(getContext());
        return view;
    }

    /**�ؼ���ʼ��*/
    public void initView(){
        setting_btn1 = (Button) view.findViewById(R.id.setting_btn1);
        setting_btn2 = (Button) view.findViewById(R.id.setting_btn2);
        setting_btn3 = (Button) view.findViewById(R.id.setting_btn3);
        setting_btn4 = (Button) view.findViewById(R.id.setting_btn4);
        setting1 = (TextView) view.findViewById(R.id.setting1);
        setting2 = (TextView) view.findViewById(R.id.setting2);
        setting3 = (TextView) view.findViewById(R.id.setting3);
        setting1.setOnClickListener(this);
        setting2.setOnClickListener(this);
        setting3.setOnClickListener(this);
        setting_btn1.setOnTouchListener(this);
        setting_btn2.setOnTouchListener(this);
        setting_btn3.setOnTouchListener(this);
        setting_btn4.setOnTouchListener(this);
    }
    /**���ݳ�ʼ��*/
    public void initData(){


    }

    /**���ݻ�ȡ*/
    public void getData(){


    }
    /**���ݴ洢*/
    public void saveData(){

    }
    /**���ݸ���*/
    public void setData(){
        new Thread(new Runnable() {
            @Override
            public void run() {

                /**����д���ݻ�ȡ�����ݴ�����*/
                while (flag) {
                    try {
                        String[] data = ReadAndWrite.ReadJni(Constants.Define.OP_WORD_D,new int[]{610,612,614});

                        Bundle bundle = new Bundle();
                        Message msg = new Message();
                        bundle.putStringArray("data",data);
                        msg.setData(bundle);
                        msg.what = 1;
                        handler.sendMessage(msg);
                        Thread.sleep(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }


    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch (v.getId()){
            case R.id.setting_btn1:
                if(event.getAction()== MotionEvent.ACTION_DOWN){
                    byte[] m190 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m190,190,1);
                }else if(event.getAction()== MotionEvent.ACTION_UP){
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m190 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m190,190,1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
            case R.id.setting_btn2:
                if(event.getAction()== MotionEvent.ACTION_DOWN){
                    byte[] m56 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m56,56,1);
                }else if(event.getAction()== MotionEvent.ACTION_UP){
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m56 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m56,56,1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
            case R.id.setting_btn3:
                if(event.getAction()== MotionEvent.ACTION_DOWN){
                    byte[] m58 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m58,58,1);
                }else if(event.getAction()== MotionEvent.ACTION_UP){
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m58 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m58,58,1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
            case R.id.setting_btn4:
                if(event.getAction()== MotionEvent.ACTION_DOWN){
                    byte[] m54 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m54,54,1);
                }else if(event.getAction()== MotionEvent.ACTION_UP){
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m54 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,m54,54,1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
        }
        return false;
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
        flag=false;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.setting1:
                pupwindow.showPopupWindow(v,Constants.Define.OP_REAL_D,new int[]{610});
                break;
            case R.id.setting2:
                pupwindow.showPopupWindow(v,Constants.Define.OP_REAL_D,new int[]{612});
                break;
            case R.id.setting3:
                pupwindow.showPopupWindow(v,Constants.Define.OP_REAL_D,new int[]{614});
                break;
        }
    }
}
