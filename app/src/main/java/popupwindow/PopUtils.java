package popupwindow;



import android.app.Activity;
import android.view.WindowManager;

/**
 * Created by Administrator on 2016/1/22.
 */
public class PopUtils {
    public static  void setBackgroundAlpha(float alpha, Activity activity) {
        WindowManager.LayoutParams lp = (activity).getWindow().getAttributes();
        lp.alpha = alpha;
        (activity).getWindow().setAttributes(lp);
    }

}
