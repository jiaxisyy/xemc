package download;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.PopupWindow;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.hitek.serial.R;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.ConnectException;
import java.net.HttpURLConnection;
import java.net.URL;
import bean.ApkInfo;
import utils.CacheUtils;
import utils.Httputils;

/**
 * Created by shuang.xiang on 2016/6/11.
 */
public class UpdateApp {
    private static String appName = "techray-coic";
    private static String localUrl = "http://10.199.198.161:8081/JavaWebApp/ver.json";
    private static String localFileUrl = "http://10.199.198.161:8081/JavaWebApp/techray-coic.apk";
    private static String url = "http://10.199.198.55:58010/userconsle/clientApps/" + appName;
    private static String fileUrl = "http://10.199.198.55:58010/userconsle/clientApps/" + appName + "/file";
    private static String filePath;
    private Context context;
    private static int NEW = 1;
    private static int OLD = 2;
    private static int INTERNETERROR = 3;
    private static String apkPath;

    private static PopupWindow upPopupWindow;
    public UpdateApp(Context context) {
        this.context = context;
    }
    private  Handler handler = new Handler() {

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if (msg.what == NEW) {
                //为最新,不需要更新
                Toast.makeText(context, "当前版本为最新版本", Toast.LENGTH_SHORT).show();
            }
            if (msg.what == OLD) {
                View newView = LayoutInflater.from(context).inflate(R.layout.popupwindow_update, null);
                final PopupWindow upPopupWindow = new PopupWindow(newView, WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT, true);
                upPopupWindow.showAsDropDown(newView);
                upPopupWindow.setAnimationStyle(R.style.AnimationPreview);
                upPopupWindow.showAsDropDown(newView);
                final TextView affirm = (TextView) newView.findViewById(R.id.pp_btn_update_affirm);
                final TextView cancel = (TextView) newView.findViewById(R.id.pp_btn_update_cancel);

                //确定更新
                affirm.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        update();
                        upPopupWindow.dismiss();

                    }
                });
                //取消
                cancel.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        upPopupWindow.dismiss();

                    }
                });


            }
            if (msg.what == INTERNETERROR) {
                //网络异常
                Toast.makeText(context, "网络异常", Toast.LENGTH_SHORT).show();


            }


        }
    };


    private void update() {



        new Thread() {
            @Override
            public void run() {
                super.run();
                try {
                    URL url = new URL(fileUrl);
                    HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                    conn.addRequestProperty("Cookie", CacheUtils.getString(context, "ID"));
                    conn.connect();
                    int length = conn.getContentLength();
                    InputStream is = conn.getInputStream();
                    String sdpath = Environment.getExternalStorageDirectory() + filePath.substring(0, 9);
//                    Log.d("TAG", sdpath);

                    File file = new File(sdpath);
                    // 判断文件目录是否存在
                    if (!file.exists()) {
                        file.mkdir();
                    }
                    File apkFile = new File(sdpath, appName + ".apk");//aaa 下载下来的软件名称

                    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(apkFile));
                    byte[] buf = new byte[1024 * 8];
                    int len = 0;
                    while ((len = is.read(buf)) != -1) {
//                        System.out.println(len);
                        bos.write(buf, 0, len);
                    }
                    System.out.println("end" + length / 1024 / 1024);
                    bos.flush();
                    bos.close();
                    is.close();

                    Intent intent = new Intent(Intent.ACTION_VIEW);
                    intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    intent.setDataAndType(Uri.fromFile(new File(apkFile.getPath())), "application/vnd.android.package-archive");
                    context.startActivity(intent);
                } catch (Exception e) {
                    e.printStackTrace();
                }

            }

        }.start();

    }


    /**
     * 更新apk文件
     */
    public void updateApk() throws RuntimeException{
        new Thread(new Runnable() {
            @Override
            public void run() {
                Httputils httputils = new Httputils(context);
                byte[] bytes = httputils.loadByteFromURL(url, context);

                if (bytes != null) {
                    String s = new String(bytes);
                    Gson gson = new Gson();
                    ApkInfo apkInfo = gson.fromJson(s, ApkInfo.class);

                    filePath = apkInfo.getFilePath();
                    int verCode = getVerCode(context);
                    int versionCode = apkInfo.getVersionCode();
                    if (versionCode > verCode) {
                        //需要更新
                        Message obtain = Message.obtain();
                        obtain.what = OLD;
                        handler.sendMessage(obtain);

                    } else {
                        //提示不需要更新,是最新版本
                        Message obtain = Message.obtain();
                        obtain.what = NEW;
                        handler.sendMessage(obtain);
                    }
                }
            }
        }).start();

    }

    public static String getApplicationName(Context context) {
        PackageManager packageManager = null;
        ApplicationInfo applicationInfo = null;
        try {
            packageManager = context.getPackageManager();
            applicationInfo = packageManager.getApplicationInfo(context.getPackageName(), 0);
        } catch (PackageManager.NameNotFoundException e) {
            applicationInfo = null;
        }
        String applicationName =
                (String) packageManager.getApplicationLabel(applicationInfo);
        return applicationName;
    }

    /**
     * 获取版本名
     *
     * @param context
     * @return
     */
    public static String getVerName(Context context) {
        String versionName = "";
        String packageName = context.getPackageName();

        try {
            versionName = context.getPackageManager().getPackageInfo(packageName, 0).versionName;

        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        return versionName;
    }

    /**
     * 获取本地版本
     *
     * @param context
     * @return
     */
    public static int getVerCode(Context context) {

        int verCode = -1;
        //包名
        String packageName = context.getPackageName();

        try {
            verCode = context.getPackageManager().getPackageInfo(packageName, 0).versionCode;


        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }


        return verCode;
    }
}
