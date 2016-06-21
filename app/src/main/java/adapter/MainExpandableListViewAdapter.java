package adapter;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.List;
import java.util.Map;


/**
 * Created by shuang.xiang on 2016/6/9.
 */
public class MainExpandableListViewAdapter extends BaseExpandableListAdapter {
    private Map<String, List<String>> map;
    private List<String> parent;
    private Context context;
    private Drawable drawable;
    private List<Integer> icons;


    public MainExpandableListViewAdapter(Map<String, List<String>> map, List<String> parent, Context context, Drawable drawable) {
        this.context = context;
        this.map = map;
        this.parent = parent;
        this.drawable = drawable;
    }

    public MainExpandableListViewAdapter(Map<String, List<String>> map, List<String> parent, Context context, List<Integer> icons) {
        this.context = context;
        this.map = map;
        this.parent = parent;
        this.icons = icons;
    }

    //得到子item需要关联的数据
    @Override
    public Object getChild(int groupPosition, int childPosition) {
        String key = parent.get(groupPosition);
        return (map.get(key).get(childPosition));
    }

    //得到子item的ID
    @Override
    public long getChildId(int groupPosition, int childPosition) {
        return childPosition;
    }

    //设置子item的组件
    @Override
    public View getChildView(int groupPosition, int childPosition,
                             boolean isLastChild, View convertView, ViewGroup parent) {
        String key = this.parent.get(groupPosition);
        String info = map.get(key).get(childPosition);
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.layout_children, null);
        }
        TextView tv = (TextView) convertView
                .findViewById(R.id.second_textview);
        tv.setText(info);
        return convertView;
    }

    //获取当前父item下的子item的个数
    @Override
    public int getChildrenCount(int groupPosition) {
        String key = parent.get(groupPosition);
        int size = map.get(key).size();
        return size;
    }

    //获取当前父item的数据
    @Override
    public Object getGroup(int groupPosition) {
        return parent.get(groupPosition);
    }

    @Override
    public int getGroupCount() {
        return parent.size();
    }

    @Override
    public long getGroupId(int groupPosition) {
        return groupPosition;
    }

    //设置父item组件
    @Override
    public View getGroupView(int groupPosition, boolean isExpanded,
                             View convertView, ViewGroup parent) {
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.layout_parent, null);
        }
        TextView tv = (TextView) convertView
                .findViewById(R.id.parent_textview);
        tv.setText(this.parent.get(groupPosition));
        ImageView imageView = (ImageView) convertView.findViewById(R.id.iv_main_icon);
        imageView.setImageResource(icons.get(groupPosition));

        return convertView;
    }

    @Override
    public boolean hasStableIds() {
        return true;
    }

    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
        return true;
    }

}

