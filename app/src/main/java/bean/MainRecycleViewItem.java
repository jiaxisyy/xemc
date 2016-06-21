package bean;

import android.graphics.drawable.Drawable;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class MainRecycleViewItem {
    private Drawable background;
    private String Data;
    private String Type;
    private String str;
    private String unit;
    private int height;
    private Drawable backgroundBig;

    public Drawable getBackground() {
        return background;
    }

    public void setBackground(Drawable background) {
        this.background = background;
    }

    public String getData() {
        return Data;
    }

    public void setData(String data) {
        Data = data;
    }

    public String getType() {
        return Type;
    }

    public void setType(String type) {
        Type = type;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    public Drawable getBackgroundBig() {
        return backgroundBig;
    }

    public void setBackgroundBig(Drawable backgroundBig) {
        this.backgroundBig = backgroundBig;
    }

    public String getUnit() {
        return unit;
    }

    public void setUnit(String unit) {
        this.unit = unit;
    }
}
