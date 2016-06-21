package bean;

/**
 * Created by shuang.xiang on 2016/6/11.
 */
public class ApkInfo {

    /**
     * fileName : a.apk
     * appName : aaa
     * filePath : /apkfile/a.apk
     * version : 0.1.1
     * versionCode : 1
     */

    private String fileName;
    private String appName;
    private String filePath;
    private String version;
    private int versionCode;




    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getAppName() {
        return appName;
    }

    public void setAppName(String appName) {
        this.appName = appName;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public int getVersionCode() {
        return versionCode;
    }

    public void setVersionCode(int versionCode) {
        this.versionCode = versionCode;
    }
}
