package popupwindow;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import com.hitek.serial.R;

import utils.ReadAndWrite;

/**
 * Created by shuang.xiang on 2016/6/13.
 */
public class PopupForWeek implements View.OnClickListener {
    private PopupWindow popupWindow;
    private View contentView;
    private Button monday,tuesday,wednesday,thursday,friday,saturday,sunday;
    private int type;
    private int[] address;
    private View view;

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public PopupForWeek(Context context){
        contentView = LayoutInflater.from(context).inflate(R.layout.week_layout, null);
        popupWindow = new PopupWindow(contentView, LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT,false);
        if(popupWindow.isShowing()){
            popupWindow.dismiss();
        }
        popupWindow.setFocusable(true);
        popupWindow.setOutsideTouchable(true);
        popupWindow.setBackgroundDrawable(new BitmapDrawable());
        popupWindow.setAnimationStyle(R.style.AnimationPreview);
        initView();
    }
    private void initView(){
        monday = (Button)  contentView.findViewById(R.id.monday);
        tuesday = (Button)  contentView.findViewById(R.id.tuesday);
        wednesday = (Button)  contentView.findViewById(R.id.wednesday);
        thursday = (Button)  contentView.findViewById(R.id.thursday);
        friday = (Button)  contentView.findViewById(R.id.friday);
        saturday = (Button)  contentView.findViewById(R.id.saturday);
        sunday = (Button)  contentView.findViewById(R.id.sunday);
        TextView pup_cancel = (TextView)contentView.findViewById(R.id.pup_cancel);
        monday.setOnClickListener(this);
        tuesday.setOnClickListener(this);
        wednesday.setOnClickListener(this);
        thursday.setOnClickListener(this);
        friday.setOnClickListener(this);
        saturday.setOnClickListener(this);
        sunday.setOnClickListener(this);
        pup_cancel.setOnClickListener(this);
    }

    public void showPopupWindow( View view, int type, int[] address){
        this.view = view;
        this.type = type;
        this.address = address;
        if(!popupWindow.isShowing()){
            popupWindow.showAtLocation(contentView, Gravity.FILL,0,0);
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
            case R.id.monday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"1"});
                popupWindow.dismiss();
                break;
            case R.id.tuesday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"2"});
                popupWindow.dismiss();
                break;
            case R.id.wednesday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"3"});
                popupWindow.dismiss();
                break;
            case R.id.thursday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"4"});
                popupWindow.dismiss();
                break;
            case R.id.friday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"5"});
                popupWindow.dismiss();
                break;
            case R.id.saturday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"6"});
                popupWindow.dismiss();
                break;
            case R.id.sunday:
                new ReadAndWrite().WriteJni(type,address,new String[]{"0"});
                popupWindow.dismiss();
                break;
            case R.id.pup_cancel:
                popupWindow.dismiss();
                break;
        }
    }
}
