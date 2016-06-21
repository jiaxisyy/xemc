//package popupwindow;
//
//import android.content.Context;
//import android.view.Gravity;
//import android.view.LayoutInflater;
//import android.view.View;
//import android.widget.Button;
//import android.widget.EditText;
//import android.widget.LinearLayout;
//import android.widget.PopupWindow;
//
//import com.hitek.serial.R;
//
//import utils.ReadAndWrite;
//
///**
// * Created by zuheng.lv on 2016/6/11.
// */
//public class PopupForSystemSetting implements View.OnClickListener {
//
//    private EditText pressure_et_max1,pressure_et_min1,pressure_et_max2,pressure_et_min2;
//    private Button systemsetting_btn_change,systemsetting_btn_cancel;
//    private View contentView;
//    private PopupWindow popupWindow;
//    private int type;
//    private int[] address;
//    private View view;
//    public PopupForSystemSetting(Context context,View view,int type, int[] address){
//        this.view = view;
//        this.type =type;
//        this.address = address;
//         contentView = LayoutInflater.from(context).inflate(R.layout.systemsetting_layout,null);
//        initView();
//        popupWindow = new PopupWindow(contentView, LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT,false);
//
//    }
//    public void showPopupWindow(){
//        if(!popupWindow.isShowing()){
//            popupWindow.showAtLocation(view, Gravity.NO_GRAVITY,130,44);
//        }
//    }
//    public void stopPopupWindow(){
//
//        if(popupWindow.isShowing()){
//            popupWindow.dismiss();
//        }
//    }
//    public void initView(){
//        pressure_et_max1 = (EditText)contentView.findViewById(R.id.pressure_et_max1);
//        pressure_et_min1 = (EditText)contentView.findViewById(R.id.pressure_et_min1);
//        pressure_et_max2 = (EditText)contentView.findViewById(R.id.pressure_et_max2);
//        pressure_et_min2 = (EditText)contentView.findViewById(R.id.pressure_et_min2);
//        pressure_et_max1.setClickable(true);
//        pressure_et_min1.setClickable(true);
//        pressure_et_max2.setClickable(true);
//        pressure_et_min2.setClickable(true);
//        systemsetting_btn_change = (Button) contentView.findViewById(R.id.systemsetting_btn_change);
//        systemsetting_btn_cancel = (Button) contentView.findViewById(R.id.systemsetting_btn_cancel);
//        systemsetting_btn_change.setText("确定");
//        systemsetting_btn_cancel.setVisibility(View.VISIBLE);
//        systemsetting_btn_cancel.setOnClickListener(this);
//        systemsetting_btn_change.setOnClickListener(this);
//    }
//
//    @Override
//    public void onClick(View v) {
//        switch (v.getId()){
//            case R.id.systemsetting_btn_change:
//                if(pressure_et_max1.getText().toString()!=null && !pressure_et_max1.getText().toString().equals("")
//                        &&pressure_et_min1.getText().toString()!=null && !pressure_et_min1.getText().toString().equals("")
//                        &&pressure_et_max2.getText().toString()!=null && !pressure_et_max2.getText().toString().equals("")
//                        &&pressure_et_min2.getText().toString()!=null && !pressure_et_min2.getText().toString().equals("")){
//                    String[] input ={pressure_et_max1.getText().toString(),pressure_et_min1.getText().toString(),pressure_et_max2.getText().toString(),pressure_et_min2.getText().toString()};
//                    new ReadAndWrite().WriteJni(type,address,input);
//                }
//                popupWindow.dismiss();
//                break;
//            case R.id.systemsetting_btn_cancel:
//                    popupWindow.dismiss();
//                break;
//        }
//    }
//}
