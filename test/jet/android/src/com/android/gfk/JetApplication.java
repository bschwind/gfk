package com.android.gfk;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

public class JetApplication extends Application {
	@Override
	public void onCreate() {
		super.onCreate();
		Log.i("gfk", "Application onCreate()");
	}
}
