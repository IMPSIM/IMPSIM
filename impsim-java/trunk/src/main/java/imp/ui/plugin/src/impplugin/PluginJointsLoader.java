/**
 * PluginJointsLoader.java
 * 5/2/12
 */
package impplugin;

import imp.core.commands.DynamicJointBuilder;
import imp.core.commands.JointArgumentInfo;
import imp.core.commands.JointBuilder;
import imp.core.commands.JointEntry;
import imp.core.exceptions.NonExistentJointEntry;

import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.jar.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;

/**
 * This is the class that resides in the plugin to dynamically load all joint files from the imp jar
 * 
 * @author chancea
 * 
 */
public class PluginJointsLoader {

	private PluginJointsLoader() {
	};

	public static String[] getTypes() {
		List<String> list = new ArrayList<String>();
		Collection<JointBuilder> joints = DynamicJointBuilder.getAllBuilders();
		for (JointBuilder j : joints) {
			list.add(j.name);
		}
		String[] retval = new String[list.size()];
		for (int i = 0; i < retval.length; i++) {
			retval[i] = list.get(i);
		}
		return retval;
	}

	public static String[] getDataFields(String type) {
		String[] retval = null;
		List<JointArgumentInfo> list = null;
		try {
			list = DynamicJointBuilder.getJointBuilder(type).getArguments();
		} catch (NonExistentJointEntry e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		List<String> realArguments = new ArrayList<String>();
		for (int x = 0; x < list.size(); x++) {
			String name = list.get(x).name.toLowerCase();
			if ((!(name.contains("name"))) && (!(name.contains("origin")))) {
				realArguments.add(list.get(x).name);
			}
		}
		retval = new String[realArguments.size()];
		for (int i = 0; i < realArguments.size(); i++) {
			retval[i] = realArguments.get(i);
		}
		return retval;
	}
}
