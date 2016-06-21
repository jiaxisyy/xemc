package adapter;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.List;

import activity.MyApplication;
import bean.MainRecycleViewItem;
import utils.Constants;
import utils.ReadAndWrite;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class MainRecycleViewAdapter extends RecyclerView.Adapter<MainRecycleViewAdapter.ViewHolder> {

    private Context context;
    private List<MainRecycleViewItem> list;
    private boolean flag;
    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case 1:
                    for (int i = 0; i <= list.size() - 1; i++) {

                        float v = Float.parseFloat(msg.getData().get(list.get(i).getStr()).toString());

                        list.get(i).setData(String.valueOf((float) Math.round(v * 100) / 100));

                    }
                    notifyDataSetChanged();
                    break;
            }

        }
    };

    public MainRecycleViewAdapter(Context context, List<MainRecycleViewItem> list, boolean flag) {
        super();
        this.context = context;
        this.list = list;
        this.flag = flag;
        onRefresh();
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.main_recycleview_layout, parent, false);
        ViewHolder viewHolder = new ViewHolder(view);
        return viewHolder;
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public void onBindViewHolder(final ViewHolder holder, int position) {
        holder.main_recycleview_data.setText(list.get(position).getData().toString() + list.get(position).getUnit() + "\n" + "\n" + list.get(position).getType());
        if (flag) {
            holder.main_recycleview_data.setBackground(list.get(position).getBackground());
            holder.main_recycleview_data.setTextSize(22);
        } else {
            holder.main_recycleview_data.setTextSize(44);
            holder.main_recycleview_data.setBackground(list.get(position).getBackgroundBig());
        }
        holder.main_recycleview_data.setHeight(list.get(position).getHeight());
        if (mOnItemClickLitener != null) {
            holder.itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int pos = holder.getLayoutPosition();
                    mOnItemClickLitener.onItemClick(holder.itemView, pos);
                }
            });

            holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    int pos = holder.getLayoutPosition();
                    mOnItemClickLitener.onItemLongClick(holder.itemView, pos);
                    return false;
                }
            });
        }
    }

    public void onRefresh() {

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    int[] str = new int[list.size()];
                    for (int i = 0; i <= list.size() - 1; i++) {
                        str[i] = Integer.parseInt(list.get(i).getStr());
                    }
                    String[] strings = ReadAndWrite.ReadJni(Constants.Define.OP_REAL_D, str);
                    Bundle bundle = new Bundle();
                    for (int i = 0; i <= list.size() - 1; i++) {
                        bundle.putString(list.get(i).getStr(), strings[i]);
                    }
                    Message msg = new Message();
                    msg.what = 1;
                    msg.setData(bundle);
                    handler.sendMessage(msg);
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    @Override
    public int getItemCount() {
        return list.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        TextView main_recycleview_data;

        public ViewHolder(View itemView) {
            super(itemView);
            main_recycleview_data = (TextView) itemView.findViewById(R.id.main_recycleview_data);
        }
    }

    public void removeData(int position, MainRecycleViewItem classess) {
//        classess.setHeight(100);
        list.add(classess);
        list.remove(position);

        notifyItemRemoved(position);
    }

    public void removeData(MainRecycleViewItem classess) {
//        classess.setHeight(220);
        list.add(classess);
        list.remove(0);
        notifyItemRemoved(0);
    }

    public interface OnItemClickLitener {
        void onItemClick(View view, int position);

        void onItemLongClick(View view, int position);
    }

    private OnItemClickLitener mOnItemClickLitener;

    public void setOnItemClickLitener(OnItemClickLitener mOnItemClickLitener) {
        this.mOnItemClickLitener = mOnItemClickLitener;
    }
}
