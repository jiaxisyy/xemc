package utils;
/**
 * Created by zuheng.lv on 2016/4/30.
 */
public class Constants {
    /**常量表*/
    public interface Define {
        int OP_BIT_X =0;
        int OP_BIT_Y =1;
        int OP_BIT_M =2;
        int OP_BIT_S =3;
        int OP_BIT_T =4;
        int OP_BIT_C =5;
        int OP_BIT_SM =6;

        int OP_WORD_D =10;
        int OP_WORD_R =11;
        int OP_WORD_SD =12;
        int OP_WORD_Z =13;
        int OP_WORD_T =14;

        int OP_DWORD_D =20;
        int OP_DWORD_R =21;
        int OP_DWORD_SD =22;
        int OP_DWORD_Z =23;
        int OP_DWORD_C =24;

        int OP_REAL_D =30;
        int OP_REAL_R =31;
        //保存登陆用户名
        String IS_LOGIN_USER_REMEMBER="is_login_user_remember";
        //保存的用户名
        String LOGIN_USERNAME="login_username";

    }
}
