package impplugin;

import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Platform;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.ImageRegistry;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.Bundle;
import org.osgi.framework.BundleContext;

/**
 * The activator class controls the plug-in life cycle
 */
public class Activator extends AbstractUIPlugin {

	// The plug-in ID
	public static final String PLUGIN_ID = "IMPPlugIn"; //$NON-NLS-1$

	// The shared instance
	private static Activator plugin;
	
	/**
	 * The constructor
	 */
	public Activator() {
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext context) throws Exception {
		super.start(context);
		plugin = this;
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext context) throws Exception {
		plugin = null;
		super.stop(context);
	}

	/**
	 * Returns the shared instance
	 *
	 * @return the shared instance
	 */
	public static Activator getDefault() {
		return plugin;
	}
	
	@Override
    protected void initializeImageRegistry(ImageRegistry registry) {
        super.initializeImageRegistry(registry);
        
        //add in the local image files to the registry
        
        Bundle bundle = Platform.getBundle(PLUGIN_ID);
        
        ImageDescriptor imgRun = ImageDescriptor.createFromURL(
              FileLocator.find(bundle,new Path("icons/Run.png"),null));
        registry.put("IMG_RUN", imgRun);
        
        ImageDescriptor imgPause = ImageDescriptor.createFromURL(
                FileLocator.find(bundle,new Path("icons/Pause.png"),null));
        registry.put("IMG_PAUSE", imgPause);
        
        ImageDescriptor imgStop = ImageDescriptor.createFromURL(
                FileLocator.find(bundle,new Path("icons/Stop.png"),null));
        registry.put("IMG_STOP", imgStop);
	}

}
