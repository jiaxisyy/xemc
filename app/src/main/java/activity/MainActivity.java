package activity;


import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.FragmentActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ExpandableListView;

import android.widget.PopupWindow;
import android.widget.TextView;
import android.widget.Toast;


import com.hitek.serial.R;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


import adapter.MainExpandableListViewAdapter;
import download.UpdateApp;
import fragment.MonitorFragment;
import fragment.MonitoringFragment;
import fragment.TimeSeriesFragment;
import service.Services;
import utils.CacheUtils;
import utils.Constants;
import utils.Utils;


/**
 * ������
 * Created by zuheng.lv on 2016/4/26.
 */
public class MainActivity extends FragmentActivity implements View.OnClickListener {
    private List<String> parent = null;
    private Map<String, List<String>> map = null;
    private TextView tv_main_time1;
    private TextView btn_main_login1, pp_tv_login_cancel;
    private EditText pp_et_username, pp_et_password;
    private Button pp_btn_affirm, pp_btn_succeed_go_home;
    private CheckBox pp_login_ck_remember;
    private PopupWindow popupWindow, newPopupWindow;
    private String LOGIN_URL = "http://10.199.198.55:58010/userconsle/login";
    private boolean gradeFlag1 = false;
    private boolean gradeFlag2 = false;
    private boolean gradeFlag3 = false;
    private final int MSG_LOGIN_SUCCEED = 1;
    private final int MSG_LOGIN_ERROR = 2;
    private final int TIME = 3;
    private final int NOINTERNET = 4;
    private final int ONE = 5;
    private final int TWO = 6;
    private final int THREE = 7;
    private List<Integer> ions;
    private ExpandableListView elv_mian_state1;
    private View view, newView;
    private String loginInfo;
    private String errorInfo, str;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Utils.replace(getSupportFragmentManager(), R.id.frameLayout_main, MonitorFragment.class);
        setContentView(R.layout.main_layout);
        initialize();
        initData();
//        startService(new Intent(this, Services.class));
        elv_mian_state1.setAdapter(new MainExpandableListViewAdapter(map, parent, this, ions));
        //取消线
//        elv_mian_state.setDivider(null);
        //去掉箭头
//        mainlistview.setGroupIndicator(null);

        elv_mian_state1.setOnChildClickListener(new ExpandableListView.OnChildClickListener() {
            @Override
            public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {


                return true;
            }
        });
        elv_mian_state1.setOnGroupClickListener(new ExpandableListView.OnGroupClickListener() {
            @Override
            public boolean onGroupClick(ExpandableListView parent, View v, int groupPosition, long id) {
                switch (groupPosition) {
                    //主页
                    case 0:
                        Utils.replace(getSupportFragmentManager(), R.id.frameLayout_main, MonitorFragment.class);
                        break;
                    case 1:
                    //监控
                        Utils.replace(getSupportFragmentManager(), R.id.frameLayout_main, MonitoringFragment.class);
                        break;
                    case 2:
                        //设置
                        Utils.replace(getSupportFragmentManager(), R.id.frameLayout_main,TimeSeriesFragment.class);
                        break;

                }


                return false;
            }
        });

    }



    public void initData() {
        parent = new ArrayList<String>();
        parent.add("首页");
        parent.add("监控");
        parent.add("设置");

        map = new HashMap<String, List<String>>();

        List<String> list1 = new ArrayList<String>();
        map.put("首页", list1);

        List<String> list2 = new ArrayList<String>();

        map.put("监控", list2);
        List<String> list3 = new ArrayList<String>();
        map.put("设置", list3);
        ions = new ArrayList<>();
        ions.add(R.drawable.main_icon_home);
        ions.add(R.drawable.main_icon_monitoring);
        ions.add(R.drawable.main_icon_setting);
    }


    private void initialize() {

        tv_main_time1 = (TextView) findViewById(R.id.tv_main_time1);
        btn_main_login1 = (TextView) findViewById(R.id.btn_main_login1);
        elv_mian_state1 = (ExpandableListView) findViewById(R.id.elv_main_state1);
        btn_main_login1.setOnClickListener(this);


    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.btn_main_login1:
                showLoginPopupWindow();
                break;

        }
    }


    /**
     * 获取弹窗
     *
     *  @return
     */

    private PopupWindow getPopupWindow(int layoutId) {
        view = LayoutInflater.from(this).inflate(layoutId, null);
        PopupWindow popupWindow = new PopupWindow(view, WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT, true);
        return popupWindow;
    }

    /**
     * 登陆弹窗
     */
    private void showLoginPopupWindow() {


        popupWindow = getPopupWindow(R.layout.popupwindow_login);
        popupWindow.setAnimationStyle(R.style.AnimationPreview);

        //用户名
        pp_et_username = (EditText) view.findViewById(R.id.pp_et_username);
//        密码
        pp_et_password = (EditText) view.findViewById(R.id.pp_et_password);
        //确认按钮

        pp_btn_affirm = (Button) view.findViewById(R.id.pp_btn_affirm);
//        保存按钮
        pp_login_ck_remember = (CheckBox) view.findViewById(R.id.pp_login_ck_remember);
        //取消按钮

        pp_tv_login_cancel = (TextView) view.findViewById(R.id.pp_tv_login_cancel);
        if (CacheUtils.getBoolean(this, Constants.Define.IS_LOGIN_USER_REMEMBER, false)) {
            pp_et_username.setText(CacheUtils.getString(this, Constants.Define.LOGIN_USERNAME));
        }
        popupWindow.showAsDropDown(view);

        pp_btn_affirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                popupWindow.dismiss();
                }

        });
        pp_tv_login_cancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //取消按钮，关闭弹窗
                popupWindow.dismiss();
                popupWindow.setAnimationStyle(R.style.AnimationPreview);
            }
        });
    }




}





