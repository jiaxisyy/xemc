package bean;

/**
 * Created by zuheng.lv on 2016/6/2.
 */
public class HistoryData {

    private int keyId;
    private String date;
    private String time;
    private String pressure;
    private String concentration;
    private String flow;
    private String totalflow;

    public int getKeyId() {
        return keyId;
    }

    public void setKeyId(int keyId) {
        this.keyId = keyId;
    }

    public String getPressure() {
        return pressure;
    }

    public void setPressure(String pressure) {
        this.pressure = pressure;
    }

    public String getConcentration() {
        return concentration;
    }

    public void setConcentration(String concentration) {
        this.concentration = concentration;
    }

    public String getFlow() {
        return flow;
    }

    public void setFlow(String flow) {
        this.flow = flow;
    }

    public String getTotalflow() {
        return totalflow;
    }

    public void setTotalflow(String totalflow) {
        this.totalflow = totalflow;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }
}
