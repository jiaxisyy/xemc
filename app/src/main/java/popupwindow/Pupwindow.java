package popupwindow;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import com.hitek.serial.R;

import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/5/12.
 */
public class Pupwindow extends Activity implements View.OnClickListener {
    private PopupWindow  popupWindow;
    private View contentView;
    private EditText pup_et;
    private int type;
    private int[] address;
    private View view;

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public Pupwindow(Context context){
        contentView =LayoutInflater.from(context).inflate(R.layout.pp_input, null);
        popupWindow = new PopupWindow(contentView, LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT,false);
        if(popupWindow.isShowing()){
            popupWindow.dismiss();
        }
        popupWindow.setFocusable(true);
        popupWindow.setOutsideTouchable(true);
        popupWindow.setBackgroundDrawable(new BitmapDrawable());
        popupWindow.setAnimationStyle(R.style.AnimationPreview);
        pup_et = (EditText) contentView.findViewById(R.id.pup_et);
        Button pup_comfirm = (Button)contentView.findViewById(R.id.pup_comfirm);
        TextView pup_cancel = (TextView)contentView.findViewById(R.id.pup_cancel);
        pup_comfirm.setOnClickListener(this);
        pup_cancel.setOnClickListener(this);
    }
    public void showPopupWindow( View view, int type, int[] address){
        this.view = view;
        this.type = type;
        this.address = address;
        if(!popupWindow.isShowing()){
            pup_et.setText("");
            popupWindow.showAtLocation(contentView,Gravity.FILL,0,0);
        }
    }
    public void stopPopupWindow(){

            if(popupWindow.isShowing()){
                popupWindow.dismiss();
            }

    }
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.pup_comfirm:
                if(pup_et.getText().toString()!=null && !pup_et.getText().toString().equals("")){
                    String[] input ={pup_et.getText().toString()};
                    new ReadAndWrite().WriteJni(type,address,input);
                }
                popupWindow.dismiss();
                break;
            case R.id.pup_cancel:
                popupWindow.dismiss();
                break;
        }
    }
}