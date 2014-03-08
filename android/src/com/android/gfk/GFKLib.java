package com.android.gfk;

public class GFKLib {
	 static {
		 System.loadLibrary("gfk");
	 }

	 public static native void init(int width, int height);
	 public static native void step();
	 public static native void onTouch(float x, float y);
}
