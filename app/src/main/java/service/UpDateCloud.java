package service;

import org.json.JSONObject;

import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/2.
 */
public class UpDateCloud {
    private String str;
    /**
     * 更新数据到云端
     */
    public UpDateCloud(String str){
       this.str = str;
    }
    public void upDateData(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    int st[]={212,264,228,244};
                    String[]num = ReadAndWrite.ReadJni(Constants.Define.OP_REAL_D,st);
                    try {
                        URL url = new URL(str);
                        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                        JSONObject ClientKey = new JSONObject();
                        ClientKey.put("pressure",num[0]);
                        ClientKey.put("concentration",num[3]);
                        ClientKey.put("flow",num[2]);
                        ClientKey.put("totalflow",num[1]);
                        JSONObject params = new JSONObject();
                        params.put("date",ClientKey);
                        String content = String.valueOf(params);
                        connection.setConnectTimeout(8000);
                        connection.setDoOutput(true);
                        connection.setRequestMethod("POST");
                        OutputStream outputStream = connection.getOutputStream();
                        outputStream.write(content.getBytes());
                        outputStream.close();
                        int code =connection.getResponseCode();
                        if(code ==200){
                            //上传成功
                        }else {
                            //上传失败
                        }
                        Thread.sleep(1000);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

}
