package bean;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import org.w3c.dom.Attr;

/**
 * Created by zuheng.lv on 2016/6/10.
 */
public class DrawLine extends View{

    public DrawLine(Context context) {
        super(context);
    }
    public DrawLine(Context context, AttributeSet attr){
        super(context,attr);
    }
    public DrawLine(Context context ,AttributeSet attr,int defStyleAttr){
        super(context,attr,defStyleAttr);
    }
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        Paint paint = new Paint();
        paint.setColor(Color.rgb(196,196,196));
        canvas.drawLine(0,0,getWidth(),getHeight(),paint);
    }
}
