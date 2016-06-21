package fragment;

import android.annotation.TargetApi;

import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import android.support.v4.app.Fragment;

import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.content.PermissionChecker;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Logger;

import activity.MyApplication;
import adapter.MainRecycleViewAdapter;
import bean.GLayoutManager;
import bean.MainRecycleViewItem;
import bean.Plate;
import utils.Constants;
import utils.ReadAndWrite;
import utils.Utils;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class MonitorFragment extends Fragment implements View.OnTouchListener {
    private Handler handler = new Handler() {
        @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case 1:
                    /**����дUI���º���*/
                    fengya_tv.setText(msg.getData().getString("i1"));
                    fenggang_tv.setText(msg.getData().getString("j1"));
                    if (msg.getData().getBoolean("m50")) {
                        jiche_layout.setBackground(getResources().getDrawable(R.drawable.jiche1));
                    } else if (msg.getData().getBoolean("m51")) {
                        jiche_layout.setBackground(getResources().getDrawable(R.drawable.jice2));
                    } else if (msg.getData().getBoolean("m52")) {
                        jiche_layout.setBackground(getResources().getDrawable(R.drawable.jiche3));
                    } else if (msg.getData().getBoolean("m53")) {
                        jiche_layout.setBackground(getResources().getDrawable(R.drawable.jiche4));
                    }
                    break;
            }
        }
    };

    //ѭ����־
    private boolean flag = true;
    private LinearLayout jiche_layout;
    private TextView fengya_tv, fenggang_tv;
    private View view;
    private Plate plate;
    private Button btn_open, btn_stop;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.monitor_layout, container, false);
        initData();
        initView();
        setData();
        return view;
    }


    /**
     * �ؼ���ʼ��
     */
    public void initView() {
        jiche_layout = (LinearLayout) view.findViewById(R.id.jiche_layout);
        fengya_tv = (TextView) view.findViewById(R.id.fengya_tv);
        fenggang_tv = (TextView) view.findViewById(R.id.fenggang_tv);
        btn_open = (Button) view.findViewById(R.id.btn_open);
        btn_stop = (Button) view.findViewById(R.id.btn_stop);
        btn_open.setOnTouchListener(this);
        btn_stop.setOnTouchListener(this);
        plate = new Plate();
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.replace(R.id.biaopan, plate);
        fragmentTransaction.commit();

    }

    @Override
    public void onStart() {
        super.onStart();
        Utils.replace(getFragmentManager(), R.id.biaopan, Plate.class);
    }

    /**
     * ���ݳ�ʼ��
     */

    public void initData() {

    }

    /**
     * ���ݻ�ȡ
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public void getData() {

    }

    /**
     * ���ݸ���
     */
    public void setData() {

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (flag) {
                    try {

                        float[] i = MyApplication.getInstance().mdbusreadreal(Constants.Define.OP_REAL_D, 212, 1);
                        float i1 = (float) (Math.round(i[0] * 10)) / 10;

                        float[] j = MyApplication.getInstance().mdbusreadreal(Constants.Define.OP_REAL_D, 264, 1);
                        float j1 = (float) (Math.round(j[0] * 100)) / 100;
                        byte[] m50 = MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_M, 50, 1);
                        byte[] m51 = MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_M, 51, 1);
                        byte[] m52 = MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_M, 52, 1);
                        byte[] m53 = MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_M, 53, 1);
                        Bundle bundle = new Bundle();

                        bundle.putString("i1", String.valueOf(i1));
                        bundle.putString("j1", String.valueOf(j1));
                        if (m50[0] == 1) {
                            bundle.putBoolean("m50", true);
                        } else {
                            bundle.putBoolean("m50", false);
                        }
                        if (m51[0] == 1) {
                            bundle.putBoolean("m51", true);
                        } else {
                            bundle.putBoolean("m51", false);
                        }
                        if (m52[0] == 1) {
                            bundle.putBoolean("m52", true);
                        } else {
                            bundle.putBoolean("m52", false);
                        }
                        if (m53[0] == 1) {
                            bundle.putBoolean("m53", true);
                        } else {
                            bundle.putBoolean("m53", false);
                        }
                        Message msg = new Message();
                        msg.what = 1;
                        msg.setData(bundle);
                        handler.sendMessage(msg);
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch (v.getId()) {
            case R.id.btn_open:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    byte[] m11 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, m11, 11, 1);
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m11 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, m11, 11, 1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
            case R.id.btn_stop:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    byte[] m101 = {1};
                    MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, m101, 101, 1);
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    TimerTask timerTask = new TimerTask() {

                        @Override
                        public void run() {
                            // TODO Auto-generated method stub
                            byte[] m101 = {0};
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, m101, 101, 1);
                        }
                    };
                    Timer time = new Timer();
                    time.schedule(timerTask, 500);
                }
                break;
        }
        return false;
    }
}
