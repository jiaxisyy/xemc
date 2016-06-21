package utils;

import android.util.Log;

import activity.MyApplication;

/**
 * Created by zuheng.lv on 2016/5/6.
 */
public class ReadAndWrite {



    public static String[] ReadJni(int type, int[] str){
        String[] Return =new String[str.length] ;
        switch (type){
            case Constants.Define.OP_BIT_X:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_X,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_Y:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_Y,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_M:
                for(int i =0;i<str.length;i++){

                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_M,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_S:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_S,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_T:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_T,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_C:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_C,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_BIT_SM:
                for(int i =0;i<str.length;i++){
                    byte[] x=  MyApplication.getInstance().mdbusreadbyte(Constants.Define.OP_BIT_SM,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_WORD_R:
                for(int i =0;i<str.length;i++){
                    short[] x=  MyApplication.getInstance().mdbusreadword(Constants.Define.OP_WORD_R,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_WORD_D:
                for(int i =0;i<str.length;i++){
                    short[] x=  MyApplication.getInstance().mdbusreadword(Constants.Define.OP_WORD_D,str[i],1);
                    ;
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_WORD_SD:
                for(int i =0;i<str.length;i++){
                    short[] x=  MyApplication.getInstance().mdbusreadword(Constants.Define.OP_WORD_SD,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_WORD_Z:
                for(int i =0;i<str.length;i++){
                    short[] x=  MyApplication.getInstance().mdbusreadword(Constants.Define.OP_WORD_Z,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_WORD_T:
                for(int i =0;i<str.length;i++){
                    short[] x=  MyApplication.getInstance().mdbusreadword(Constants.Define.OP_WORD_T,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_DWORD_D:
                for(int i =0;i<str.length;i++){
                    int[] x=  MyApplication.getInstance().mdbusreaddword(Constants.Define.OP_DWORD_D,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_DWORD_R:
                for(int i =0;i<str.length;i++){
                    int[] x=  MyApplication.getInstance().mdbusreaddword(Constants.Define.OP_DWORD_R,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_DWORD_SD:
                for(int i =0;i<str.length;i++){
                    int[] x=  MyApplication.getInstance().mdbusreaddword(Constants.Define.OP_DWORD_SD,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_DWORD_Z:
                for(int i =0;i<str.length;i++){
                    int[] x=  MyApplication.getInstance().mdbusreaddword(Constants.Define.OP_DWORD_Z,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_DWORD_C:
                Return = new String[str.length];
                for(int i =0;i<str.length;i++){
                    int[] x=  MyApplication.getInstance().mdbusreaddword(Constants.Define.OP_DWORD_C,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
            case Constants.Define.OP_REAL_D:
                for(int i =0;i<str.length;i++){
                    float[] x=  MyApplication.getInstance().mdbusreadreal(Constants.Define.OP_REAL_D,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
               break;

            case Constants.Define.OP_REAL_R:
                for(int i =0;i<str.length;i++){
                    float[] x=  MyApplication.getInstance().mdbusreadreal(Constants.Define.OP_REAL_R,str[i],1);
                    Return[i] = String.valueOf(x[0]);
                }
                break;
        }
        return Return;
    }

    public static void WriteJni(int type, int[] str, String[] input){
        switch (type){
            case Constants.Define.OP_BIT_X:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_X,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_Y:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_Y,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_M:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_M,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_S:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_S,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_T:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_T,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_C:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_C,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_BIT_SM:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        MyApplication.getInstance().mdbuswritebyte(Constants.Define.OP_BIT_SM,input[i].getBytes(),str[i],1);
                    }
                }
                break;
            case Constants.Define.OP_WORD_R:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        short[]s = {Short.parseShort(input[i])};
                        MyApplication.getInstance().mdbuswriteword(Constants.Define.OP_WORD_R,s,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_WORD_D:

                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        short[]s = {Short.parseShort(input[i])};
                        MyApplication.getInstance().mdbuswriteword(Constants.Define.OP_WORD_D,s,str[i],1);

                    }

                }
                break;
            case Constants.Define.OP_WORD_SD:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        short[]s = {Short.parseShort(input[i])};
                        MyApplication.getInstance().mdbuswriteword(Constants.Define.OP_WORD_SD,s,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_WORD_Z:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        short[]s = {Short.parseShort(input[i])};
                        MyApplication.getInstance().mdbuswriteword(Constants.Define.OP_WORD_Z,s,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_WORD_T:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        short[]s = {Short.parseShort(input[i])};
                        MyApplication.getInstance().mdbuswriteword(Constants.Define.OP_WORD_T,s,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_DWORD_D:
//                Log.d("TAG","OP_DWORD_D1");
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
//                        Log.d("TAG","OP_DWORD_D2");
                        int[]integer = {Integer.parseInt(input[i])};
                        MyApplication.getInstance().mdbuswritedword(Constants.Define.OP_DWORD_D,integer,str[i],1);
//                        Log.d("TAG","OP_DWORD_D3");
                    }

                }
                break;
            case Constants.Define.OP_DWORD_R:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        int[]integer = {Integer.parseInt(input[i])};
                        MyApplication.getInstance().mdbuswritedword(Constants.Define.OP_DWORD_R,integer,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_DWORD_SD:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        int[]integer = {Integer.parseInt(input[i])};
                        MyApplication.getInstance().mdbuswritedword(Constants.Define.OP_DWORD_SD,integer,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_DWORD_Z:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        int[]integer = {Integer.parseInt(input[i])};
                        MyApplication.getInstance().mdbuswritedword(Constants.Define.OP_DWORD_Z,integer,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_DWORD_C:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        int[]integer = {Integer.parseInt(input[i])};
                        MyApplication.getInstance().mdbuswritedword(Constants.Define.OP_DWORD_C,integer,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_REAL_D:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        float[]floats = {Float.parseFloat(input[i])};
                        MyApplication.getInstance().mdbuswritereal(Constants.Define.OP_REAL_D,floats,str[i],1);
                    }

                }
                break;
            case Constants.Define.OP_REAL_R:
                for(int i =0;i<str.length;i++){
                    if(input[i]!=null && !input[i].equals("")){
                        float[]floats = {Float.parseFloat(input[i])};
                        MyApplication.getInstance().mdbuswritereal(Constants.Define.OP_REAL_R,floats,str[i],1);
                    }
                }
                break;
        }
    }
}
