package com.android.gfk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class GFKActivity extends Activity {

	GFKView mView;

	@Override protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		mView = new GFKView(getApplication());
		setContentView(mView);
	}

	@Override protected void onPause() {
		super.onPause();
		mView.onPause();
	}

	@Override protected void onResume() {
		super.onResume();
		mView.onResume();
	}
}
