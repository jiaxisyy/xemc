package fragment;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.Fragment;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.hitek.serial.R;

import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class MonitoringFragment extends Fragment {


    private View view;
    private TextView mo1;
    private TextView mo2;
    private TextView mo3;
    private TextView mo4;
    private TextView mo5;
    private TextView mo6;
    private TextView mo7;
    private TextView mo8;
    private TextView mo9;
    private TextView mo10;
    private TextView mo11;
    private TextView mo12;
    private TextView mo13;
    private TextView mo14;
    private TextView mo15;
    private TextView mo16;
    private Handler handler = new Handler() {

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            String[] s1 = msg.getData().getStringArray("s1");
            String[] s2 = msg.getData().getStringArray("s2");
            String[] s3 = msg.getData().getStringArray("s3");

            if (!TextUtils.isEmpty(s1[0])) {
                mo1.setText(s1[0]);
            }
            if (!TextUtils.isEmpty(s1[1])) {
                mo2.setText(s1[1]);
            }
            if (!TextUtils.isEmpty(s1[2])) {
                mo3.setText(s1[2]);
            }
            if (!TextUtils.isEmpty(s1[3])) {
                mo4.setText(s1[3]);
            }
            if (!TextUtils.isEmpty(s1[4])) {
                mo5.setText(s1[4]);
            }
            if (!TextUtils.isEmpty(s1[5])) {
                mo6.setText(s1[5]);
            }
            if (!TextUtils.isEmpty(s1[6])) {
                mo7.setText(s1[6]);
            }
            if (!TextUtils.isEmpty(s1[7])) {
                mo8.setText(s1[7]);
            }
            if (!TextUtils.isEmpty(s1[8])) {
                mo9.setText(s1[8]);
            }
            if (!TextUtils.isEmpty(s1[9])) {
                mo10.setText(s1[9]);
            }
            if (!TextUtils.isEmpty(s1[10])) {
                mo11.setText(s1[10]);
            }
            if (!TextUtils.isEmpty(s1[11])) {
                mo12.setText(s1[11]);
            }
            if (!TextUtils.isEmpty(s1[12])) {
                mo16.setText(s1[12]);
            }
            /***********************************************/
            String[] ms = {"空档", "1档", "2档", "3档"};
            int length = ms.length;
            for (int i = 0; i < length; i++) {
                int j = Integer.parseInt(s2[i]);
                if (j == 1) {
                    mo13.setText(ms[i]);
                }
            }
            /***********************************************/
            String s620 = s3[0];
            if (!TextUtils.isEmpty(s620)) {
                if (Integer.parseInt(s620) == 1) {
                    //前牵
                    mo14.setText("前牵");

                }else if(Integer.parseInt(s620)==2){

                    mo14.setText("后牵");
                }

            }

            String s622 = s3[1];
            if (!TextUtils.isEmpty(s622)) {
                if (Integer.parseInt(s622) == 1) {
                    //前牵
                    mo15.setText("前机");

                }else if(Integer.parseInt(s622)==2){

                    mo15.setText("后机");
                }else if(Integer.parseInt(s622)==3){

                    mo15.setText("双机");
                }

            }


        }
    };


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_monitoring, container, false);
        initialize();
        getData();

        return view;
    }

    private void getData() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int[] ints = new int[]{700, 400, 402, 404, 406, 212, 408, 410, 412, 414, 416, 418, 624};
                int[] ints2 = new int[]{50, 51, 52, 53};
                int[] ints3 = new int[]{620, 622};

                while (true) {
                    try {
                        String[] strings1 = ReadAndWrite.ReadJni(Constants.Define.OP_REAL_D, ints);
                        String[] strings2 = ReadAndWrite.ReadJni(Constants.Define.OP_BIT_M, ints2);
                        String[] strings3 = ReadAndWrite.ReadJni(Constants.Define.OP_WORD_D, ints3);
                        Message obtain = Message.obtain();
                        Bundle bundle = new Bundle();
                        bundle.putStringArray("s1", strings1);
                        bundle.putStringArray("s2", strings2);
                        bundle.putStringArray("s3", strings3);
                        obtain.setData(bundle);
                        handler.sendMessage(obtain);
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                }


            }
        }).start();


    }


    private void initialize() {

        mo1 = (TextView) view.findViewById(R.id.mo_1);
        mo2 = (TextView) view.findViewById(R.id.mo_2);
        mo3 = (TextView) view.findViewById(R.id.mo_3);
        mo4 = (TextView) view.findViewById(R.id.mo_4);
        mo5 = (TextView) view.findViewById(R.id.mo_5);
        mo6 = (TextView) view.findViewById(R.id.mo_6);
        mo7 = (TextView) view.findViewById(R.id.mo_7);
        mo8 = (TextView) view.findViewById(R.id.mo_8);
        mo9 = (TextView) view.findViewById(R.id.mo_9);
        mo10 = (TextView) view.findViewById(R.id.mo_10);
        mo11 = (TextView) view.findViewById(R.id.mo_11);
        mo12 = (TextView) view.findViewById(R.id.mo_12);
        mo13 = (TextView) view.findViewById(R.id.mo_13);
        mo14 = (TextView) view.findViewById(R.id.mo_14);
        mo15 = (TextView) view.findViewById(R.id.mo_15);
        mo16 = (TextView) view.findViewById(R.id.mo_16);
    }
}
