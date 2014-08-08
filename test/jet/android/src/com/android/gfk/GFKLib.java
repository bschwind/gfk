package com.android.gfk;

public class GFKLib {
	 static {
		 System.loadLibrary("gfk");
	 }

	 public static native void init();
	 public static native void resize(int width, int height);
	 public static native void step();
	 public static native void unloadContent();
}
