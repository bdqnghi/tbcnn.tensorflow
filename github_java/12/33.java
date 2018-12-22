package com.shaderblow.filter.motionblur;

import com.jme3.asset.AssetManager;
import com.jme3.material.Material;
import com.jme3.math.Matrix4f;
import com.jme3.post.Filter;
import com.jme3.renderer.RenderManager;
import com.jme3.renderer.ViewPort;

public class MotionBlurFilter extends Filter {

	
	
	private float strength = 1f;
	private int blurSamples = 8;

	private ViewPort viewPort;
	
	private Matrix4f tempMat = new Matrix4f();
	private Matrix4f currentProjectionMatrix = new Matrix4f();
	private Matrix4f currentToPreviousMatrix = new Matrix4f();
	
	
	
	public MotionBlurFilter() { super("MotionBlur"); }
	
	@Override
	protected Material getMaterial() { return material; }

	@Override
	protected boolean isRequiresDepthTexture() { return true; }

	/** Sets the strength/scale of the "blur" at 100 FPS */
	public float getStrength() { return strength; }

	/** Gets the strength/scale of the "blur" at 100 FPS */
	public void setStrength(float s) { strength = s; }

	/** Gets how "smooth" the blur is. Higher is more smooth, but more GPU intensive. */
	public int getBlurSamples() { return blurSamples; }

	/** Sets the smoothness of the "blur". Lower is faster, but banding is more noticeable.  Higher is slower, but the blur is smoother. 8 is a good balance. */
	public void setBlurSamples(int num) {
		blurSamples = num;
		
		if (material != null)
			material.setInt("BlurSamples", blurSamples);
	}
	
	
	
	@Override
	protected void initFilter(AssetManager manager, RenderManager renderManager, ViewPort vp, int w, int h) {
		material = new Material(manager, "ShaderBlow/MatDefs/Filters/MotionBlur/MotionBlur.j3md");
		
		viewPort = vp;
		
		// set the material parameters to whatever the fields actually are
		// since this initFilter() method doesnt get called
		// til right before the first render, but by then every AppStates'
		// update() methods have run once and if we are changing these
		// parameters in that time, they have already changed but since the material was null
		// at that point the material's value wasn't set!... just trust me on this one...
		setStrength(strength);
		setBlurSamples(blurSamples);
	}

	
	
	/** Calculates and sets the material's curr-to-prev Transformation matrix 
	 *  We do this once the CPU to avoid calling one extra 4x4 matrix-multiplication per fragment on the GPU, which nets ~10% performance increase */
	private void setCurrToPrevMatrix() {
		currentToPreviousMatrix.set(currentProjectionMatrix); // "previous projection matrix"
		
		currentProjectionMatrix.set(viewPort.getCamera().getViewProjectionMatrix()); // "current projection matrix"

		currentToPreviousMatrix.multLocal(currentProjectionMatrix.invert(tempMat)); // "prev proj mat" * "curr proj mat INVERTED"
		material.setMatrix4("CurrentToPreviousMat", currentToPreviousMatrix);
	}
	
	
	
	@Override
	protected void preFrame(float delta) {
		// makes the blur framerate independent
		// makes more sense to do 1 calculation on CPU versus 1 per fragment on GPU
		material.setFloat("Strength", strength * (1f / delta / 100f));
		
		// calculate the currentToPrevious transformation matrix
		setCurrToPrevMatrix();
	}
}