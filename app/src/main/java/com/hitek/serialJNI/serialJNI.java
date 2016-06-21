package com.hitek.serialJNI;

public class serialJNI {
	static {
        System.loadLibrary("serialJNI");
    }
	public native  boolean init();
	public native  int mainloop();
	public native  byte[]  mdbusreadbyte(int type,int stadr,int len);
	public native  int mdbuswritebyte(int type,byte buf[],int stadr,int len);
	
	public native  short[] mdbusreadword(int type,int stadr,int len);
	public native  int mdbuswriteword(int type,short buf[],int stadr,int len);
	
	public native  int[] mdbusreaddword(int type, int stadr, int len);
	public native  int mdbuswritedword(int type, int buf[], int stadr, int len);
	
	public native  float[] mdbusreadreal(int type, int stadr, int len);
	public native  int mdbuswritereal(int type, float buf[],int stadr, int len);
	
	public native  void destory();
}
