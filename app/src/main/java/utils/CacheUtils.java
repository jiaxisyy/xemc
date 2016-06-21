/**
 * 创建日期:2016-1-3下午4:08:04
 * 作者:itheima
 * 描述:TODO
 */
package utils;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

/**
 * @author  使用sp保存软件参数
 */
public class CacheUtils {

	public  static final String IS_FIRST_USE = "is_first_use";//是否第一次使用本应用
	/***
	 * 方法 保存boolean
	 * 
	 * @param context
	 * @param key
	 * @param value
	 */
	public static void putBoolean(Context context, String key, boolean value) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		// 编辑器
		Editor edit = sharedPreferences.edit();
		edit.putBoolean(key, value).commit();
	}

	/***
	 * 方法 读取一个boolean
	 * 
	 * @param context
	 * @param key
	 * @return
	 */
	public static boolean getBoolean(Context context, String key) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		return sharedPreferences.getBoolean(key, false);
	}
	
	//取得布尔值 ，可以设置缺省值
	public static boolean getBoolean(Context context, String key,boolean delValue) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		return sharedPreferences.getBoolean(key, delValue);
	}

	/*** 方法保存字符串
	@param context
	@param key
	@param value
	*/
	public static void putString(Context context, String key, String value) {

		//获取软件参数
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
	
		//编辑器
		Editor edit = sharedPreferences.edit();
		edit.putString(key, value).commit();
	}
	/*** 方法 读取字符串
	@param context
	@param key
	@return
	*/
	public static String getString(Context context, String key) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		return sharedPreferences.getString(key, "");//第二个参数为取不到的时候的默认值
	}
	
	
	
	//取整数	
	public static int getInt(Context context, String key) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		return sharedPreferences.getInt(key,0);//第二个参数为取不到的时候的默认值
	}
	//取整数，可以设置缺省值
	public static int getInt(Context context, String key,int defvalue) {
		// 共享参数对象
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
		return sharedPreferences.getInt(key,defvalue);//第二个参数为取不到的时候的默认值
	}
	//存整数
	public static void putInt(Context context, String key, int value) {

		//获取软件参数
		SharedPreferences sharedPreferences = context.getSharedPreferences("config", Context.MODE_PRIVATE);
	
		//编辑器
		Editor edit = sharedPreferences.edit();
		edit.putInt(key, value).commit();
	}
}
