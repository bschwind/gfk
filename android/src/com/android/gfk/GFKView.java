package com.android.gfk;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

/**
 * A simple GLSurfaceView sub-class that demonstrate how to perform
 * OpenGL ES 2.0 rendering into a GL Surface. Note the following important
 * details:
 *
 * - The class must use a custom context factory to enable 2.0 rendering.
 *   See ContextFactory class definition below.
 *
 * - The class must use a custom EGLConfigChooser to be able to select
 *   an EGLConfig that supports 2.0. This is done by providing a config
 *   specification to eglChooseConfig() that has the attribute
 *   EGL10.ELG_RENDERABLE_TYPE containing the EGL_OPENGL_ES2_BIT flag
 *   set. See ConfigChooser class definition below.
 *
 * - The class must select the surface's format, then choose an EGLConfig
 *   that matches it exactly (with regards to red/green/blue/alpha channels
 *   bit depths). Failure to do so would result in an EGL_BAD_MATCH error.
 */
class GFKView extends GLSurfaceView {
	private static String TAG = "GFKView";
	private static final boolean DEBUG = false;

	public GFKView(Context context) {
		super(context);
		init(false, 0, 0);
	}

	public GFKView(Context context, boolean translucent, int depth, int stencil) {
		super(context);
		init(translucent, depth, stencil);
	}

	private void init(boolean translucent, int depth, int stencil) {
		/* By default, GLSurfaceView() creates a RGB_565 opaque surface.
		 * If we want a translucent one, we should change the surface's
		 * format here, using PixelFormat.TRANSLUCENT for GL Surfaces
		 * is interpreted as any 32-bit surface with alpha by SurfaceFlinger.
		 */
		if (translucent) {
			this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		}

		/* Setup the context factory for 2.0 rendering.
		 * See ContextFactory class definition below
		 */
		setEGLContextFactory(new ContextFactory());

		/* We need to choose an EGLConfig that matches the format of
		 * our surface exactly. This is going to be done in our
		 * custom config chooser. See ConfigChooser class definition
		 * below.
		 */
		// setEGLConfigChooser(translucent ?
		// 					 new ConfigChooser(8, 8, 8, 8, depth, stencil) :
		// 					 new ConfigChooser(5, 6, 5, 0, depth, stencil));

		setEGLConfigChooser(new MultisampleConfigChooser());

		/* Set the renderer responsible for frame rendering */
		setRenderer(new Renderer());
	}

	private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
		private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

		public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
			Log.w(TAG, "creating OpenGL ES 2.0 context");

			checkEglError("Before eglCreateContext", egl);
			int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
			EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
			checkEglError("After eglCreateContext", egl);

