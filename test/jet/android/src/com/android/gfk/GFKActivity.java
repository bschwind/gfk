package com.android.gfk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;

public class GFKActivity extends Activity {

	GFKView mView;

	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		Log.i("gfk", "onCreate()");
		mView = new GFKView(getApplication());
		setContentView(mView);
	}

	@Override
	protected void onStart() {
		super.onStart();
		Log.i("gfk", "onStart()");
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.i("gfk", "onRestart()");
	}

	@Override
	protected void onPause() {
		super.onPause();
		mView.onPause();
		Log.i("gfk", "onPause()");
	}

	@Override
	protected void onResume() {
		super.onResume();
		mView.onResume();
		Log.i("gfk", "onResume()");
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.i("gfk", "onStop()");
		GFKLib.unloadContent();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		Log.i("gfk", "onDestroy()");
	}
}
