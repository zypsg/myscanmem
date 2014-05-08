package com.example.jnidemo;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		String msg = getStringFromJNI();

		TextView tv = (TextView) findViewById(R.id.text_view);
		tv.setText(msg);

		int ret = jniStaticShowMessage(MainActivity.this, "JNI test2",
				"test static callback");

		if (ret == 0) {
			tv.setText("test JNI static callback successed");
		} else {
			tv.setText("test JNI static callback failed");
		}

		ret = jniShowMessage(MainActivity.this, "JNI test2",
				"test static callback");
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	static int staticShowMessage(Context ctx, String strTitle, String strMessage) {
		Log.e("MainActivity", ">>>staticShowMessage");

		return 0;
	}

	public String getTestString() {
		return "Hello,world";
	}

	public int showMessage(Context ctx, String strTitle, String strMessage) {
		Log.e("MainActivity", ">>>showMessage strTitle:" + strTitle
				+ ", strMessage:" + strMessage);
		return 0;
	}

	public native String getStringFromJNI();

	public native int jniStaticShowMessage(MainActivity act, String testName,
			String testMethod);

	public native int jniShowMessage(MainActivity act, String testName,
			String testMethod);

	static {
		System.loadLibrary("jnidemo");
	}
}
