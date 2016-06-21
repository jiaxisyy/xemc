package popupwindow;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.Timer;
import java.util.TimerTask;

import activity.MyApplication;
import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by shuang.xiang on 2016/6/15.
 */
public class PopupForTime implements View.OnClickListener, View.OnTouchListener {
    private PopupWindow popupWindow;
    private View contentView;
    private int type;
    private int[] address;
    private View view;
    private EditText popupfortime_year, popupfortime_month, popupfortime_day, popupfortime_hour, popupfortime_minute, popupfortime_second;

    public PopupForTime(Context context) {
        contentView = LayoutInflater.from(context).inflate(R.layout.popupfortime_layout, null);
        popupWindow = new PopupWindow(contentView, LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, false);
        if (popupWindow.isShowing()) {
            popupWindow.dismiss();
        }
        popupWindow.setFocusable(true);
        popupWindow.setOutsideTouchable(true);
        popupWindow.setBackgroundDrawable(new BitmapDrawable());
        popupWindow.setAnimationStyle(R.style.AnimationPreview);
    }

    private void initView() {
        popupfortime_year = (EditText) contentView.findViewById(R.id.popupfortime_year);
        popupfortime_month = (EditText) contentView.findViewById(R.id.popupfortime_month);
        popupfortime_day = (EditText) contentView.findViewById(R.id.popupfortime_day);
        popupfortime_hour = (EditText) contentView.findViewById(R.id.popupfortime_hour);
        popupfortime_minute = (EditText) contentView.findViewById(R.id.popupfortime_minute);
        popupfortime_second = (EditText) contentView.findViewById(R.id.popupfortime_second);
        Button pupfortime_comfirm = (Button) contentView.findViewById(R.id.pupfortime_comfirm);
        TextView pupforcancel_cancel = (TextView) contentView.findViewById(R.id.pupforcancel_cancel);
        pupfortime_comfirm.setOnTouchListener(this);
        pupforcancel_cancel.setOnClickListener(this);
    }

    public void showPopupWindow(View view, int type, int[] address) {
        this.view = view;
        this.type = type;
        this.address = address;
        initView();
        int[] adddd = {610, 611, 612, 613, 614, 615};
        String[] ssss = ReadAndWrite.ReadJni(type, adddd);
        popupfortime_year.setHint(ssss[0]);
        popupfortime_month.setHint(ssss[1]);
        popupfortime_day.setHint(ssss[2]);
        popupfortime_hour.setHint(ssss[3]);
        popupfortime_minute.setHint(ssss[4]);
        popupfortime_second.setHint(ssss[5]);
        if (!popupWindow.isShowing()) {
            popupWindow.showAtLocation(contentView, Gravity.FILL, 0, 0);
        }
    }

    public void stopPopupWindow() {
        if (popupWindow.isShowing()) {
            popupWindow.dismiss();
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.pupforcancel_cancel:
                popupWindow.dismiss();
                break;
        }
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch (v.getId()) {
            case R.id.pupfortime_comfirm:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    if ((popupfortime_year.getText().toString() != null && !popupfortime_year.getText().toString().equals("")
                            && (popupfortime_month.getText().toString() != null && !popupfortime_month.getText().toString().equals(""))
                            && (popupfortime_day.getText().toString() != null && !popupfortime_day.getText().toString().equals(""))
                            && (popupfortime_hour.getText().toString() != null && !popupfortime_hour.getText().toString().equals(""))
                            && (popupfortime_minute.getText().toString() != null && !popupfortime_minute.getText().toString().equals(""))
                            && (popupfortime_second.getText().toString() != null && !popupfortime_second.getText().toString().equals("")))) {
                        String year = popupfortime_year.getText().toString();
                        String month = popupfortime_month.getText().toString();
                        String day = popupfortime_day.getText().toString();
                        String hour = popupfortime_hour.getText().toString();
                        String minute = popupfortime_minute.getText().toString();
                        String second = popupfortime_second.getText().toString();
                        String[] strs = {year, month, day, hour, minute, second};
                        new ReadAndWrite().WriteJni(type, address, strs);

                        TimerTask timerTask = new TimerTask() {
                            @Override
                            public void run() {
                                MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, new byte[]{1}, 56, 1);
                                Log.d("TAG","down");
                            }
                        };
                        Timer timer = new Timer();
                        timer.schedule(timerTask, 2000);

                    }
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    TimerTask timerTask = new TimerTask() {
                        @Override
                        public void run() {
                            MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M, new byte[]{0}, 56, 1);
                            Log.d("TAG","up");
                        }
                    };
                    Timer timer = new Timer();
                    timer.schedule(timerTask, 2000);
                    popupWindow.dismiss();
                }
                break;
        }
        return false;
    }
}