			return context;
		}

		public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
			egl.eglDestroyContext(display, context);
		}
	}

	private static void checkEglError(String prompt, EGL10 egl) {
		int error;

		while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
			Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
		}
	}

	private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {
		private static int[] attributes = {
					EGL10.EGL_BUFFER_SIZE,
					EGL10.EGL_ALPHA_SIZE,
					EGL10.EGL_BLUE_SIZE,
					EGL10.EGL_GREEN_SIZE,
					EGL10.EGL_RED_SIZE,
					EGL10.EGL_DEPTH_SIZE,
					EGL10.EGL_STENCIL_SIZE,
					EGL10.EGL_CONFIG_CAVEAT,
					EGL10.EGL_CONFIG_ID,
					EGL10.EGL_LEVEL,
					EGL10.EGL_MAX_PBUFFER_HEIGHT,
					EGL10.EGL_MAX_PBUFFER_PIXELS,
					EGL10.EGL_MAX_PBUFFER_WIDTH,
					EGL10.EGL_NATIVE_RENDERABLE,
					EGL10.EGL_NATIVE_VISUAL_ID,
					EGL10.EGL_NATIVE_VISUAL_TYPE,
					0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
					EGL10.EGL_SAMPLES,
					EGL10.EGL_SAMPLE_BUFFERS,
					EGL10.EGL_SURFACE_TYPE,
					EGL10.EGL_TRANSPARENT_TYPE,
					EGL10.EGL_TRANSPARENT_RED_VALUE,
					EGL10.EGL_TRANSPARENT_GREEN_VALUE,
					EGL10.EGL_TRANSPARENT_BLUE_VALUE,
					0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
					0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
					0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
					0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
					EGL10.EGL_LUMINANCE_SIZE,
					EGL10.EGL_ALPHA_MASK_SIZE,
					EGL10.EGL_COLOR_BUFFER_TYPE,
					EGL10.EGL_RENDERABLE_TYPE,
					0x3042 // EGL10.EGL_CONFORMANT
			};

			private static String[] names = {
					"EGL_BUFFER_SIZE",
					"EGL_ALPHA_SIZE",
					"EGL_BLUE_SIZE",
					"EGL_GREEN_SIZE",
					"EGL_RED_SIZE",
					"EGL_DEPTH_SIZE",
					"EGL_STENCIL_SIZE",
					"EGL_CONFIG_CAVEAT",
					"EGL_CONFIG_ID",
					"EGL_LEVEL",
					"EGL_MAX_PBUFFER_HEIGHT",
					"EGL_MAX_PBUFFER_PIXELS",
					"EGL_MAX_PBUFFER_WIDTH",
					"EGL_NATIVE_RENDERABLE",
					"EGL_NATIVE_VISUAL_ID",
					"EGL_NATIVE_VISUAL_TYPE",
					"EGL_PRESERVED_RESOURCES",
					"EGL_SAMPLES",
					"EGL_SAMPLE_BUFFERS",
					"EGL_SURFACE_TYPE",
					"EGL_TRANSPARENT_TYPE",
					"EGL_TRANSPARENT_RED_VALUE",
					"EGL_TRANSPARENT_GREEN_VALUE",
					"EGL_TRANSPARENT_BLUE_VALUE",
					"EGL_BIND_TO_TEXTURE_RGB",
					"EGL_BIND_TO_TEXTURE_RGBA",
					"EGL_MIN_SWAP_INTERVAL",
					"EGL_MAX_SWAP_INTERVAL",
					"EGL_LUMINANCE_SIZE",
					"EGL_ALPHA_MASK_SIZE",
					"EGL_COLOR_BUFFER_TYPE",
					"EGL_RENDERABLE_TYPE",
					"EGL_CONFORMANT"
			};

		/* This EGL config specification is used to specify 2.0 rendering.
		 * We use a minimum size of 4 bits for red/green/blue, but will
		 * perform actual matching in chooseConfig() below.
		 */
		private static int EGL_OPENGL_ES2_BIT = 4;
		private static int[] s_configAttribs2 =
		{
			EGL10.EGL_RED_SIZE, 4,
			EGL10.EGL_GREEN_SIZE, 4,
			EGL10.EGL_BLUE_SIZE, 4,
			EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL10.EGL_NONE
		};

		// Subclasses can adjust these values:
		protected int mRedSize;
		protected int mGreenSize;
		protected int mBlueSize;
		protected int mAlphaSize;
		protected int mDepthSize;
		protected int mStencilSize;
		private int[] mValue = new int[1];

		public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
			mRedSize = r;
			mGreenSize = g;
			mBlueSize = b;
			mAlphaSize = a;
			mDepthSize = depth;
			mStencilSize = stencil;
		}

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
			/* Get the number of minimally matching EGL configurations
			 */
			int[] num_config = new int[1];
			egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

			int numConfigs = num_config[0];

			if (numConfigs <= 0) {
				throw new IllegalArgumentException("No configs match configSpec");
			}

			/* Allocate then read the array of minimally matching EGL configs
			 */
			EGLConfig[] configs = new EGLConfig[numConfigs];
			egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

			if (DEBUG) {
				 printConfigs(egl, display, configs);
			}

			/* Now return the "best" one
			 */
			return chooseConfig(egl, display, configs);
		}

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
			for (EGLConfig config : configs) {
				int d = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
				int s = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);

				// We need at least mDepthSize and mStencilSize bits
				if (d < mDepthSize || s < mStencilSize) {
					continue;
				}

				// We want an *exact* match for red/green/blue/alpha
				int r = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
				int g = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
				int b = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
				int a = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

				if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize) {
					return config;
				}
			}
			return null;
		}

		private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue) {
			if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
				return mValue[0];
			}

			return defaultValue;
		}

		private void printConfigs(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
			int numConfigs = configs.length;
			Log.w(TAG, String.format("%d configurations", numConfigs));

			for (int i = 0; i < numConfigs; i++) {
				Log.w(TAG, String.format("Configuration %d:\n", i));
				printConfig(egl, display, configs[i]);
			}
		}

		private void printConfig(EGL10 egl, EGLDisplay display, EGLConfig config) {
			int[] value = new int[1];

			for (int i = 0; i < attributes.length; i++) {
				int attribute = attributes[i];
				String name = names[i];

				if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
					Log.w(TAG, String.format("  %s: %d\n", name, value[0]));
				} else {
					// Log.w(TAG, String.format("  %s: failed\n", name));
					while (egl.eglGetError() != EGL10.EGL_SUCCESS);
				}
			}
		}
	}

	public class MultisampleConfigChooser implements GLSurfaceView.EGLConfigChooser {
		static private final String kTag = "GDC11";

		@Override
		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
			mValue = new int[1];

			// Try to find a normal multisample configuration first.
			int[] configSpec = {
					EGL10.EGL_RED_SIZE, 5,
					EGL10.EGL_GREEN_SIZE, 6,
					EGL10.EGL_BLUE_SIZE, 5,
					EGL10.EGL_DEPTH_SIZE, 16,
					// Requires that setEGLContextClientVersion(2) is called on the view.
					EGL10.EGL_RENDERABLE_TYPE, 4 /* EGL_OPENGL_ES2_BIT */,
					EGL10.EGL_SAMPLE_BUFFERS, 1 /* true */,
					EGL10.EGL_SAMPLES, 2,
					EGL10.EGL_NONE
			};

			if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue)) {
				throw new IllegalArgumentException("eglChooseConfig failed");
			}

			int numConfigs = mValue[0];

			if (numConfigs <= 0) {
				// No normal multisampling config was found. Try to create a
				// converage multisampling configuration, for the nVidia Tegra2.
				// See the EGL_NV_coverage_sample documentation.

				final int EGL_COVERAGE_BUFFERS_NV = 0x30E0;
				final int EGL_COVERAGE_SAMPLES_NV = 0x30E1;

				configSpec = new int[] {
						EGL10.EGL_RED_SIZE, 5,
						EGL10.EGL_GREEN_SIZE, 6,
						EGL10.EGL_BLUE_SIZE, 5,
						EGL10.EGL_DEPTH_SIZE, 16,
						EGL10.EGL_RENDERABLE_TYPE, 4 /* EGL_OPENGL_ES2_BIT */,
						EGL_COVERAGE_BUFFERS_NV, 1 /* true */,
						EGL_COVERAGE_SAMPLES_NV, 2,  // always 5 in practice on tegra 2
						EGL10.EGL_NONE
				};

				if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue)) {
					throw new IllegalArgumentException("2nd eglChooseConfig failed");
				}

				numConfigs = mValue[0];

				if (numConfigs <= 0) {
					// Give up, try without multisampling.
					configSpec = new int[]{
							EGL10.EGL_RED_SIZE, 5,
							EGL10.EGL_GREEN_SIZE, 6,
							EGL10.EGL_BLUE_SIZE, 5,
							EGL10.EGL_DEPTH_SIZE, 16,
							EGL10.EGL_RENDERABLE_TYPE, 4 /* EGL_OPENGL_ES2_BIT */,
							EGL10.EGL_NONE
					};

					if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue)) {
						throw new IllegalArgumentException("3rd eglChooseConfig failed");
					}

					numConfigs = mValue[0];

					if (numConfigs <= 0) {
					  throw new IllegalArgumentException("No configs match configSpec");
					}

				} else {
					mUsesCoverageAa = true;
				}
			}

			// Get all matching configurations.
			EGLConfig[] configs = new EGLConfig[numConfigs];
			if (!egl.eglChooseConfig(display, configSpec, configs, numConfigs, mValue)) {
				throw new IllegalArgumentException("data eglChooseConfig failed");
			}

			// CAUTION! eglChooseConfigs returns configs with higher bit depth
			// first: Even though we asked for rgb565 configurations, rgb888
			// configurations are considered to be "better" and returned first.
			// You need to explicitly filter the data returned by eglChooseConfig!
			int index = -1;

			for (int i = 0; i < configs.length; ++i) {
				if (findConfigAttrib(egl, display, configs[i], EGL10.EGL_RED_SIZE, 0) == 5) {
					index = i;
					break;
				}
			}

			if (index == -1) {
				Log.w(kTag, "Did not find sane config, using first");
			}

			EGLConfig config = configs.length > 0 ? configs[index] : null;

			if (config == null) {
				throw new IllegalArgumentException("No config chosen");
			}

			return config;
		}

		private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue) {
			if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
				return mValue[0];
			}
			
			return defaultValue;
		}

		public boolean usesCoverageAa() {
			return mUsesCoverageAa;
		}

		private int[] mValue;
		private boolean mUsesCoverageAa;
	}

	private static class Renderer implements GLSurfaceView.Renderer {
		public void onDrawFrame(GL10 gl) {
			GFKLib.step();
		}

		public void onSurfaceChanged(GL10 gl, int width, int height) {
			GFKLib.resize(width, height);
		}

		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			GFKLib.init();
		}
	}
}
