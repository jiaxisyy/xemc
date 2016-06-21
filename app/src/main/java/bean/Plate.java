package bean;

import android.annotation.TargetApi;
import android.app.Fragment;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;

import com.hitek.serial.R;

import activity.MyApplication;
import utils.Constants;

/**
 * Created by zuheng.lv on 2016/5/28.
 */
@TargetApi(Build.VERSION_CODES.HONEYCOMB)
public class Plate extends android.support.v4.app.Fragment {
    private ImageView imageView;
    private long begin = 0;
    Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);


                startAnimation(Double.parseDouble(String.valueOf(msg.getData().getFloat("s")/750*180)));
        }
    };
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.equipment,container,false);
        imageView = (ImageView) view.findViewById(R.id.iv_needle);
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                   float[]f =  MyApplication.getInstance().mdbusreadreal(Constants.Define.OP_REAL_D,700,1);
                    Message message = new Message();
                    Bundle bundle = new Bundle();
                    bundle.putFloat("s",f[0]);

                    message.setData(bundle);
                    handler.sendMessage(message);
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

            }
        }).start();
        return view;
    }
    public void startAnimation(double d) {
        AnimationSet animationSet = new AnimationSet(true);
        /**
         * 前两个参数定义旋转的起始和结束的度数，后两个参数定义圆心的位置
         */
        RotateAnimation rotateAnimation = new RotateAnimation(begin, (float)d, Animation.RELATIVE_TO_SELF, 0.9f, Animation.RELATIVE_TO_SELF, 0.5f);
        rotateAnimation.setDuration(1000);
        animationSet.addAnimation(rotateAnimation);
        imageView.startAnimation(animationSet);
        begin =(long)d;
    }
}
