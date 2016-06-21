package view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;
import android.widget.TextView;

/**
 * Created by zuheng.lv on 2016/6/6.
 */
public class AlarmLamp extends View{

    private Paint paintRect;
    private Paint paintText;
    private float thisX;
    private float thisY;
    public AlarmLamp(Context context) {
        super(context);
         paintRect = new Paint();
         paintRect.setColor(Color.RED);
         paintRect.setStyle(Paint.Style.STROKE);
         paintText = new Paint();
        paintText.setColor(Color.BLACK);
        thisX =getWidth();
        thisY = 0;
        runDraw();
    }
    public AlarmLamp(Context context , AttributeSet attrs){
        super(context,attrs);
    }
    public AlarmLamp(Context context,AttributeSet attrs, int defStyle){
        super(context,attrs,defStyle);

    }
    private void runDraw(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    thisX++;
                    postInvalidate();
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawText("strrrrrfsfssssss",thisX,thisY,paintText);
        canvas.drawRect(0,0,getWidth(),50,paintRect);
    }
}
