package popupwindow;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import com.hitek.serial.R;

import java.util.List;

import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/11.
 */
public class PopupForSimulaion implements View.OnClickListener {
    private PopupWindow  popupWindow;
    private View contentView;
    private EditText popupforsimulaion_et;
    private int type;
    private int[] address;
    private View view;
    private float x;
    private float y;

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public PopupForSimulaion(Context context){
        contentView =LayoutInflater.from(context).inflate(R.layout.popupforsimulaion_layout, null);
        popupWindow = new PopupWindow(contentView, LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT,false);
        if(popupWindow.isShowing()){
            popupWindow.dismiss();
        }
        popupWindow.setFocusable(true);
        popupWindow.setOutsideTouchable(true);
        popupWindow.setBackgroundDrawable(new BitmapDrawable());
        popupforsimulaion_et = (EditText) contentView.findViewById(R.id.popupforsimulaion_et);

    }
    public void showPopupWindow( View view, float x, float y, int type, int[] address){
        this.x=x;
        this.y=y;
        this.view = view;
        this.type = type;
        this.address = address;
        if(!popupWindow.isShowing()){
            popupforsimulaion_et.setWidth(view.getWidth());
            popupforsimulaion_et.setHeight(view.getHeight());
            Button popupforsimulaion_btn = (Button)contentView.findViewById(R.id.popupforsimulaion_btn);
            popupforsimulaion_btn.setOnClickListener(this);
            popupforsimulaion_et.setText("");
            popupWindow.showAtLocation(view, Gravity.NO_GRAVITY, (int) x, (int) y);
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
            case R.id.popupforsimulaion_btn:
                if(popupforsimulaion_et.getText().toString()!=null && !popupforsimulaion_et.getText().toString().equals("")){
                    String[] input ={popupforsimulaion_et.getText().toString()};
                    new ReadAndWrite().WriteJni(type,address,input);
                }
                popupWindow.dismiss();
                break;
        }
    }
}
