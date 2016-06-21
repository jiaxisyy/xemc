package popupwindow;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.text.InputType;
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

import activity.MyApplication;
import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/11.
 * //
 */
public class PopupForTimeSetting implements View.OnClickListener{
    private PopupWindow  popupWindow;
    private View contentView;
    private EditText pup_et;
    private int type;
    private int[] address;
    private View view;

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public PopupForTimeSetting(Context context){
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
            pup_et.setInputType(InputType.TYPE_CLASS_NUMBER);
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
